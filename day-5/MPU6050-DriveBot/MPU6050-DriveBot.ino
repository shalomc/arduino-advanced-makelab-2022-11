#include <PID_v1.h>
#include "Wire.h"
#include "MPU6050_6Axis_MotionApps20.h"
// #define TWOWHEELDRIVE_DEBUG

#include "TwoWheelDriveRobot.h"

#define MOTOR1_ENABLE 10
#define MOTOR1_PIN1 8
#define MOTOR1_PIN2 9

#define MOTOR2_PIN1 7
#define MOTOR2_PIN2 6
#define MOTOR2_ENABLE 5

#define SPEED 100

TwoWheelDriveRobot robot(MOTOR1_ENABLE, MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_ENABLE, MOTOR2_PIN1, MOTOR2_PIN2);

#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)

MPU6050 mpu;
#include "dmp_util.h"

bool blinkState = false;
double Setpoint, Input, Output;
int realSetpoint = 75;
double Kp=4, Ki=1, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  dmp6Setup();
  myPID.SetOutputLimits(-255, 255);
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  if (dmp6Update()) {
    int currentReading = ypr[0] * 180 / M_PI + 180;
    int error = getError(currentReading, realSetpoint);
//    Serial.print("currentReading: ");
//    Serial.print(currentReading);
//    Serial.print(" realSetpoint: ");
//    Serial.print(realSetpoint);
//    Serial.print(" error: ");
//    Serial.print(error);
//    Serial.println();
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);

    Input = 0;
    Setpoint = error;
    myPID.Compute();
    
    Serial.print(error);
    Serial.print("\t");
    Serial.print(Output);
    Serial.println();

    robot.drive(Output, -Output);
    // robot.drive(100 + Output/2, 100 - Output/2);
  }
}


int getError(int in, int sp) {
  if(in == sp) {
    return 0;
  }
  boolean done = false;
  int cw = in;
  int ccw = in;
  int counter = 0;
  while (!done) {
    cw++;
    if(cw == 360) {
      cw = 0;
    }
    ccw--;
    if(ccw == -1) {
      ccw = 359;
    }
    counter++;
    if (cw == sp || ccw == sp) {
      done = true;
    }
  }
  if(cw == sp) {
    return counter;
  }
  else {
    return -counter;
  }
}
