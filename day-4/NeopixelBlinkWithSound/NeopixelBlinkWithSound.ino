#include "neopixel_flasher.h"
#include "space_beeper.h"

#define NEOPIXEL_PIN 4
#define NUMPIXELS 16
const int intervalOfLight = 100; 
NeopixelFlasher neopixeler(NUMPIXELS, NEOPIXEL_PIN, intervalOfLight );
SpaceBeeper beeper1(50, 500, 6);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(millis());
  // neopixeler.Update();
  //  neopixeler.UpdateRainbow();
  neopixeler.UpdateTheaterRainbow();
  // beeper1.Update();
}
