#pragma once
#include "headers.h"

class menu
{
	const Adafruit_ILI9341* tft_;
	//0-play,1-settings,2-authors
	int selected_menu_element_ = 0;
	//default - 0 up/shoot, 1 enter/left, 2 down/-, enter/right | changing button in setting changes position in this array
	int button_[4] = { BUTTON_PIN1,BUTTON_PIN2,BUTTON_PIN3,BUTTON_PIN4 };
	bool button_state_[4] = { false,false,false,false }; //true-pressed
public:
	explicit menu(const Adafruit_ILI9341* tft);
	void display_main_menu();
	void handle_menu();
private:
	void display_string(const int x, const int y, const int size, const int color, const String str) const;
	void display_string(const int size, const int color, const String str) const;
	void display_string(const String str) const;
	void read_buttons();
	int read_button();
	void highlight_selected_element() const;
	void print_authors();
	void handle_select();
};


