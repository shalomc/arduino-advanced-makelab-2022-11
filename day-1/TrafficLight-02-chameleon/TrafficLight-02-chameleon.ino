// based on AnalogInOutSerial
// change between traffic lights according to the potentiometer state

// define the analog pins that your traffic light is connected to

const int pinRED = 9 ; 
const int pinYELLOW = 6 ;
const int pinGREEN = 7 ;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the potentiometer
boolean DEBUG=false; 

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
  if (DEBUG) {
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
  int mappedValue = map(sensorValue, 0, 1023, 0, 2) ; 
  for (int p=0; p<3;p++) {
    lightsArray[p] = 255 * (p==mappedValue); 
  }
}
