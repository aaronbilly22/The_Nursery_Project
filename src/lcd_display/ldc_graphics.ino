// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

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

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BUTTON_X 52
#define BUTTON_Y 150
#define BUTTON_W 80
#define BUTTON_H 45
#define BUTTON_SPACING_X 26
#define BUTTON_SPACING_Y 30
#define BUTTON_TEXTSIZE 3

Adafruit_GFX_Button button[3];


Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

//four status bits for:
// [0] = master switch on/off ie)running
// [1] = missing pot detected
// [2] = refill trays
// [3] = refill pots
byte status[4];
byte state[4] = {0,0,0,0};
byte oldstate[4] = {0,0,0,0};


void setup(void) {
  status[0] = 10;
  status[1] = 11;
  status[2] = 12;
  status[3] = 13;
  pinMode(status[0],INPUT);
  pinMode(status[1],INPUT);
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

#ifdef USE_ADAFRUIT_SHIELD_PINOUT
  Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    return;
  }


  
  tft.begin(identifier);
  
  tft.fillScreen(WHITE);
  tft.setRotation(1);
  tft.fillRect(100,0,280,20,BLACK);
  tft.setCursor(160, 2);
  tft.setTextColor(WHITE); 
  tft.setTextSize(2);
  tft.println("Status Monitor");
  
    
  

  tft.fillRoundRect(245,175,215,135,3,RED);
  tft.drawRoundRect(245,175,215,135,3,BLACK);

  // button[0].initButton(&tft, 120,117,200,115,BLACK,YELLOW,WHITE,"yep",3);
  // button[0].drawButton();

  verification();

  masterSwitchOFF();

  trayStock();

  
  // button[0].initButton(&tft, 120,252,200,115,BLACK,BLUE,WHITE,"blue",3);
  // button[0].drawButton();
    
  }
  



void loop(void) {
  // [0] = master switch on/off ie)running
  // [1] = missing pot detected
  // [2] = refill trays
  // [3] = refill pots
    state[0] = digitalRead(status[0]);
    state[1] = digitalRead(status[1]);
    state[2] = digitalRead(status[2]);
    state[3] = digitalRead(status[3]);

    
    if(state[0]!=oldstate[0]){
      oldstate[0] ^= 1;
      if(state[0]==1){
        masterSwitchON();
      }
      else{
        masterSwitchOFF();
      }
    }

    if(state[1]!=oldstate[1]){
      oldstate[1] ^= 1;
      if(state[1]==1){
        verificationDetected();
      }
      else{
        verification();
      }
    }

    if(state[2]!=oldstate[2]){
      oldstate[2] ^= 1;
      if(state[2]==1){
        trayStockRefill();
      }
      else{
        trayStock();
      }
    }


    
    
  
        
}


void masterSwitchON(){
  tft.fillRoundRect(20,30,215,135,3,GREEN);
  tft.drawRoundRect(20,30,215,135,3,BLACK);
  tft.setCursor(50,35);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("Master Switch");
  tft.setCursor(90,90);
  tft.setTextColor(BLACK);
  tft.setTextSize(6);
  tft.print("ON");
}
void masterSwitchOFF(){
  tft.fillRoundRect(20,30,215,135,3,RED);
  tft.drawRoundRect(20,30,215,135,3,BLACK);
  tft.setCursor(50,35);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Master Switch");
  tft.setCursor(80,90);
  tft.setTextColor(WHITE);
  tft.setTextSize(6);
  tft.print("OFF");
}

void verification(){
  tft.fillRoundRect(245,30,215,135,3,GREEN);
  tft.drawRoundRect(245,30,215,135,3,BLACK);
  tft.setCursor(280,35);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("Verification");
  tft.setCursor(280,95);
  tft.setTextColor(BLACK);
  tft.setTextSize(5);
  tft.print("CLEAR");
}

void verificationDetected(){
  tft.fillRoundRect(245,30,215,135,3,RED);
  tft.drawRoundRect(245,30,215,135,3,BLACK);
  tft.setCursor(280,35);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("Verification");
  tft.setCursor(300,90);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("ERROR!");
  tft.setCursor(255,120);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Pot Missing");
}

void trayStockRefill(){
  tft.fillRoundRect(20,175,215,135,3,YELLOW);
  tft.drawRoundRect(20,175,215,135,3,BLACK);
  tft.setCursor(75,180);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("Tray Stock");
  tft.setCursor(60,235);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("WARNING!");
  tft.setCursor(40,265);
  tft.setTextColor(BLACK);
  tft.setTextSize(3);
  tft.print("Fill Trays");
}

void trayStock(){
  tft.fillRoundRect(20,175,215,135,3,GREEN);
  tft.drawRoundRect(20,175,215,135,3,BLACK);
  tft.setCursor(75,180);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("Tray Stock");
  tft.setCursor(80,240);
  tft.setTextColor(BLACK);
  tft.setTextSize(5);
  tft.print("FULL");
}

