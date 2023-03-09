#include <ezButton.h>

const int led = 8;
const int trigPin = 9;
const int echoPin = 10;
const int relayConveyor = 7;

ezButton startButton(13);

long duration;
int distance;

void setup() {
  startButton.setDebounceTime(50);
  pinMode(led, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(relayConveyor, OUTPUT);

  Serial.begin(9600);
  
  while (!startButton.isPressed()){
    startButton.loop();
  }

}

void loop() {

  GetDistance();
  
  
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
