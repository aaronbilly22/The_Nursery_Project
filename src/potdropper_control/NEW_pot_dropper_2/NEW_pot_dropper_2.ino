#include <Servo.h>
#define trigPin 10
#define echoPin 13
#define LIMIT_SWITCH_PIN_L A0
#define LIMIT_SWITCH_PIN_R A2  
#define servoPin1 A1
#define servoPin2 A3

const int stepPin1 = 2; 
const int dirPin1 =3; 

const int stepPin2 = 5; 
const int dirPin2 = 6; 
Servo Servo1; 
Servo Servo2;

void setup() {
  Serial.begin (9600);
  pinMode(LIMIT_SWITCH_PIN_L, INPUT);
  Servo1.attach(servoPin1); 
  pinMode(LIMIT_SWITCH_PIN_R, INPUT);
  Servo2.attach(servoPin2); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(11, OUTPUT);//stop conveyor
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
}

void loop() {
  digitalWrite(11, LOW); // Turn the LED STOP


  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  Servo1.write(0);
  Servo2.write(0); 
  Serial.println(digitalRead(LIMIT_SWITCH_PIN_L)&&digitalRead(LIMIT_SWITCH_PIN_R));

  if (digitalRead(LIMIT_SWITCH_PIN_L) == HIGH && digitalRead(LIMIT_SWITCH_PIN_R) == HIGH){
    Servo1.write(90);
    Servo2.write(90);
    delay(1000)
    for(int i=0;i<5;i++){
      digitalWrite(11, HIGH);
      delay(1000);
      digitalWrite(dirPin1,HIGH);
      digitalWrite(dirPin2,HIGH);
      for(int x = 0; x < 200; x++) {
        digitalWrite(stepPin1,HIGH); 
        digitalWrite(stepPin2,HIGH);
        delayMicroseconds(600); 
        digitalWrite(stepPin1,LOW); 
        digitalWrite(stepPin2,LOW); 
        delayMicroseconds(600);
      }
      delay(825);
      digitalWrite(11, LOW);
      delay(825);
      // Serial.println(digitalRead(LIMIT_SWITCH_PIN_L)&&digitalRead(LIMIT_SWITCH_PIN_R));
     Servo1.write(0); 
     Servo2.write(0);
   }

}
