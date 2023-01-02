#include <ArduinoQueue.h>
// requires installation via the library manager
// documentation https://github.com/EinarArnason/ArduinoQueue

#include "TwoWheelDriveRobot.h"

#define DEBUG false
#define QUEUE_SIZE 1
// we only need 1 atm :)

#define STOP 0
#define MOVE_FORWARD 1
#define MOVE_BACKWARD 2
#define TURN_LEFT 3
#define TURN_RIGHT 4

struct robotState_struct {
  int speed1;
  int speed2;
  int interval;
  int movement ; // 0=stop; 1=forward ; 2=backward ; 3=turn left ; 4 = turn right
};

// queue of states to execute.
// by default we only want a single item in queue at a time
ArduinoQueue<robotState_struct> stateQueue(QUEUE_SIZE);

// inherit TwoWheelDriveRobot_Scheduler from TwoWheelDriveRobot
// and just add the scheduling stuff

class TwoWheelDriveRobot_Scheduler: public TwoWheelDriveRobot {
    // this is the structure definiton for the robot state.
    // structures can make the code more structured and easier to understand the context.
    robotState_struct robotState;    // actual global state stored here
    unsigned long previousMillis;  // previos time measurement

  public:
    TwoWheelDriveRobot_Scheduler(
      int motor1Enable, int motor1Pin1, int motor1Pin2,
      int motor2Enable, int motor2Pin1, int motor2Pin2, int qSize = QUEUE_SIZE
    ) : TwoWheelDriveRobot(
        motor1Enable, motor1Pin1, motor1Pin2,
        motor2Enable, motor2Pin1, motor2Pin2 ) {
      ;
      robotState.interval = 0;
      robotState = {0, 0, 0, 0};
    }
    ///////////////////////////////////////////////////////////////////
    /*
        Each incoming schedule event is placed on the queue, only if the queue is empty.

    */
    void schedule(int movement,  int interval, int speed1, int speed2 ) {
      if (stateQueue.itemCount() < QUEUE_SIZE ) {    // 0=we don't have anything *planned* to do.
        robotState_struct queuedState = { speed1, speed2, interval, movement };
        stateQueue.enqueue( queuedState );
        if (DEBUG ) {
          // debug mode
          Serial.print(" speed1=");
          Serial.print(speed1);
          Serial.print(" speed2=");
          Serial.print(speed2);
          Serial.print(" interval=");
          Serial.print(interval);
          Serial.print(" enqueue ");
          Serial.println();
        }
      }
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis > robotState.interval)  {
        if (DEBUG && !robotState.interval) {
          // debug mode
          Serial.print(" speed1=");
          Serial.print(robotState.speed1);
          Serial.print(" speed2=");
          Serial.print(robotState.speed2);
          Serial.print(" interval=");
          Serial.print(robotState.interval);
          Serial.println();
        }
        robotState = stateQueue.dequeue();
        /*
          robotState.interval = interval;
          robotState.speed1 = speed1;
          robotState.speed2 = speed2;
          robotState.movement = movement;
        */
        previousMillis = currentMillis;
        // this->drive(robotState.speed1, robotState.speed2);
      } else {  // end if (currentMillis - previousMillis > robotState.interval)
        ; // place holder for what to do if not
      }

      this->drive(robotState.speed1, robotState.speed2);
    }
    ///////////////////////////////////////////////////////////////////
    void schedule(int movement,  int interval, int speed ) {
      int speedLeft, speedRight = 0;
      if (stateQueue.itemCount() < QUEUE_SIZE ) {    // 0=we don't have anything *planned* to do.
        switch (movement) {
          case MOVE_FORWARD:
            speedLeft = speed;
            speedRight = speed;
            break;
          case MOVE_BACKWARD:
            speedLeft = -speed;
            speedRight = -speed;
            break;
          case TURN_LEFT:
            speedLeft = -speed;
            speedRight = speed;
            break;
          case TURN_RIGHT:
            speedLeft = speed;
            speedRight = -speed;
            break;
          case STOP:
            speedLeft = 0;
            speedRight = 0;
            break;
          default:
            speedLeft = 0;
            speedRight = 0;
            break;
        }
        robotState_struct queuedState = { speedLeft, speedRight, interval, movement };
        stateQueue.enqueue( queuedState );
        if (DEBUG ) {
          // debug mode
          Serial.print(" speed=");
          Serial.print(speed);
          Serial.print(" interval=");
          Serial.print(interval);
          Serial.print(" enqueue ");
          Serial.println();
        }
      }
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis > robotState.interval)  {
        if (DEBUG && !robotState.interval) {
          // debug mode
          Serial.print(" speed1=");
          Serial.print(robotState.speed1);
          Serial.print(" speed2=");
          Serial.print(robotState.speed2);
          Serial.print(" interval=");
          Serial.print(robotState.interval);
          Serial.println();
        }
        robotState = stateQueue.dequeue();
        /*
          robotState.interval = interval;
          robotState.speed1 = speed1;
          robotState.speed2 = speed2;
          robotState.movement = movement;
        */
        previousMillis = currentMillis;
        // this->drive(robotState.speed1, robotState.speed2);
      } else {  // end if (currentMillis - previousMillis > robotState.interval)
        ; // place holder for what to do if not
      }

      this->drive(robotState.speed1, robotState.speed2);
    }
    ///////////////////////////////////////////////////////////////////
    void unschedule() {
      if (! stateQueue.isEmpty()) {    // we don't have anything *planned* to do
        robotState_struct dummy = stateQueue.dequeue( );
      }
    }

};
