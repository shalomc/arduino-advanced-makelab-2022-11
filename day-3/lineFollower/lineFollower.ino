int ENA = 10;// Left Wheel
int ENB = 5;// Right Wheel
int aForward = 8;
int bForward = 6;
int carSpeed = 105;
void left(){
  analogWrite(ENA,LOW);
  analogWrite(ENB,carSpeed);
  digitalWrite(aForward,LOW);
  digitalWrite(bForward,HIGH);
}

void right(){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,LOW);
  digitalWrite(aForward,HIGH);
  digitalWrite(bForward,LOW);
}
void forward(){
  analogWrite(ENA,carSpeed);
  analogWrite(ENB,carSpeed);
  digitalWrite(aForward,HIGH);
  digitalWrite(bForward,HIGH);
}
void stopCar(){
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
}
void setup(){
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(aForward,OUTPUT);
  pinMode(bForward,OUTPUT);

  Serial.begin(9600);
  
  stopCar();
  
}



void loop(){
  int Light = analogRead(A0);
  int carSpeed = 105;
  Serial.println(Light);

  while(Light>35){
    Light =analogRead(A0);
    left();
    
    Serial.println(Light);
  }
  while(Light<26){
    Light = analogRead(A0);
    right();

    Serial.println(Light);
  }

  
}
