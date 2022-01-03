#include "menu.h"

menu::menu(const Adafruit_ILI9341& tft) :tft_(tft)
{}

void menu::display_main_menu()
{
	display_string(65, 10, 4, ILI9341_RED, "SPACE");
	display_string(30, 50, 4, ILI9341_RED, "INVADERS");
	tft_.fillRect(0, 120, 240, 3, ILI9341_BLUE);
	display_string(30, 135, 3, ILI9341_CYAN, "PLAY");
	tft_.fillRect(0, 170, 240, 3, ILI9341_BLUE);
	display_string(30, 185, 3, ILI9341_CYAN, "SETTINGS");
	tft_.fillRect(0, 220, 240, 3, ILI9341_BLUE);
	display_string(30, 235, 3, ILI9341_CYAN, "AUTHORS");
	tft_.fillRect(0, 275, 240, 3, ILI9341_BLUE);
}
void menu::display_string(const int x, const int y, const int size, const int color, const String str) const
{
	tft_.setCursor(x, y);
	display_string(size, color, str);
}

void menu::display_string(const int size, const int color, const String str) const
{
	tft_.setTextColor(color);
	tft_.setTextSize(size);
	display_string(str);
}

void menu::display_string(const String str) const
{
	tft_.println(str);
}

int* menu::read_buttons()
{
	for (int i = 0; i < 4; i++)
	{
		if (digitalRead(button_[i]) == LOW)
			button_state_[i] = true;
		else
			button_state_[i] = false;
	}
}


