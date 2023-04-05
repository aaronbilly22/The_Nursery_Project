// Include the Servo library 
#include <Servo.h> 
#define LIMIT_SWITCH_PIN_L A0
#define LIMIT_SWITCH_PIN_R A2
#define servoPin1 A1
#define servoPin2 A3
// Declare the Servo pin 
// int servoPin1 = 1; 
// int servoPin2 = 3;
// Create a servo object 
Servo Servo1; 
Servo Servo2;
void setup() { 
   // We need to attach the servo to the used pin number 
   Serial.begin(9600);
   pinMode(LIMIT_SWITCH_PIN_L, INPUT);
   Servo1.attach(servoPin1); 
   pinMode(LIMIT_SWITCH_PIN_R, INPUT);
   Servo2.attach(servoPin2); 
}
void loop(){ 
   Servo1.write(0);
   Servo2.write(0); 
   Serial.println(digitalRead(LIMIT_SWITCH_PIN_L)&&digitalRead(LIMIT_SWITCH_PIN_R));
   if (digitalRead(LIMIT_SWITCH_PIN_L) == HIGH && digitalRead(LIMIT_SWITCH_PIN_R) == HIGH)
   {
      Serial.println(digitalRead(LIMIT_SWITCH_PIN_L)&&digitalRead(LIMIT_SWITCH_PIN_R));
    Servo1.write(90);
    Servo2.write(90);   
   delay(10000); 
   // Make servo go to 90 degrees 
   Servo1.write(0); 
   Servo2.write(0);
   }
   
}