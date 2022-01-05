#include "menu.h"

menu::menu(const Adafruit_ILI9341* tft) :tft_(tft)
{}

void menu::display_main_menu()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(60, 10, 4, ILI9341_RED, "SPACE");
	display_string(25, 50, 4, ILI9341_RED, "INVADERS");
	tft_->fillRect(0, 120, 240, 3, ILI9341_BLUE);
	display_string(30, 135, 3, ILI9341_WHITE, "PLAY");
	tft_->fillRect(0, 170, 240, 3, ILI9341_BLUE);
	display_string(30, 185, 3, ILI9341_CYAN, "SETTINGS");
	tft_->fillRect(0, 220, 240, 3, ILI9341_BLUE);
	display_string(30, 235, 3, ILI9341_CYAN, "AUTHORS");
	tft_->fillRect(0, 275, 240, 3, ILI9341_BLUE);
}

void menu::display_string(const int x, const int y, const int size, const int color, const String str) const
{
	tft_->setCursor(x, y);
	display_string(size, color, str);
}

void menu::display_string(const int size, const int color, const String str) const
{
	tft_->setTextColor(color);
	tft_->setTextSize(size);
	display_string(str);
}

void menu::display_string(const String str) const
{
	tft_->println(str);
}

void menu::read_buttons()
{
	for (int i = 0; i < 4; i++)
	{
		if (digitalRead(button_[i]) == LOW)
			button_state_[i] = true;
		else
			button_state_[i] = false;
	}
}

//single button press
int menu::read_button()
{
	while (true)
	{
		for (int i = 0; i < 4; i++)
			if (digitalRead(button_[i]) == LOW)
				return i;
		delay(15);
	}
}

void menu::highlight_selected_element_menu() const
{
	if (selected_menu_element_ == 0)
	{
		display_string(30, 135, 3, ILI9341_WHITE, "PLAY");
		display_string(30, 185, 3, ILI9341_CYAN, "SETTINGS");
		display_string(30, 235, 3, ILI9341_CYAN, "AUTHORS");
	}
	else if (selected_menu_element_ == 1)
	{
		display_string(30, 135, 3, ILI9341_CYAN, "PLAY");
		display_string(30, 185, 3, ILI9341_WHITE, "SETTINGS");
		display_string(30, 235, 3, ILI9341_CYAN, "AUTHORS");
	}
	else
	{
		display_string(30, 135, 3, ILI9341_CYAN, "PLAY");
		display_string(30, 185, 3, ILI9341_CYAN, "SETTINGS");
		display_string(30, 235, 3, ILI9341_WHITE, "AUTHORS");
	}
}

void menu::handle_menu()
{
	selected_menu_element_ = 0;
	while (true)
	{
		const int button = read_button();
		if (button == 0)
		{
			selected_menu_element_ = (selected_menu_element_ - 1) % 3;
			highlight_selected_element_menu();
		}
		else if (button == 2)
		{
			selected_menu_element_ = (selected_menu_element_ + 1) % 3;
			highlight_selected_element_menu();
		}
		else if (button == 1)
			handle_menu_select();
		delay(150);
	}
}

void menu::display_authors()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(35, 35, 4, ILI9341_CYAN, "AUTHORS");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 95, 3, ILI9341_ORANGE, "Piotr");
	display_string(10, 130, 3, ILI9341_ORANGE, "Zajaczkowski");
	tft_->fillRect(0, 165, 240, 3, ILI9341_RED);
	display_string(10, 180, 3, ILI9341_ORANGE, "Julian");
	display_string(10, 215, 3, ILI9341_ORANGE, "Zielinski");
	tft_->fillRect(0, 250, 240, 3, ILI9341_RED);
}

void menu::highlight_selected_element_settings() const
{
	if (selected_menu_element_ == 0)
	{
		display_string(10, 95, 3, ILI9341_WHITE, "Difficulty");
		display_string(10, 145, 3, ILI9341_ORANGE, "Buttons");
	}
	else
	{
		display_string(10, 95, 3, ILI9341_ORANGE, "Difficulty");
		display_string(10, 145, 3, ILI9341_WHITE, "Buttons");
	}
}

void menu::display_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(25, 35, 4, ILI9341_CYAN, "SETTINGS");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 95, 3, ILI9341_WHITE, "Difficulty");
	tft_->fillRect(0, 130, 240, 3, ILI9341_RED);
	display_string(10, 145, 3, ILI9341_ORANGE, "Buttons");
	tft_->fillRect(0, 180, 240, 3, ILI9341_RED);
}

void menu::display_difficulty_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(15, 35, 4, ILI9341_CYAN, "DIFFICULTY");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 120, 4, ILI9341_WHITE, String(game_difficulty_));
	tft_->fillRect(0, 165, 240, 3, ILI9341_RED);
}

void menu::handle_settings_select()
{
	if (selected_menu_element_ == 0)
	{
		display_difficulty_settings();
		while (true)
		{
			switch (read_button())
			{
			case 0:
				break;
			case 2:
				break;
			default:
				return;
			}
		}
	}
	else
	{

	}
}

void menu::handle_settings()
{
	selected_menu_element_ = 0;
	while (true)
	{
		display_settings();
		const int button = read_button();
		if (button == 0)
		{
			selected_menu_element_ = (selected_menu_element_ - 1) % 2;
			highlight_selected_element_settings();
		}
		else if (button == 2)
		{
			selected_menu_element_ = (selected_menu_element_ + 1) % 2;
			highlight_selected_element_settings();
		}
		else if (button == 1)
		{
			handle_settings_select();
		}
		else
		{
			selected_menu_element_ = 0;
			display_main_menu();
			return;
		}
		delay(150);
	}
}

void menu::handle_menu_select()
{
	switch (selected_menu_element_)
	{
	case 0:
		//game
		break;
	case 1:
		//settings
		handle_settings();
		break;
	case 2:
		display_authors();
		read_button();
		display_main_menu();
		selected_menu_element_ = 0;
		break;
	default:
		Serial.println("HANDLESELECTERROR");
	}
}

