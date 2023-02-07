#define trigPin 10
#define echoPin 13
const int stepPin1 = 2; 
const int dirPin1 =3; 
const int stepPin2 = 5; 
const int dirPin2 = 6; 

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(11, OUTPUT);//stop LED
  pinMode(12, OUTPUT);//Green LED
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
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);

  if (distance < 5){
  digitalWrite(11, HIGH);
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
  delay(500);
  digitalWrite(11, LOW);
  delay(500);
  } 

}
