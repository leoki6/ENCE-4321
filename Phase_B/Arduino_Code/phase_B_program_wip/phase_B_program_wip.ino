/* Includes */
#include <Arduino.h>
#include <RTOS.h>

/* Definitions */
#define LED 13
#define BUFF_SIZE 20

/* Globals */
char gCommsMsgBuff[BUFF_SIZE];
int iBuff = 0;
bool gPackageFlag = false;
bool gProcessDataFlag = false;
SemaphoreHandle_t gSerialSemaphore; //not sure if this is supposed to be xSemaphoreHandle_t, header files were unclear

/* Function Declarations */
char compare_array(char a[], char b[], int size);

/* Tasks */
void serialTask(void *parameters) { //Buffer and receive Serial Data
  while(1) {
    if(xSemaphoreTake(gSerialSemaphore, portMAX_DELAY) == pdTRUE) { //wait till semaphore is available
      char gIncomingChar = Serial.read(); //read message from serial

      if(gPackageFlag == true) // incoming character belongs to data
      {
        gCommsMsgBuff[iBuff] = gIncomingChar; //add to buffer
        iBuff++; //increment buffer size

        // Buffer Size is at maximum
        if(iBuff == BUFF_SIZE)
        {
          gPackageFlag = false; //this prevents task from stalling if \n is never received
          gProcessDataFlag = true; //ledTask uses this flag to process the result
        }
      }

      // check if start of message
      if(gIncomingChar == '$')
      {    
        gPackageFlag = true;  // beginning of message
        
        // Ensure buffer is clear
        for(int i=0; i<BUFF_SIZE; i++)
        {
          gCommsMsgBuff[i] = 0;
        }

        // reset index of array
        iBuff = 0;
      }

      // End of Message Check
      if((gIncomingChar == '\n') && gPackageFlag)
      {
        // Signal end of package
        gPackageFlag = false; //end reached
        gProcessDataFlag = true; //signal to other task that the message can be processed
      }
      
      xSemaphoreGive(gSerialSemaphore); //this releases the Semaphore "lock" so other tasks can use resources
    }
  }
}

//Determining whether to turn on a LED depending on the data received
void ledTask(void *parameters) {

  pinMode(LED, OUTPUT);

  while(1) {
    //serialTask will set this to true if a message has been received in its entirety
    if(gProcessDataFlag) {
      
      gProcessDataFlag = false; //flag reset
      
      //compares first three chars with "STR"
      if(compArray(gCommsMsgBuff, "STR", 3) == 1)
      {
        
        //turn on LED
        digitalWrite(LED, HIGH);
      }
      
      //compares first three chars with "STR" using array comparison function
      if(compArray(gCommsMsgBuff, "STP", 3) == 1)
      {
        // Turn off LED
        digitalWrite(LED, LOW);
      }
    }
  }
}


/* Function Definitions */
char compArray(char a[], char b[], int size) //Compares two arrays and returns char to determine if the arrays are equal
{
  int i;
  char result = 1;  // default: the arrays are equal
  
  for(i = 0; i<size; i++)
  {
    if(a[i]!=b[i])
    {
      result = 0; //arrays are not equal, returned to ledTask for message processing
      break;
    }
  }
  return result;
}


/* Main */
void setup() {
  Serial.begin(9600);
  gSerialSemaphore = xSemaphoreCreateMutex();
  
  xTaskCreate(
    serialTask,
    "Serial Task",
    128,
    NULL,
    2,
    NULL
  );
  
  xTaskCreate(
    ledTask,
    "LED Task",
    128,
    NULL,
    1,
    NULL
  );
  
  vTaskStartScheduler();
}
////////////////////////////////////////////////////////////////////////////////
void loop() {
  // empty, tasks are scheduled with RTOS
}

