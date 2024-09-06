/*
  Refined code for DAU Go Kart project. This code is for the throttle portion of the Go Kart.

    -Place all Serial comms within an #ifdef/#endif pair.
    -Use defines for all non-changing values
    -Use all caps for all #defines

  Use a Mega for development

  Contriubutors:
    M. Pena

    
*/

// Declarations for use
#define THROTTLE_PIN_IN 10  // These variables are set up for the Throttle operation of the go kart
#define THROTTLE_PIN_OUT 12
#define THROTTLE_STOP_VALUE 0


// Included Libraries
#include <Servo.h>          // Should be included in initial IDE download

// Global Classes/Stuctures
Servo throttleServo;

// Global variables
int throttleValue = 0,throttleOutputValue = 0;


void setup() {

  Serial.begin(9600);  // Allows for the Serial Monitor to be used
  
  pinMode(THROTTLE_PIN_IN, INPUT);            // Sets up the input pin from the RC receiver as an output
  throttleServo.attach(THROTTLE_PIN_OUT);     // Attaches the servo input signal to the previously declared 
}

void loop() {

  throttleValue = pulseIn(THROTTLE_PIN_IN, HIGH);
  throttleOutputValue = map(throttleValue, 1450, 960, 0, 170);

  Serial.print("throttleOutputValue:  ");
  Serial.println(throttleOutputValue);
 

    if (throttleValue < 1450) {  //lines 96-103 negotiate what the value of throttle input is and sends that analog signal to the throttle servo and is linear to the throttle trigger
      throttleServo.write(throttleOutputValue);
      delay(5);
    } else {
      throttleOutputValue = THROTTLE_STOP_VALUE;
      throttleServo.write(THROTTLE_STOP_VALUE);
      delay(5);
    }
}
