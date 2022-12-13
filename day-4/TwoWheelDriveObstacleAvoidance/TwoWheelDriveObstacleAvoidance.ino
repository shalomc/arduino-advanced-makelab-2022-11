// Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN  13
// Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN     12
// maximum distance to expect object
#define MAX_DISTANCE 100

#include "TwoWheelDriveRobot.h"

#define MOTOR1_ENABLE 10
#define MOTOR1_PIN1 9
#define MOTOR1_PIN2 8

#define MOTOR2_PIN1 6
#define MOTOR2_PIN2 7
#define MOTOR2_ENABLE 5

#define SPEED 100

float weighed = 0;

TwoWheelDriveRobot robot(
  MOTOR1_ENABLE, MOTOR1_PIN1, MOTOR1_PIN2,
  MOTOR2_ENABLE, MOTOR2_PIN1, MOTOR2_PIN2);

void setup() {

}

void loop() {
  robot.forward(SPEED);
  int cm = ultrasonic_measure(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  weighed = 0.9 * weighed + 0.1 * cm;

  if (weighed < 15 && weighed >= 1) {
    robot.backward(SPEED);
    delay(1000);
    robot.drive(-SPEED, SPEED);
    delay(random(500, 1500));
    weighed = 0;
  }
  delay(50);
}


int ultrasonic_measure(int trigPin, int echoPin, int max_distance) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH, max_distance * 59);
  return duration / 59;
}
