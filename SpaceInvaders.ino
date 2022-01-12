#include "headers.h"
#include "menu.h"

Adafruit_ILI9341 tft= Adafruit_ILI9341(TFT_CS,TFT_DC);
SevSeg sevseg;
menu menu_ = menu(&tft,&sevseg);

void initialize_sevseg(SevSeg* sevseg);

void setup() {
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN4, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);
  initialize_sevseg(&sevseg);
  Serial.begin(9600);
  tft.begin();
}

void loop() {
  menu_.display_main_menu();
  menu_.handle_menu();
}

void initialize_sevseg(SevSeg* sevseg)
{
  byte numDigits = 4;
  byte digitPins[] = {D7_DIG1,D7_DIG2,D7_DIG3,D7_DIG4};
  byte segmentPins[] = {D7_A,D7_B,D7_C,D7_D,D7_E,D7_F,D7_G};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_ANODE;
  bool updateWithDelays = false;
  bool leadingZeros = false; 
  bool disableDecPoint = true; 

  sevseg->begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg->setBrightness(90);
}