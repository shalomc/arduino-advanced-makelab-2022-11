// #define TWOWHEELDRIVE_DEBUG

#include "TwoWheelDriveRobot.h"

#define MOTOR1_ENABLE 10
#define MOTOR1_PIN1 9
#define MOTOR1_PIN2 8

#define MOTOR2_PIN1 6
#define MOTOR2_PIN2 7
#define MOTOR2_ENABLE 5

#define SPEED 100
#define DARKNESS_THRESHOLD 300
#define SENSOR1_PIN  A6
#define SENSOR2_PIN  A7
#define SENSOR1_GAIN  1
#define SENSOR2_GAIN  1.4

#define DIAGNOSTIC_MODE false

TwoWheelDriveRobot robot(MOTOR1_ENABLE, MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_ENABLE, MOTOR2_PIN1, MOTOR2_PIN2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // light sensors have different values at rest, so trying to equalise them 
  int sensor1Value = analogRead(SENSOR1_PIN) * SENSOR1_GAIN;
  int sensor2Value = analogRead(SENSOR2_PIN) * SENSOR2_GAIN;
  
  // The control is inspired by PID. 
  // The motors will increase or decrease their speed gradually based on the difference between the sensors readings (the error)
  int sensorDifference = sensor1Value - sensor2Value;
  int speedDifference = map(sensorDifference, -200, 200, -SPEED, SPEED);
  bool isLight = sensor1Value < DARKNESS_THRESHOLD && sensor2Value < DARKNESS_THRESHOLD; 
  int speedLeft = isLight * int((SPEED + speedDifference) / 2);
  int speedRight = isLight * int((SPEED - speedDifference) / 2);

  if (!DIAGNOSTIC_MODE) {
    robot.drive(speedLeft, speedRight);
  } else { 
    // debug mode
    Serial.print("sensor1=");
    Serial.print(sensor1Value);
    Serial.print(" sensor2=");
    Serial.print(sensor2Value);
    Serial.print(" diff=");
    Serial.print(sensorDifference);
    Serial.print(" speedleft=");
    Serial.print(speedLeft);
    Serial.print(" speedRight=");
    Serial.print(speedRight);
    Serial.println();
  }
  delay(10);
}
