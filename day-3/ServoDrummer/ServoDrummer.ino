#include <Servo.h>

int servoPin = 3;
Servo servo;
int angle = 90; // servo position in degrees

int full = 1000; 
int half = 500; 
int quarter = 250; 
int eighth = 125; 

void doBeat() {

  int delayVal = 60;

  servo.write(160); //down

  delay(delayVal);

  servo.write(100); //up

  delay(delayVal);

}


void setup() {
  servo.attach(servoPin);
  servo.write(angle);
}


void loop() {

  WilemTel(); // WilemTel drum routine

  delay(40);

}

void WilemTel() {
	int scoreSize = 200; 
	int notes[scoreSize] = { 
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
	for (int note=0 ; note < scoreSize; note++) {
		if (notes[note]>0) {
			doBeat(); 
			delay(notes[note]); 
		}
	}
}