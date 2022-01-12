#pragma once
#include "SPI/SPI.h"
#include "Adafruit-GFX-Library/Adafruit_GFX.h"
#include "Adafruit_ILI9341/Adafruit_ILI9341.h"
#include "LinkedList.h"


//headers made for intellisense - different for wokwi simulator
//wokwi headers:
//#include "SPI.h"
//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9341.h"
//#include "SevSeg.h"
//#include "LinkedList.h"


//Buttons
#define BUTTON_PIN1 7
#define BUTTON_PIN2 6
#define BUTTON_PIN3 5
#define BUTTON_PIN4 4
//Buzzer
#define BUZZER_PIN 3
//Ili9341
#define TFT_CS 10
#define TFT_DC 9
//Leds
#define LED_PIN1 2
#define LED_PIN2 1
#define LED_PIN3 0
//7segDisp
#define D7_DIG1 34
#define D7_DIG2 35
#define D7_DIG3 36
#define D7_DIG4 37
#define D7_A 38
#define D7_B 39
#define D7_C 40
#define D7_D 41
#define D7_E 42
#define D7_F 43
#define D7_G 44
#define D7_DP 45