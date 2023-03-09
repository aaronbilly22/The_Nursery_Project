int stepPin = 9;
int dirPin = 8;
int buttonState = 0;
int buttonPin = 13;
int ms1 = 10;
int ms2 = 11;
int ms3 = 12;

void setup(){
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    pinMode(buttonPin,INPUT);
    pinMode(ms1,OUTPUT);
    pinMode(ms2,OUTPUT);
    pinMode(ms3,OUTPUT);
    Serial.begin(9600);
}

void loop(){
    buttonState = digitalRead(buttonPin);
    digitalWrite(dirPin,HIGH);

    digitalWrite(ms1,HIGH);
    digitalWrite(ms2,HIGH);
    digitalWrite(ms3,LOW);

    if(buttonState == HIGH){
    
        for(int i=0;i<17*8;i++){
            digitalWrite(stepPin,HIGH);
            delayMicroseconds(700);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(700);
        }
        Serial.print("YESSSIRR\n");
        delay(1000);
        }
    
    else{
        Serial.print("NOOOOO\n");
    }

}
