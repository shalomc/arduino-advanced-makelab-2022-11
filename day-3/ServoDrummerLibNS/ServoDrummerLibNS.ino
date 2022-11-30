#include "drummer_ns.h"

// size of array to keep the robot beats score


// parameters for the robot engines
// parameters for the drumming servo
#define SERVO_PIN_1  13
#define DIAGNOSTIC_MODE false

int tuneShuffle = 1;
int beats01[DRUM_MAX_SCORE_SIZE] = {200, 300, 200, 300, 100, 100, 100, 500, 500, 500};


void setup() {
  Serial.begin(9600);
  Drum::initialise(SERVO_PIN_1);
}

void loop() {
  switch (tuneShuffle) {
    case 1:
      Drum::WilemTel();
      tuneShuffle++;
      break;
    case 2:
      Drum::Bolero();
      tuneShuffle++;
      break;
    case 3:
      Drum::playScore(beats01);
      tuneShuffle++;
      break;
    case 4:
      for (int i = 0; i < 10; i++) {
        Drum::doBeat();
        delay(Drum::half);
      }
      tuneShuffle++;
      break;
    default:
      tuneShuffle = 1;
      break;
  }
  delay(400);

}
