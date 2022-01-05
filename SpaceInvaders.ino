#include "headers.h"
#include "menu.h"

Adafruit_ILI9341 tft= Adafruit_ILI9341(TFT_CS,TFT_DC);
menu menu_ = menu(&tft);

void setup() {
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(BUTTON_PIN3, INPUT_PULLUP);
  pinMode(BUTTON_PIN4, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  tft.begin();
}

void loop() {
  menu_.display_main_menu();
  menu_.handle_menu();
}
