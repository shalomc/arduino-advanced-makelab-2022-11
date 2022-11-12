// based on AnalogInOutSerial
// Make the red light strobe according to the potentiometer state
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int MinHerz= 1;                 // minimum pulses/second
int MaxHerz= 10;               // maximum pulses/second
int frequencyDelay = 0; 
int frequency = 0; 
boolean DEBUG=false; 

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  frequency = map(sensorValue, 0, 1023, MinHerz, MaxHerz);
  frequencyDelay = 1000/frequency/2 ;
  analogWrite(analogOutPin, HIGH);
  delay(frequencyDelay);
  analogWrite(analogOutPin, LOW);
  delay(frequencyDelay);
  if (DEBUG) {
    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("\t delay = ");
    Serial.println(frequencyDelay);
  }
}
