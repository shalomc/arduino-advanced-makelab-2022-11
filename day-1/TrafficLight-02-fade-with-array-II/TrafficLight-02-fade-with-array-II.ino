#include <math.h>

// based on AnalogInOutSerial
// fade between traffic lights according to the potentiometer state
/*
  Use a C array of structs to manage the traffic lights .
   array[0] = green
   array[1] = yellow
   array[2] = red
  A C array is good to track a list of items, for example a list of pins to write to in order
*/

// define the analog pins that your traffic light is connected to

const int pinRED = 9 ;
const int pinYELLOW = 6 ;
const int pinGREEN = 7 ;
const int numOfPins = 3; 

struct trafficLight {
  String pinName;
  int pinNumber;
  int pinValue;
  float offsetX;
  float offsetY;
  int maxValue;
};



trafficLight trafficLightsArray[numOfPins] = {
  {"Green",  pinGREEN,  0, PI, 1, 256},
  {"Yellow", pinYELLOW, 0,  0, 0, 180},
  {"Red",    pinRED,    0, PI, 1, 150}
};

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the potentiometer
boolean DEBUG = true;
boolean DEBUGx2 = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1);
  sensorValue = analogRead(analogInPin);
  setTrafficLightValues( sensorValue, trafficLightsArray ) ;
  if (DEBUG) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
  }
  for (int p = 0; p < numOfPins; p++) {
    analogWrite(trafficLightsArray[p].pinNumber, trafficLightsArray[p].pinValue);
    if (DEBUG) {
      Serial.print(" ; ");
      Serial.print(trafficLightsArray[p].pinName);
      Serial.print("= ");
      Serial.print(trafficLightsArray[p].pinValue);
    }
  }
    if (DEBUG) {
      Serial.println();
    }
}


void setTrafficLightValues(int sensorValue, trafficLight (&lightsArray)[numOfPins] ) {
  const int funcMultiplier = 1000;
  const int maxFuncValue = 1000;
  int pi_map = map(sensorValue, 0, 1023, 0, int(PI*100)) ;

  if (DEBUGx2) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
  }
  for (int p = 0; p < numOfPins; p++) {
    int rangeFactor = (p == 0) * (sensorValue < 512) + (p == 1) + (p == 2) * (sensorValue >= 512);
    float funcValue = sin((float)pi_map / 100.0 + lightsArray[p].offsetX) + lightsArray[p].offsetY;
    int returnedValueRaw = (int)(funcValue * funcMultiplier ) * rangeFactor;
    int returnedValueAdjusted = map(returnedValueRaw, 0, maxFuncValue, 0, lightsArray[p].maxValue);
    lightsArray[p].pinValue = returnedValueAdjusted;
    if (DEBUGx2) {
      Serial.print("; ");
      Serial.print(lightsArray[p].pinName);
      Serial.print(" ; ");
      Serial.print("funcValue=");
      Serial.print(funcValue);
      Serial.print(" ; ");
      Serial.print("returnedValueRaw=");
      Serial.print(returnedValueRaw);
      Serial.print(" ; ");
      Serial.print("returnedValueAdjusted=");
      Serial.print(returnedValueAdjusted);
    }
  }
  if (DEBUG) {
    Serial.println();
  }


}
