/* This code does stuff



*/
// this is a test
// Declarations for use
#define THROTTLE_PIN_IN 10  // These variables are set up for the Throttle operation of the go kart
#define THROTTLE_PIN_OUT 12
#define THROTTLE_STOP_VALUE 0

#define STEER_PIN_IN 9  // These variables are set up for the Steering operation of the go kart
#define STEER_STOP_VALUE 1500
#define RIGHT_SWITCH_PIN 13
#define LEFT_SWITCH_PIN 6
#define STEER_SERVO_OUTPUT 5

#define DEADMAN_PIN_IN 11  //These variables are setup for the Deadman switch and braking operation of the go kart
#define BRAKE_RIGHT_OUTPUT_PIN 2
#define BRAKE_LEFT_OUTPUT_PIN 3
#define BRAKE_PIN_IN 8

#define BRAKE_ENCODER_PIN A15  // These variables are setup for using the encoder that exists on the braking linear acutator
#define BRAKE_OFF_POSITION_VALUE 30
#define BRAKE_ON_POSITION_VALUE 12
#define SHAFT_LENGTH 146
#define ENCODER_MAX 877
#define ENCODER_MIN 30
#define BRAKE_SPEED 255
#define BRAKE_STOP 0

// Included Libraries
#include <Servo.h>
#include <ezButton.h>

// Global Classes/Stuctures
ezButton limitSwitch1(RIGHT_SWITCH_PIN);
ezButton limitSwitch2(LEFT_SWITCH_PIN);
Servo steerServo;
Servo throttleServo;
// Global variables

int brakeValue = 0, brakePositionValue = 0, shaftPositionValue = 0, throttleValue = 0,
    throttleOutputValue = 0, steerValue = 0, steerOutputValue = 0, rightSwitchValue = 0,
    leftSwitchValue = 0, deadmanValue = 0;


void setup() {

  Serial.begin(9600);  // Allows for the Serial Monitor to be used

  limitSwitch1.setDebounceTime(50);  // Sets the time need to wait before the limit switches can take another input
  limitSwitch2.setDebounceTime(50);

  pinMode(STEER_PIN_IN, INPUT);  // Sets up the Steering, Brake, Deadman, Throttle pins to be used as inputs in the loop; all these values are read from the RC receiver
  pinMode(DEADMAN_PIN_IN, INPUT);
  pinMode(BRAKE_PIN_IN, INPUT);
  pinMode(THROTTLE_PIN_IN, INPUT);

  pinMode(BRAKE_RIGHT_OUTPUT_PIN, OUTPUT);  // Sets up the the Brake, Steering and Throttle pins to be used as outputs; these are wire to the siganl wires of the different servos
  pinMode(BRAKE_LEFT_OUTPUT_PIN, OUTPUT);
  steerServo.attach(STEER_SERVO_OUTPUT);
  throttleServo.attach(THROTTLE_PIN_OUT);
}

void loop() {

  getValues();  // runs the function below that runs all the funtions that read the new input values

  throttleServo.write(THROTTLE_STOP_VALUE);  //sets the servo for throttle to zero to stop the kart
  steerServo.write(STEER_STOP_VALUE);

  if (shaftPositionValue > BRAKE_ON_POSITION_VALUE) {  //runs and if else statement that will check if the brake linear acutator is engages on the break
    analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_SPEED);
    analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_STOP);
    delay(5);
  } else {
    analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_STOP);
    analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_STOP);
    delay(5);
  }

  while (deadmanValue > 1600) {  // runs the moving operation of the go cart; requires the the deadman button to be held for the following code to function

    getValues();  // runs again the function below to get all the new input values

    if ((brakeValue < 1400) && (shaftPositionValue < BRAKE_OFF_POSITION_VALUE)) {  //lines 82-93 negotiate whether or not the break switch is turned on and engages the break
      analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_STOP);
      analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_SPEED);
      delay(5);
    } else if ((brakeValue > 1500) && (shaftPositionValue > BRAKE_ON_POSITION_VALUE)) {
      analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_SPEED);
      analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_STOP);
      delay(5);
    } else {
      analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_STOP);
      analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_STOP);
      delay(5);
    }

    if (throttleValue < 1450) {  //lines 96-103 negotiate what the value of throttle input is and sends that analog signal to the throttle servo and is linear to the throttle trigger
      throttleServo.write(throttleOutputValue);
      delay(5);
    } else {
      throttleOutputValue = THROTTLE_STOP_VALUE;
      throttleServo.write(THROTTLE_STOP_VALUE);
      delay(5);
    }

    if ((steerOutputValue < 475) && (leftSwitchValue != 0)) {  //lines 105-114 check the values from the limit switches and the input for the steering servo and sends a full speed one way or another to the steering servo
      steerServo.write(600);
      delay(5);
    } else if ((steerOutputValue > 600) && (rightSwitchValue != 0)) {
      steerServo.write(2400);
      delay(5);
    } else {
      steerServo.write(1500);
      delay(20);
    }
  }
}

void getValues() { //this a function that reads all of the values from the the RC receivers and saves them to some global variables
  deadmanValue = pulseIn(DEADMAN_PIN_IN, HIGH);

  brakePositionValue = analogRead(BRAKE_ENCODER_PIN);
  brakeValue = pulseIn(BRAKE_PIN_IN, HIGH);
  shaftPositionValue = map(brakePositionValue, ENCODER_MIN, ENCODER_MAX, 0, SHAFT_LENGTH);

  throttleValue = pulseIn(THROTTLE_PIN_IN, HIGH);
  throttleOutputValue = map(throttleValue, 1450, 960, 0, 170);

  steerValue = pulseIn(STEER_PIN_IN, HIGH);
  steerOutputValue = map(steerValue, 2100, 1000, 0, 1000);

  limitSwitch1.loop();
  limitSwitch2.loop();
  leftSwitchValue = limitSwitch1.getState();
  rightSwitchValue = limitSwitch2.getState();

  Serial.print("throttleOutputValue:  ");
  Serial.println(throttleOutputValue);
  Serial.print("steerOutputValue:  ");
  Serial.println(steerOutputValue);
}
