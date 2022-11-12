#include <math.h>

// based on AnalogInOutSerial
// fade between traffic lights according to the potentiometer state
/* 
 Use a C array to manage the traffic lights . 
   array[0] = green
   array[1] = yellow
   array[2] = red
 A C array is good to track a list of items, for example a list of pins to write to in order
*/

// define the analog pins that your traffic light is connected to

const int pinRED = 9 ; 
const int pinYELLOW = 6 ;
const int pinGREEN = 7 ;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the potentiometer
boolean DEBUG=true; 

// Is it better to use a struct instead of array?

int trafficLightsArray[3]; 
/* 0 = green
 * 1 = yellow
 * 2 = red
 */

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1); 
  sensorValue = analogRead(analogInPin);
  setTrafficLightValues( sensorValue, trafficLightsArray ) ;
  analogWrite(pinGREEN, trafficLightsArray[0]);
  analogWrite(pinYELLOW, trafficLightsArray[1]);
  analogWrite(pinRED, trafficLightsArray[2]);
  if (false) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print(" green= ");
    Serial.print(trafficLightsArray[0]);
    Serial.print(" yellow= ");
    Serial.print(trafficLightsArray[1]);
    Serial.print(" red= ");
    Serial.println(trafficLightsArray[2]);
  }
}


void setTrafficLightValues(int sensorValue, int (&lightsArray)[3] ) {
  int pi_map = map(sensorValue, 0, 1023, 0, 314) ; 

  const int maxGreen = 256; 
  const int maxYellow = 180; 
  const int maxRed = 150; 

  float sinGreen = sin((float)pi_map/100.0 + 2.0 * PI / 2.0)+1; 
  float sinYellow = sin((float)pi_map/100.0 + 0.0 * PI / 2.0);
  float sinRed = sin((float)pi_map/100.0 + 2.0 * PI / 2.0)+1;

  int valueGreen = (int)(sinGreen*1000.0) * (sensorValue < 512); 
  int valueYellow = (int)(sinYellow*1000.0) * true ; 
  int valueRed = (int)(sinRed*1000.0) *  (sensorValue >= 512); 

  lightsArray[0] = map(valueGreen,0,1000,0,maxGreen); 
  lightsArray[1] = map(valueYellow,0,1000,0,maxYellow); 
  //lightsArray[1] = maxYellow-int(abs(int(valueYellow-512))/int(512/maxYellow)); 
  lightsArray[2] = map(valueRed,0,1000,0,maxRed);  
  
  if (DEBUG) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print(" sinGreen= ");
    Serial.print(sinGreen);
    Serial.print(" valueGreen= ");
    Serial.print(valueGreen);
    Serial.print(" green= ");
    Serial.print(lightsArray[0]);
    //Serial.print(" sinYellow= ");
    //Serial.print(sinYellow);
    //Serial.print(" valueYellow= ");
    //Serial.print(valueYellow);
    Serial.print(" yellow= ");
    Serial.print(lightsArray[1]);
    Serial.print(" sinRed= ");
    Serial.println(sinRed);
    Serial.print(" valueRed= ");
    Serial.println(valueRed);
    Serial.print(" red= ");
    Serial.println(lightsArray[2]);
  }
}
