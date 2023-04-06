//////////////////////////////////////////////////////////////////
///////////////////// INTEGRATION LAB-03 /////////////////////////
//////////////////////////////////////////////////////////////////

//L298 Motor Controller Pin Assignment
// Motor A pin connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B pin connections
int enB = 3;
int in3 = 4;
int in4 = 5;

void setup() {
  // Set all motor controller pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initial state - Turn off all the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {

  // move forward with 60% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, 153);
  analogWrite(enB, 153);

  // Rotate left and right wheels in clockwise direction - Move forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(2000); // move forward for 2 seconds

  // turn with 30% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, 77);
  analogWrite(enB, 77);

  // Rotate left wheel clockwise and right wheel in anti-clockwise direction - Spin clockwise/Turn right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(1000); // move forward for 1 second

  // turn with 30% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, 77);
  analogWrite(enB, 77);

  // Rotate left wheel anti-clockwise and right wheel in clockwise direction - Spin anti-clockwise/Turn left
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(1000); // move forward for 1 second

  // move backward with 60% speed - For PWM values varies between 0 (no speed) and 255 (full speed)
  analogWrite(enA, 153);
  analogWrite(enB, 153);

  // Rotate left and right wheels in anti-clockwise direction - Move backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  delay(2000); // move backward for 2 seconds
}