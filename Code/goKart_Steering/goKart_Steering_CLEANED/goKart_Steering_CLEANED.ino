/* This code does stuff



*/
// this is a test
// Declarations for use

#define STEER_PIN_IN 9  // These variables are set up for the Steering operation of the go kart
#define STEER_STOP_VALUE 1500
#define RIGHT_SWITCH_PIN 13
#define LEFT_SWITCH_PIN 6
#define STEER_SERVO_OUTPUT 5

// Included Libraries
#include <Servo.h>
#include <ezButton.h>

// Global Classes/Stuctures
ezButton limitSwitch1(RIGHT_SWITCH_PIN);
ezButton limitSwitch2(LEFT_SWITCH_PIN);
Servo steerServo;

// Global variables

int steerValue = 0, steerOutputValue = 0, rightSwitchValue = 0,
    leftSwitchValue = 0;


void setup() {

  Serial.begin(9600);  // Allows for the Serial Monitor to be used

  limitSwitch1.setDebounceTime(50);  // Sets the time need to wait before the limit switches can take another input
  limitSwitch2.setDebounceTime(50);

  pinMode(STEER_PIN_IN, INPUT);  // Sets up the Steering, Brake, Deadman, Throttle pins to be used as inputs in the loop; all these values are read from the RC receiver
  steerServo.attach(STEER_SERVO_OUTPUT);
}

void loop() {

  limitSwitch1.loop();
  limitSwitch2.loop();

  leftSwitchValue = limitSwitch1.getState();
  rightSwitchValue = limitSwitch2.getState();
  steerValue = pulseIn(STEER_PIN_IN, HIGH);
  steerOutputValue = map(steerValue, 2100, 1000, 0, 1000);


  if ((steerOutputValue < 475) && (leftSwitchValue != 0)) {  //lines 105-114 check the values from the limit switches and the input for the steering servo and sends a full speed one way or another to the steering servo
    steerServo.write(600);
    delay(5);
  } else if ((steerOutputValue > 600) && (rightSwitchValue != 0)) {
    steerServo.write(2400);
    delay(5);
  } else {
    steerServo.write(STEER_STOP_VALUE);
    delay(20);
  }
}
