int stepPin = 3;
int dirPin = 4;

void setup(){
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
}

void loop(){
    digitalWrite(dirPin,HIGH);

    for(int i=0;i<200;i++){
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
    }
    delay(1000);
}