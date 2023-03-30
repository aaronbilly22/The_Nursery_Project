// Include the Servo library 
#include <Servo.h> 
#define LIMIT_SWITCH_PIN 2
// Declare the Servo pin 
int servoPin = 4; 
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Serial.begin(9600);
   pinMode(LIMIT_SWITCH_PIN, INPUT);
   Servo1.attach(servoPin); 
}
void loop(){ 
   Servo1.write(0); 
   if (digitalRead(LIMIT_SWITCH_PIN) == HIGH)
   {
    Servo1.write(90); 
   delay(10000); 
   // Make servo go to 90 degrees 
   Servo1.write(0); 
   }
   
}