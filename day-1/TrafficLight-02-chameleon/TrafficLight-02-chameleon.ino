// based on AnalogInOutSerial
// change between traffic lights according to the potentiometer state

// define the analog pins that your traffic light is connected to

const int pinRED = 9 ; 
const int pinYELLOW = 6 ;
const int pinGREEN = 7 ;

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the potentiometer
boolean DEBUG=false; 

struct trafficLight{
   String pinName; 
   int pinNumber;
   int pinValue;
};

trafficLight trafficLightsArray[3] = {
  {"Green", pinGREEN,0},
  {"Yellow", pinYELLOW,0},
  {"Red", pinRED,0}
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(1); 
  sensorValue = analogRead(analogInPin);
  setTrafficLightValues( sensorValue, trafficLightsArray ) ;
  for (int p=0; p<3;p++) {
    analogWrite(trafficLightsArray[p].pinNumber, trafficLightsArray[p].pinValue);
  }
/* The naive, explicit way
 * 
  analogWrite(pinGREEN, trafficLightsArray[0].pinValue);
  analogWrite(pinYELLOW, trafficLightsArray[1].pinValue);
  analogWrite(pinRED, trafficLightsArray[2].pinValue);
 */
  if (DEBUG) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    for (int p=0;p<3;p++) {
      Serial.print(" ; ");
      Serial.print(trafficLightsArray[p].pinName);
      Serial.print("= ");
      Serial.print(trafficLightsArray[p].pinValue);
    }
    Serial.println(); 
  }
}


void setTrafficLightValues(int sensorValue, trafficLight (&lightsArray)[3] ) {
  /*
   * First we map the sensor value to 0,1,2 
   * then we set the appropriate value in the lights array
   * The expression (p==mappedValue) will have the value of TRUE or FALSE, which are equivalent to 1 or 0. 
   */
  int mappedValue = map(sensorValue, 0, 1023, 0, 2) ; 
  for (int p=0; p<3;p++) {
    lightsArray[p].pinValue = 255 * (p==mappedValue); 
  }
}
