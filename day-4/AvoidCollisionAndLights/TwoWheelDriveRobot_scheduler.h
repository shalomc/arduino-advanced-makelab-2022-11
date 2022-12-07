#include <ArduinoQueue.h>
// requires installation via the library manager
// documentation https://github.com/EinarArnason/ArduinoQueue

#include "TwoWheelDriveRobot.h"

#define DEBUG false
#define QUEUE_SIZE 2  // we only need 1 atm :) 

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define TURN_LEFT 2
#define TURN_RIGHT 3

struct robotState_struct {
  int speed1;
  int speed2;
  int interval;
  // movement not used atm
  int movement ; // 0=forward ; 1=backward ; 2=turn left ; 3 = turn right
};

// queue of states to execute. We only want a single item in queue at a time
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
      int motor2Enable, int motor2Pin1, int motor2Pin2
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
    void schedule(int speed1, int speed2, int interval, int movement) {
      if (stateQueue.isEmpty()) {    // we don't have anything *planned* to do. Could use stateQueue.itemCount()
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
    void unschedule() {
      if (! stateQueue.isEmpty()) {    // we don't have anything *planned* to do
        robotState_struct dummy = stateQueue.dequeue( );
      }
    }

};
