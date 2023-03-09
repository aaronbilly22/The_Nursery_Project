const int relay = 3;
const int stop = 4;



void setup() {
  pinMode(relay, OUTPUT);
  pinMode(stop, INPUT);

  Serial.begin(9600);
}

void loop() {

  digitalWrite(relay,HIGH);
  if(digitalRead(stop)==HIGH){
    digitalWrite(relay,LOW);
  }
  
}
