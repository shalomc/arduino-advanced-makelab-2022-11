#include "flasher.h"
#include "space_beeper.h"

Flasher led1(12, 100, 400);
Flasher led2(13, 350, 350);
// Flasher led3(11, 111, 382);

SpaceBeeper beeper1(5, 100, 8);

void setup() {
  Serial.begin(115200);
}
 
void loop() {
  Serial.println(millis());
  led1.Update();
  led2.Update();
  // led3.Update();
  beeper1.Update();
  Serial.println(beeper1.noteCount); 
}
