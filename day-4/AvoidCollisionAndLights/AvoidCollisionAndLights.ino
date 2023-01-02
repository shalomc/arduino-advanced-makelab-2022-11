// #define TWOWHEELDRIVE_DEBUG

#include "TwoWheelDriveRobot_scheduler.h"
#include "neopixel_scheduler.h"

#define DIAGNOSTIC_MODE false
#define DEBUG false

// Ultrasonic sensor parameters
#define TRIGGER_PIN  SDA
#define ECHO_PIN     SCL
// maximum distance to expect object
#define MAX_DISTANCE 100
#define TURNING_POINT 15
#define CHANGE_DIRECTION_DURATION 1000


// robot movement definitions
// #define MOTOR1_ENABLE 10
// #define MOTOR1_PIN1 9
// #define MOTOR1_PIN2 8
#define MOTOR1_ENABLE 3
#define MOTOR1_PIN1 2
#define MOTOR1_PIN2 1

#define MOTOR2_ENABLE 5
#define MOTOR2_PIN1 6
#define MOTOR2_PIN2 7

// robot adjustments
#define MOTOR1_GAIN 1.2
#define MOTOR2_GAIN 1
#define BASE_ROBOT_SPEED 50

// Neopixel parms
#define NEOPIXEL_PIN 4
#define NUMPIXELS 16

// set as variable because we may want to play with value
int intervalOfLight = 30;

// initialise
NeopixelFlasher neopixeler(NUMPIXELS, NEOPIXEL_PIN, intervalOfLight );
TwoWheelDriveRobot_Scheduler robot(MOTOR1_ENABLE, MOTOR1_PIN1, MOTOR1_PIN2, MOTOR2_ENABLE, MOTOR2_PIN1, MOTOR2_PIN2);

float weighed = 0.0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  neopixeler.UpdateTheaterRainbow();
  int cm = ultrasonic_measure(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  weighed = 0.9 * weighed + 0.1 * cm;

  // set movement defaults
  int baseSpeed1 = BASE_ROBOT_SPEED;
  int baseSpeed2 = BASE_ROBOT_SPEED;
  int speedLeft  = baseSpeed1 * calculateMotorGain(1, baseSpeed1);
  int speedRight = baseSpeed2 * calculateMotorGain(2, baseSpeed2);
  int durationDelay = 0; // no delay by default
  byte movement =  MOVE_FORWARD;

  if (!DIAGNOSTIC_MODE) { // diagnostic mode will cancel all movement
    if (weighed < TURNING_POINT && weighed >= 1) {  //  proximity alert!
      movement = MOVE_BACKWARD;
      durationDelay = CHANGE_DIRECTION_DURATION;
      robot.schedule(movement, durationDelay, -speedLeft, -speedRight  );
      // randomly turn either left or right
      int direction = random(0, 2);
      switch (direction) {
        case 0:
          speedLeft = -speedLeft;
          movement = TURN_LEFT;
          break;
        case 1:
          speedRight = -speedRight;
          movement = TURN_RIGHT;
          break;
      }
      durationDelay = random(CHANGE_DIRECTION_DURATION * 0.5, CHANGE_DIRECTION_DURATION * 1.5);
      weighed = 0;
    } else {  // no proximity alert!
    }
    robot.schedule(movement, durationDelay, speedLeft, speedRight  );
  } // end of non-diagnostic mode
  if (DEBUG) {
    // debug mode
    Serial.print(" speedleft=");
    Serial.print(speedLeft);
    Serial.print(" speedRight=");
    Serial.print(speedRight);
    Serial.println();
  }
  delay(10);
}


///////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////
int ultrasonic_measure(int trigPin, int echoPin, int max_distance) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  // speed of sound (cm/ms) = 0.0340 ; therefore 2* 1/0.0340 ~= 59
  int duration = pulseIn(echoPin, HIGH, max_distance * 59);
  return duration / 59;
}
