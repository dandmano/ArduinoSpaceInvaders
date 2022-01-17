#pragma once
#include "headers.h"

class menu
{
//consts
	const Adafruit_ILI9341* tft_;
	const SevSeg* sevseg_;
//menu variables
	//in menu : 0-play, 1-settings, 2-authors | in setting : 0-difficulty, 1-buttons, 2-editor | in buttons : 0-left, 1-right, 2-shoot
	int selected_menu_element_ = 0;
	//for menu - 0 up, 1 enter, 2 down, 3 back
	int menu_button_[4] = { BUTTON_PIN1,BUTTON_PIN2,BUTTON_PIN3,BUTTON_PIN4 };
//variables for game
	//3 game difficulties - 0,1,2 (easy, normal, hard)
	int game_difficulty_ = 0;
	//default 18 - 3 rows
	int no_enemies_ = 18;
	//default for game - 0 shoot, 1 left, 2 - , 3 right
	int game_button_[4] = { BUTTON_PIN1,BUTTON_PIN2,BUTTON_PIN3,BUTTON_PIN4 };

public:
	explicit menu(const Adafruit_ILI9341* tft, const SevSeg* sevseg);
private:
//functional methods
	int read_button();
	void display_string(const int x, const int y, const int size, const int color, const String str) const;
	String game_difficulty_to_string();
	String button_to_string(int button_number);
	void button_change_error();
//display methods
public:
	void display_main_menu();
private:	
	void display_settings();
	void display_authors();
	void display_difficulty_settings();
	void display_button_settings();
	void display_button_change_helper();
	void display_editor_settings();
//highlight-display methods
	void highlight_selected_element_menu() const;
	void highlight_selected_element_settings() const;
	void highlight_selected_element_button_settings();
//handler functions
public:
	void handle_menu();
private:
	void handle_menu_select();
	void handle_settings();
	void handle_settings_select();
	void handle_difficulty_settings();
	void handle_buttons_settings();
	void handle_button_change();
	void handle_editor_settings();
};


