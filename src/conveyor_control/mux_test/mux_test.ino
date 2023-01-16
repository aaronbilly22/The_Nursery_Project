//Normally open is side with 2; Top
//Normally closed is side with 2; Bottom
//Coil pos/neg are side with 3; Top and Bottom
//Common Output is side with 3; Middle

#define coil_1 3


void setup() {
  pinMode(coil_1, OUTPUT);

  Serial.begin(9600);


}

void loop() {


  digitalWrite(coil_1,1);
  delay(2000);
  digitalWrite(coil_1,0);
  delay(2000);
  
  
}
