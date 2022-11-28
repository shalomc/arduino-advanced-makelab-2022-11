#include "drummer_ns.h"

// size of array to keep the robot beats score


// parameters for the robot engines
// parameters for the drumming servo
#define SERVO_PIN_1  3
#define DIAGNOSTIC_MODE false



void setup() {
  Serial.begin(9600);
  Drum::initialise(SERVO_PIN_1);
}

void loop() {
  Drum::Bolero();
  int beats[DRUM_MAX_SCORE_SIZE] = {200, 300, 200, 300, 100, 100, 100, 500, 500, 500};
  for (int i = 0; i < 10; i++) {
    Drum::doBeat();
    delay(300);
  }

  for (int i = 0; i < 10; i++) {
    Drum::playScore(beats);
    delay(300);
  }

  delay(10);
}
