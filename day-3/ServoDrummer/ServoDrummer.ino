#include <Servo.h>

#define MAX_SCORE_SIZE 300

int servoPin = 3;
Servo servo;


int initialAngle = 90; // servo position in degrees

// Beats 
int full = 600; 
int half = full/2; 
int quarter = half/2; 
int eighth = quarter/2; 

int tuneFlipper = 1; 

void setup() {
  servo.attach(servoPin);
  servo.write(initialAngle);
}


void loop() {
	switch (tuneShuffle) {
		case 1: 
			WilemTel();
			break;
		case 2: 
			Bolero();
			break;
		default: 
			tuneFlipper=0; 
			break; 
	}	
	tuneFlipper++; 
	delay(40);

}

void WilemTel() {
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
		full, quarter, quarter, quarter, quarter, quarter, quarter, quarter, quarter,quarter
	};
	for (int i=0 ; i<2; i++) {
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




void playScore(int (&notesArray)[MAX_SCORE_SIZE] ) {
	// (sizeof(notesArray)/sizeof(int))-1 
	//will always be the number of items in the array
	for (int note=0 ; note < (sizeof(notesArray)/sizeof(int)) - 1 ; note++) {
		if (notesArray[note]>0) {
			doBeat(); 
			delay(notesArray[note]); 
		}
	}
}


