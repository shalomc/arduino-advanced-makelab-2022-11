// Arduino pin tied to trigger pin on the ultrasonic sensor.
// #define TRIGGER_PIN  SCL
#define TRIGGER_PIN  SDA  
// Arduino pin tied to echo pin on the ultrasonic sensor.
// #define ECHO_PIN     12  
#define ECHO_PIN     SCL  
// maximum distance to expect object
#define MAX_DISTANCE 100


void setup() {
  Serial.begin(9600);
}

float weightCm = 0.0;

void loop() {
  int cm = ultrasonic_measure(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
  weightCm = 0.9 * weightCm + 0.1 * cm;
  Serial.println(String(cm) + "\t" + weightCm);
  // Serial.println(int(weightCm) );
  delay(50);
}

int ultrasonic_measure(int trigPin, int echoPin, int max_distance) {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH, max_distance * 59);
  return duration / 59;
}
