#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

boolean blinkState = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  setup_acc();
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(ax); Serial.print("\t");
  Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
//  Serial.print(gx); Serial.print("\t");
//  Serial.print(gy); Serial.print("\t");
//  Serial.print(gz); Serial.print("\t");
  Serial.println();
  blinkState = !blinkState;
  digitalWrite(LED_BUILTIN, blinkState);
}

void setup_acc() {
  Serial.println("Initializing I2C devices...");
  Wire.begin();
  accelgyro.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  Serial.println("ax ay az");
}
