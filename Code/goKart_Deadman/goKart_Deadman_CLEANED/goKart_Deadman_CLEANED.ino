/*
  Refined code for DAU Go Kart project. This code is for the deadman portion of the Go Kart.

    -Place all Serial comms within an #ifdef/#endif pair.
    -Use defines for all non-changing values
    -Use all caps for all #defines

  Use a Mega for development

  Contriubutors:
    M. Pena


*/

// Declarations for use
#define DEADMAN_PIN_IN 11  //These variables are setup for the Deadman switch and braking operation of the go kart


// Included Libraries


// Global Classes/Stuctures


// Global variables
int deadmanValue = 0;


void setup() {

  Serial.begin(9600);  // Allows for the Serial Monitor to be used

  pinMode(DEADMAN_PIN_IN, INPUT);

}

void loop() {
  deadmanValue = pulseIn(DEADMAN_PIN_IN, HIGH);
  Serial.print("Dead Man Value: ");
  Serial.println(deadManValue);


  while (deadmanValue > 1600) {
    deadmanValue = pulseIn(DEADMAN_PIN_IN, HIGH);
    Serial.print("Deadman switch is pressed!");
    
  }
}
