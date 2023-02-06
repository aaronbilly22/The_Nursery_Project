// //Normally open is side with 2; Top
// //Normally closed is side with 2; Bottom
// //Coil pos/neg are side with 3; Top and Bottom
// //Common Output is side with 3; Middle

// #define coil_1 3



// void setup() {
//   pinMode(coil_1, OUTPUT);

//   Serial.begin(9600);
  


// }

// void loop() {


//   digitalWrite(coil_1,1);
//   delay(5000);
//   digitalWrite(coil_1,0);
//   delay(1000);
  
  
// }

#include <ezButton.h>
#define led 8

ezButton button2(10);

void setup() {
  button2.setDebounceTime(50);
  pinMode(led, OUTPUT);

  Serial.begin(9600);
  
  while (!button2.isPressed()){
    button2.loop();
  }

}

void loop() {

  digitalWrite(led,1);
  delay(1000);
  digitalWrite(led,0);
  delay(1000);
  
  
}

