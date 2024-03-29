#include <Servo.h>
#define trigPin 10
#define echoPin 13
#define LIMIT_SWITCH_PIN_L A0
#define LIMIT_SWITCH_PIN_R A2  
#define servoPin1 A1
#define servoPin2 A3
#define errorPin A4
#define conveyorPin 11

const int stepPin1 = 2; 
const int dirPin1 =3; 
const int stepPin2 = 5; 
const int dirPin2 = 6;

Servo Servo1; 
Servo Servo2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(LIMIT_SWITCH_PIN_L, INPUT);
  Servo1.attach(servoPin1); 
  pinMode(LIMIT_SWITCH_PIN_R, INPUT);
  Servo2.attach(servoPin2); 

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(conveyorPin, OUTPUT);//pin to control start/stop of conveyor
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(errorPin, OUTPUT); //pin to output error to screen
  Servo1.write(0); //servo down
  Servo2.write(90); //servo down
  digitalWrite(errorPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(conveyorPin, LOW); // start conveyor command

  //sensor control
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);

  //determines if tray is not below pot dropper and lowers arm switches
  if(distance >20 && distance <50){
    delay(850);
    Servo1.write(0);
    Servo2.write(90);
  }
    else digitalWrite(errorPin, HIGH); //send error message to screen

  //determine if arm switches are pressed by tray, begin pot dropping sequence
  if (digitalRead(LIMIT_SWITCH_PIN_L) == HIGH && digitalRead(LIMIT_SWITCH_PIN_R) == HIGH){
    digitalWrite(11, HIGH);
    delay(500);
    Servo1.write(90); //servo up
    Servo2.write(0); //servo up
    delay(500);
    //run stepper rotation for 5 sequences
    for(int i=0;i<5;i++){
      digitalWrite(11, HIGH); //stop conveyor command
      digitalWrite(dirPin1,HIGH); //
      digitalWrite(dirPin2,HIGH);
        //full rotation of stepper motors 
        for(int x = 0; x < 200; x++) {
          digitalWrite(stepPin1,HIGH); 
          digitalWrite(stepPin2,HIGH);
          delayMicroseconds(600); 
          digitalWrite(stepPin1,LOW); 
          digitalWrite(stepPin2,LOW); 
          delayMicroseconds(600); 
        }
      delay(890);
      digitalWrite(conveyorPin, LOW); //start conveyor command
      delay(890); //advance tray on conveyor for specified delay
    }
    //determines if tray is not below pot dropper and lowers arm switches
    if(distance >20 && distance <50){
      Servo1.write(0);
      Servo2.write(90);
    }

  }

}
