//----------------------------------------Include Library
#include <Adafruit_GFX.h>    //--> Core graphics library
#include <Adafruit_TFTLCD.h> //--> Hardware-specific library
#include <TouchScreen.h>
//----------------------------------------

//----------------------------------------
#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif
//----------------------------------------

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7

// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).
//   D0 connects to digital pin 22
//   D1 connects to digital pin 23
//   D2 connects to digital pin 24
//   D3 connects to digital pin 25
//   D4 connects to digital pin 26
//   D5 connects to digital pin 27
//   D6 connects to digital pin 28
//   D7 connects to digital pin 29

// For the Arduino Due, use digital pins 33 through 40
// (on the 2-row header at the end of the board).
//   D0 connects to digital pin 33
//   D1 connects to digital pin 34
//   D2 connects to digital pin 35
//   D3 connects to digital pin 36
//   D4 connects to digital pin 37
//   D5 connects to digital pin 38
//   D6 connects to digital pin 39
//   D7 connects to digital pin 40

//----------------------------------------Pin configuration and initialization for Touchscreen
#define YP A2 //--> must be an analog pin, use "An" notation!
#define XM A1 //--> must be an analog pin, use "An" notation!
#define YM 6  //--> can be a digital pin
#define XP 7  //--> can be a digital pin

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
//----------------------------------------

//----------------------------------------Pin configuration and initialization for LCD TFT
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//----------------------------------------

//----------------------------------------Defines colors
// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define BLACKM  0x18E3
//----------------------------------------

//----------------------------------------The results of the x and y point calibration on the touch screen
#define TS_MINX 158
#define TS_MINY 127
#define TS_MAXX 895
#define TS_MAXY 872
//----------------------------------------

//----------------------------------------Variable for detecting touch screen when touched
#define MINPRESSURE 10
#define MAXPRESSURE 1000
//----------------------------------------

//----------------------------------------Defines an LED pin
#define LED 12
//----------------------------------------

//----------------------------------------Button location at point x and y
int BtnGreenX = 30;
int BtnGreenY = 30;
int BtnRedX = 200;
int BtnRedY = 30;
//----------------------------------------

//========================================================================VOID SETUP()
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  tft.reset();

  // *** SPFD5408 change -- Begin
//  uint16_t identifier = tft.readID();
//
//  if(identifier == 0x9325) {
//    Serial.println(F("Found ILI9325 LCD driver"));
//  } else if(identifier == 0x9328) {
//    Serial.println(F("Found ILI9328 LCD driver"));
//  } else if(identifier == 0x7575) {
//    Serial.println(F("Found HX8347G LCD driver"));
//  } else if(identifier == 0x9341) {
//    Serial.println(F("Found ILI9341 LCD driver"));
//  } else if(identifier == 0x8357) {
//    Serial.println(F("Found HX8357D LCD driver"));
//  } else {
//    Serial.print(F("Unknown LCD driver chip: "));
//    Serial.println(identifier, HEX);
//    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
//    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
//    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
//    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
//    Serial.println(F("Also if using the breakout, double-check that all wiring"));
//    Serial.println(F("matches the tutorial."));
//    return;
//  }
//
//  tft.begin(identifier);

  tft.begin(0x9341); //--> SPFD5408/ILI9341

  tft.setRotation(135); //--> Need for the Mega, please changed for your choice or rotation initial

  tft.fillScreen(WHITE); //--> TFT LCD background color

  pinMode(13, OUTPUT);  

  pinMode(LED, OUTPUT);

  DrawButtonGreen(BtnGreenX,BtnGreenY);
  DrawButtonRed(BtnRedX, BtnRedY);

  tft.setTextSize(3);
  tft.setTextColor(BLUE, WHITE);
  tft.setCursor(100, 160);
  tft.print("LED OFF");
}
//========================================================================

//========================================================================VOID LOOP()
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  //pinMode(YM, OUTPUT);

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
  
  int y_set_rotatoon_135 = map(p.x, 0, 240, 0, tft.height());
  int x_set_rotatoon_135 = map(tft.width() - p.y, 0, 320, 0, tft.width());

  //----------------------------------------Use the code lines below to display the x, y and z points on the touch screen
//  tft.setTextSize(2);
//  tft.setTextColor(RED, WHITE);
//
//  tft.setCursor(0, 55 + 70);
//  tft.print("TSPoint");
//  
//  tft.setCursor(0, 85 + 70);
//  tft.print("X:");
//  tft.print(x_set_rotatoon_135);
//  tft.print("   ");
//
//  tft.setCursor(0, 115 + 70);
//  tft.print("Y:");
//  tft.print(y_set_rotatoon_135);
//  tft.print("   ");
//
//  tft.setCursor(0, 145 + 70);
//  tft.print("Z:");
//  tft.print(p.z);
//  tft.print("   ");
  //----------------------------------------

  //----------------------------------------Conditions for detecting touch screen when touched
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    
    //----------------------------------------Condition to detect when the Green Button (Button to turn on LED) is touched and the command
    if (x_set_rotatoon_135 > BtnGreenX && x_set_rotatoon_135 < (BtnGreenX+84) && y_set_rotatoon_135 > BtnGreenY && y_set_rotatoon_135 < (BtnGreenY+84)) {
      tft.setTextSize(3);
      tft.setTextColor(BLUE, WHITE);
      tft.setCursor(100, 160);
      tft.print("LED ON ");

      digitalWrite(LED, HIGH);
      
      DrawButtonGreenPress(BtnGreenX, BtnGreenY);
      delay(100);
      DrawButtonGreen(BtnGreenX,BtnGreenY);
    }
    //----------------------------------------

    //----------------------------------------Condition to detect when the Red Button (Button to turn off LED) is touched and the command
    if (x_set_rotatoon_135 > BtnRedX && x_set_rotatoon_135 < (BtnRedX+84) && y_set_rotatoon_135 > BtnRedY && y_set_rotatoon_135 < (BtnRedY+84)) {
      tft.setTextSize(3);
      tft.setTextColor(BLUE, WHITE);
      tft.setCursor(100, 160);
      tft.print("LED OFF");

      digitalWrite(LED, LOW);
  
      DrawButtonRedPress(BtnRedX, BtnRedY);
      delay(100);
      DrawButtonRed(BtnRedX, BtnRedY);
    }
    //----------------------------------------
  }
  //----------------------------------------
}
//========================================================================

//========================================================================DrawButtonGreen(x, y)
void DrawButtonGreen(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 84, 84, 10, BLACKM);
  tft.fillRoundRect(xp+2, yp+2, 80, 80, 10, GREEN);
  tft.setCursor(xp+22, yp+32);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("ON");
}
//========================================================================

//========================================================================DrawButtonGreenPress(x, y)
void DrawButtonGreenPress(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 84, 84, 10, BLACKM);
}
//========================================================================

//========================================================================DrawButtonRed(x, y)
void DrawButtonRed(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 84, 84, 10, BLACKM);
  tft.fillRoundRect(xp+2, yp+2, 80, 80, 10, RED);
  tft.setCursor(xp+18, yp+32);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("OFF");
}
//========================================================================

//========================================================================DrawButtonRedPress(x, y)
void DrawButtonRedPress(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 84, 84, 10, BLACKM);
}