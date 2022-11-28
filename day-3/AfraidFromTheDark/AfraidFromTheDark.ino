
// #define TWOWHEELDRIVE_DEBUG

#include "TwoWheelDriveRobot.h"
#include "drummer_ns.h"

#define SEEK_ATTENTION true

#define MOTOR1_ENABLE 10
#define MOTOR1_PIN1 9
#define MOTOR1_PIN2 8
#define MOTOR1_GAIN 1

#define MOTOR2_PIN1 6
#define MOTOR2_PIN2 7
#define MOTOR2_ENABLE 5
#define MOTOR2_GAIN 1

#define BASE_ROBOT_SPEED 100

#define DARKNESS_THRESHOLD 300
#define SENSOR1_PIN  A6
#define SENSOR2_PIN  A7
#define SENSOR1_GAIN  1
#define SENSOR2_GAIN  1.4

#define SERVO_PIN_1 3
#define DIAGNOSTIC_MODE false
#define DEBUG true

TwoWheelDriveRobot robot(MOTOR1_ENABLE, MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_ENABLE, MOTOR2_PIN1, MOTOR2_PIN2);

void setup() {
  Serial.begin(9600);
  if (SEEK_ATTENTION) { 
    Drum::initialise( SERVO_PIN_1);
  }
}

void loop() {
  // light sensors have different values at rest, so trying to equalise them
  int sensor1Value = analogRead(SENSOR1_PIN) * SENSOR1_GAIN;
  int sensor2Value = analogRead(SENSOR2_PIN) * SENSOR2_GAIN;

  // The control is inspired by PID.
  // The motors will increase or decrease their speed gradually based on the difference between the sensors readings (the error)
  int sensorDifference = sensor1Value - sensor2Value;
  int speedDifference = map(sensorDifference, -200, 200, -BASE_ROBOT_SPEED, BASE_ROBOT_SPEED);
  bool isLight = sensor1Value < DARKNESS_THRESHOLD && sensor2Value < DARKNESS_THRESHOLD;
  int baseSpeed1 = int((BASE_ROBOT_SPEED + speedDifference) / 2);
  int baseSpeed2 = int((BASE_ROBOT_SPEED - speedDifference) / 2);
  int speedLeft  = isLight * baseSpeed1 * calculateMotorGain(1, baseSpeed1);
  int speedRight = isLight * baseSpeed2 * calculateMotorGain(2, baseSpeed2);

  //  int speedLeft = isLight * int((BASE_ROBOT_SPEED + speedDifference) / 2);
  //  int speedRight = isLight * int((BASE_ROBOT_SPEED - speedDifference) / 2);


  if (!isLight && SEEK_ATTENTION ) {
    Serial.print("attention!! ");
    seekAttention();
    delay(300);
  }

  if (!DIAGNOSTIC_MODE) {
    robot.drive(speedLeft, speedRight);
  } 
  if (DEBUG) {
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

void seekAttention() {
  // uninitialized array members are empty-initialized to 0
  // https://en.cppreference.com/w/c/language/array_initialization
  int beats[DRUM_MAX_SCORE_SIZE] = {Drum::quarter, Drum::quarter, Drum::eighth, Drum::eighth, Drum::half};
  Drum::playScore(beats);
}


float calculateMotorGain(int motor, int currentSpeed) {
  // placeholder for possible non-linear gain complexity
  switch (motor) {
    case 1:
      return float(MOTOR1_GAIN);
      break;
    case 2:
      return float(MOTOR2_GAIN);
      break;
    default:
      return float(1.0);
      break;
  }
}
