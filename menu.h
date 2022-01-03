#pragma once
#include "headers.h"

class menu
{
	Adafruit_ILI9341 tft_;
	int selected_menu_element_ = 0; //0-play,1-settings,2-authors
	//default - 1 up/shoot, 2-enter/left, 3-back/-, 4-down/right | changing button in setting changes position in this array
	int button_[4] = { BUTTON_PIN1,BUTTON_PIN2,BUTTON_PIN3,BUTTON_PIN4 };
	bool button_state_[4] = { false,false,false,false }; //true-pressed
public:
	explicit menu(const Adafruit_ILI9341& tft);
	void display_main_menu();
	void display_string(const int x, const int y, const int size, const int color, const String str) const;
	void display_string(const int size, const int color, const String str) const;
	void display_string(const String str) const;
	void read_buttons();
};


