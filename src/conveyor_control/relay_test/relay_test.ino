const int relayPin = 3;
const int stopPin = 4;



void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(stopPin, INPUT);

  Serial.begin(9600);

}

void loop() {


  if(digitalRead(stopPin)==HIGH){
    digitalWrite(relayPin, LOW);
  }
  else{
    digitalWrite(relayPin, HIGH);
  }
 
  
}
