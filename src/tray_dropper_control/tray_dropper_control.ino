const int stepPin = 9;
const int dirPin = 8;
const int buttonPin = 13;
const int ms1 = 12;
const int ms2 = 11;
const int ms3 = 10;
const int trigPin = 3;
const int echoPin = 4;

long duration;
int distance;

int buttonState = 0;


void setup(){
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);

    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    pinMode(ms1,OUTPUT);
    pinMode(ms2,OUTPUT);
    pinMode(ms3,OUTPUT);

    digitalWrite(ms1,HIGH);
    digitalWrite(ms2,HIGH);
    digitalWrite(ms3,LOW);

    digitalWrite(dirPin,HIGH);
    Serial.begin(9600);
}

int GetDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void loop(){
    Serial.println(GetDistance());
    if(GetDistance() >= 20){
        for(int i=0;i<17*8;i++){
            digitalWrite(stepPin,HIGH);
            delayMicroseconds(700);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(700);
        }
        delay(10000);
    }
}
