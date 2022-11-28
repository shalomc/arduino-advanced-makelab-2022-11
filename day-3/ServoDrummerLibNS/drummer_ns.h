#ifndef drummer_ns_h
#define drummer_ns_h
#include <Servo.h>

#define DRUM_MAX_SCORE_SIZE 300
#define SERVO_INITIAL_ANGLE 90
#define DRUM_BASE_FULL_STOP_DURATION 600

/* How to use the drum library:

void setup(){  
  int pinNumber = 3;
  Drum::initialise(pinNumber);
  // or you can also overide the defaulty stop duration of 600 with your own value, like the following 2 lines show
  // int full_stop_duration = 600; 
  // Drum::initialise(pinNumber, full_stop_duration);
}

examples to put in your loop() function

  // produce 4 beats, use built-in delays
	Drum::doBeat();
	delay(Drum::full);
	Drum::doBeat();
	delay(Drum::half);
	Drum::doBeat();
	delay(Drum::quarter);
	Drum::doBeat();
	delay(Drum::eighth);

  // Drum a built-in score
	Drum::Bolero();
	delay(100);
	
  // Drum out your own score by prividing an array of beat stops in milliseconds
  int beats[DRUM_MAX_SCORE_SIZE] = {200, 300, 200, 300, 100, 100, 100, 500,500, 500};
  Drum::playScore(beats);

  // Shuffle between built-in scores
  for (int track=1; track<=2; track++) {
	  Drum::shuffle(track);
  }
*/
namespace Drum {
  Servo servo;
  int full ;
  int half ;
  int quarter ;
  int eighth ;
  
  void  initialise(int servoPin, int baseFullDuration = DRUM_BASE_FULL_STOP_DURATION) {
    // beats
    Drum::full = baseFullDuration;
    Drum::half = full / 2;
    Drum::quarter = half / 2;
    Drum::eighth = quarter / 2;
    Drum::servo.attach(servoPin );
    Drum::servo.write(SERVO_INITIAL_ANGLE);
    Serial.print("Initialised servo at pin ");
    Serial.println(servoPin);
  }
  ////////////////////////////////////////////////////////////////////////////
  void doBeat() {
    int delayVal = 60;
    servo.write(160); //down
    delay(delayVal);
    servo.write(100); //up
    //  delay(delayVal);
  }
  ////////////////////////////////////////////////////////////////////////////
  // void playScore(int (&beatsArray)[DRUM_MAX_SCORE_SIZE] ) {
  void playScore(int (&beatsArray)[DRUM_MAX_SCORE_SIZE] ) {
    // (sizeof(beatsArray)/sizeof(int))-1
    //will always be the number of items in the array
    for (int note = 0 ; note < (sizeof(beatsArray) / sizeof(int)) - 1 ; note++) {
      if (beatsArray[note] > 0) {
        doBeat();
        delay(beatsArray[note]);
      }
    }
  }
  ////////////////////////////////////////////////////////////////////////////
  void Bolero() {
    int beatsArray[DRUM_MAX_SCORE_SIZE] = {
      full, quarter, quarter, quarter,
      full, quarter, quarter, quarter,
      full, full,
      full, quarter, quarter, quarter,
      full, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter
    };
    Drum::playScore(beatsArray);
  }
  ////////////////////////////////////////////////////////////////////////////
  void WilemTel() {
    // uninitialized array members are empty-initialized to 0
    // https://en.cppreference.com/w/c/language/array_initialization
    int beatsArray[DRUM_MAX_SCORE_SIZE] = {
      eighth, eighth, quarter,
      eighth, eighth, quarter,
      eighth, eighth, quarter,  quarter,  quarter,
      eighth, eighth, quarter,
      eighth, eighth, quarter,
      eighth, eighth, quarter,  quarter,  quarter ,
      eighth, eighth, quarter,
      eighth, eighth, quarter,
      eighth, eighth, quarter,  quarter,  quarter,
      eighth, eighth, half,
      eighth, eighth, eighth, quarter, quarter, quarter
    };
    Drum::playScore(beatsArray);
  }
  ////////////////////////////////////////////////////////////////////////////
  void shuffle(int trackNumber) {
    switch (trackNumber) {
      case 1:
        Drum::WilemTel();
        break;
      case 2:
        Drum::Bolero();
        break;
      default:
  
        break;
    }
    delay(40);
  
  }
}

#endif // drummer_ns_h