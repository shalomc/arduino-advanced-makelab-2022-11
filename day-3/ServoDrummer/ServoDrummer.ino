#include <Servo.h>

#define MAX_SCORE_SIZE 300

int servoPin = 13;
Servo servo;


int initialAngle = 90; // servo position in degrees

// Beats
int full = 600;
int half = full / 2;
int quarter = half / 2;
int eighth = quarter / 2;

int tuneShuffle = 1;

void setup() {
  servo.attach(servoPin);
  servo.write(initialAngle);
}


void loop() {
  switch (tuneShuffle) {
    case 1:
      WilemTel();
      tuneShuffle++;
      break;
    case 2:
      Bolero();
      tuneShuffle++;
      break;
    default:
      tuneShuffle = 1;
      break;
  }
  delay(40);

}

void WilemTel() {
  // uninitialized array members are empty-initialized to 0
  // https://en.cppreference.com/w/c/language/array_initialization
  int beats[MAX_SCORE_SIZE] = {
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
  playScore(beats);
}


void Bolero() {
  int beats[MAX_SCORE_SIZE] = {
    full, quarter, quarter, quarter,
    full, quarter, quarter, quarter,
    full, full,
    full, quarter, quarter, quarter,
    full, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter
  };
  for (int i = 0 ; i < 2; i++) {
    playScore(beats);
  }
}

void doBeat() {
  int delayVal = 60;
  servo.write(160); //down
  delay(delayVal);
  servo.write(100); //up
  //  delay(delayVal);
}




void playScore(int (&beatsArray)[MAX_SCORE_SIZE] ) {
  // (sizeof(beatsArray)/sizeof(int))-1
  //will always be the number of items in the array
  for (int note = 0 ; note < (sizeof(beatsArray) / sizeof(int)) - 1 ; note++) {
    if (beatsArray[note] > 0) {
      doBeat();
      delay(beatsArray[note]);
    }
  }
}
