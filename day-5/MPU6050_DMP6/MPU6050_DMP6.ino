#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)

#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"

MPU6050 mpu;
#include "dmp_util.h"

bool blinkState = false;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dmp6Setup();
}

void loop() {
  if (dmp6Update()) {
    Serial.print("ypr\t");
    Serial.print(ypr[0] * 180 / M_PI);
    Serial.print("\t");
    Serial.print(ypr[1] * 180 / M_PI);
    Serial.print("\t");
    Serial.println(ypr[2] * 180 / M_PI);
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
  }
}
