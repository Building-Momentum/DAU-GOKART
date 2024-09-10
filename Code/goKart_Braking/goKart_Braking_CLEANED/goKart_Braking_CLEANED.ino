/*
  Refined code for DAU Go Kart project. This code is for the Braking portion of the Go Kart.

    -Place all Serial comms within an #ifdef/#endif pair.
    -Use defines for all non-changing values
    -Use all caps for all #defines

  Use a Mega for development

  Contriubutors:
    M. Pena


*/

// Declarations for use

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

// Global Classes/Stuctures

// Global variables

int brakeValue = 0, brakePositionValue = 0, shaftPositionValue = 0;


void setup() {

  Serial.begin(9600);  // Allows for the Serial Monitor to be used

  pinMode(BRAKE_PIN_IN, INPUT);

  pinMode(BRAKE_RIGHT_OUTPUT_PIN, OUTPUT);  // Sets up the the Brake, Steering and Throttle pins to be used as outputs; these are wire to the siganl wires of the different servos
  pinMode(BRAKE_LEFT_OUTPUT_PIN, OUTPUT);
}

void loop() {

  brakePositionValue = analogRead(BRAKE_ENCODER_PIN);
  brakeValue = pulseIn(BRAKE_PIN_IN, HIGH);
  shaftPositionValue = map(brakePositionValue, ENCODER_MIN, ENCODER_MAX, 0, SHAFT_LENGTH);

  Serial.print("Brake Value: ");
  Serial.print(brakeValue);
  Serial.print(" ");
  Serial.print("Shaft Position: ");
  Serial.print(shaftPositionValue);
  Serial.print(" ");
  Serial.print("Brake State: ");


  if ((brakeValue < 1400) && (shaftPositionValue < BRAKE_OFF_POSITION_VALUE)) {  //lines 82-93 negotiate whether or not the break switch is turned on and engages the break
    Serial.println("Disengaging");
    analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_STOP);
    analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_SPEED);
    delay(5);
  } else if ((brakeValue > 1500) && (shaftPositionValue > BRAKE_ON_POSITION_VALUE)) {
    Serial.println("Engaging");
    analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_SPEED);
    analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_STOP);
    delay(5);
  } else {
    Serial.println("OFF");
    analogWrite(BRAKE_RIGHT_OUTPUT_PIN, BRAKE_STOP);
    analogWrite(BRAKE_LEFT_OUTPUT_PIN, BRAKE_STOP);
    delay(5);
  }
}
