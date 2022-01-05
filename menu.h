#pragma once
#include "headers.h"

class menu
{
	const Adafruit_ILI9341* tft_;
	//in menu : 0-play, 1-settings, 2-authors| in setting : 0-difficulty, 1-buttons
	int selected_menu_element_ = 0;
	//3 game difficulties - 0,1,2
	int game_difficulty_ = 0;
	//default for menu - 0 up, 1 enter, 2 down, 3 back
	int button_[4] = { BUTTON_PIN1,BUTTON_PIN2,BUTTON_PIN3,BUTTON_PIN4 };
	//default for game - 0 shoot, 1 left, 2 shoot, 3 right
	int game_button_[4] = { BUTTON_PIN1,BUTTON_PIN2,BUTTON_PIN3,BUTTON_PIN4 };
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
	void highlight_selected_element_menu() const;
	void display_authors();
	void highlight_selected_element_settings() const;
	void display_settings();
	static void display_difficulty_settings();
	void handle_settings_select();
	void handle_settings();
	void handle_menu_select();
};


