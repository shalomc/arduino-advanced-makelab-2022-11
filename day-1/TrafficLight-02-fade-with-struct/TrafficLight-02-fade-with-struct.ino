#include <math.h>

// based on AnalogInOutSerial
// fade between traffic lights according to the potentiometer state
/* 
 Use a C struct to manage the traffic lights 
 A C struct is good to track an object with well known and distinct values
*/

// define the analog pins that your traffic light is connected to
const int pinRED = 9 ; 
const int pinYELLOW = 6 ;
const int pinGREEN = 7 ;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the potentiometer
boolean DEBUG=true; 
boolean DEBUGx2=false; 

// Is it better to use a struct instead of array?

struct trafficLight{
   int green;
   int yellow;
   int red;
};

trafficLight traffic_light; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1); 
  sensorValue = analogRead(analogInPin);
  traffic_light = setTrafficLightValues( sensorValue ) ;
  analogWrite(pinGREEN, traffic_light.green);
  analogWrite(pinYELLOW, traffic_light.yellow);
  analogWrite(pinRED, traffic_light.red);
  if (false) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print(" green= ");
    Serial.print(traffic_light.green);
    Serial.print(" yellow= ");
    Serial.print(traffic_light.yellow);
    Serial.print(" red= ");
    Serial.println(traffic_light.red);
  }
}


trafficLight setTrafficLightValues(int sensorValue ) {
  int pi_map = map(sensorValue, 0, 1023, 0, 314) ; 
  const int maxGreen = 256; 
  const int maxYellow = 180; 
  const int maxRed = 150; 
  trafficLight lightsArray; 

  float sinGreen = sin((float)pi_map/100.0 + 2.0 * PI / 2.0)+1; 
  float sinYellow = sin((float)pi_map/100.0 + 0.0 * PI / 2.0);
  float sinRed = sin((float)pi_map/100.0 + 2.0 * PI / 2.0)+1;

  int valueGreen = (int)(sinGreen*1000.0) * (sensorValue < 512); 
  int valueYellow = (int)(sinYellow*1000.0) * true ; 
  int valueRed = (int)(sinRed*1000.0) *  (sensorValue >= 512); 

  lightsArray.green = map(valueGreen,0,1000,0,maxGreen); 
  lightsArray.yellow = map(valueYellow,0,1000,0,maxYellow); 
  //lightsArray.yellow = maxYellow-int(abs(int(valueYellow-512))/int(512/maxYellow)); 
  lightsArray.red = map(valueRed,0,1000,0,maxRed);  
  
  if (DEBUGx2) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print(" sinGreen= ");
    Serial.print(sinGreen);
    Serial.print(" valueGreen= ");
    Serial.print(valueGreen);
    Serial.print(" green= ");
    Serial.print(lightsArray.green);
    //Serial.print(" sinYellow= ");
    //Serial.print(sinYellow);
    //Serial.print(" valueYellow= ");
    //Serial.print(valueYellow);
    Serial.print(" yellow= ");
    Serial.print(lightsArray.yellow);
    Serial.print(" sinRed= ");
    Serial.println(sinRed);
    Serial.print(" valueRed= ");
    Serial.println(valueRed);
    Serial.print(" red= ");
    Serial.println(lightsArray.red);
  }
  return lightsArray;
}
