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
		if (digitalRead(menu_button_[i]) == LOW)
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
			if (digitalRead(menu_button_[i]) == LOW)
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

String menu::game_difficulty_to_string()
{
	if (game_difficulty_ == 0)
		return "Easy";
	if (game_difficulty_ == 1)
		return "Normal";
	return "Hard";
}

void menu::display_difficulty_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(30, 45, 3, ILI9341_ORANGE, "DIFFICULTY");
	tft_->fillRect(0, 95, 240, 3, ILI9341_RED);
	display_string(60, 120, 4, ILI9341_CYAN, game_difficulty_to_string());
	tft_->fillRect(0, 165, 240, 3, ILI9341_RED);
}

void menu::handle_difficulty_settings()
{
	display_difficulty_settings();
	while (true)
	{
		switch (read_button())
		{
		case 0:
			game_difficulty_ = (game_difficulty_ + 1) % 3;
			tft_->fillRect(0, 120, 240, 40, ILI9341_BLACK);
			display_string(60, 120, 4, ILI9341_CYAN, game_difficulty_to_string());
			break;
		case 2:
			game_difficulty_ = (game_difficulty_ - 1) % 3;
			tft_->fillRect(0, 120, 240, 40, ILI9341_BLACK);
			display_string(60, 120, 4, ILI9341_CYAN, game_difficulty_to_string());
			break;
		default:
			display_settings();
			return;
		}
		delay(150);
	}
}

String menu::button_to_string(const int button_number)
{
	switch (button_number)
	{
	case 7:
		return "Upper button";
	case 6:
		return "Left button";
	case 5:
		return "Middle button";
	case 4:
		return "Right button";
	default:
		Serial.println("ERROR");
		return "ERROR";
	}
}

void menu::highlight_selected_element_button_settings()
{
	if (selected_menu_element_ == 0)
	{
		display_string(10, 95, 3, ILI9341_WHITE, "Move left:");
		display_string(20, 130, 3, ILI9341_WHITE, button_to_string(game_button_[0]));
		display_string(10, 160, 3, ILI9341_CYAN, "Move right:");
		display_string(20, 195, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
		display_string(10, 225, 3, ILI9341_CYAN, "Shoot:");
		display_string(20, 260, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
	}
	else if (selected_menu_element_ == 1)
	{
		display_string(10, 95, 3, ILI9341_CYAN, "Move left:");
		display_string(20, 130, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
		display_string(10, 160, 3, ILI9341_WHITE, "Move right:");
		display_string(20, 195, 3, ILI9341_WHITE, button_to_string(game_button_[3]));
		display_string(10, 225, 3, ILI9341_CYAN, "Shoot:");
		display_string(20, 260, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
	}
	else
	{
		display_string(10, 95, 3, ILI9341_CYAN, "Move left:");
		display_string(20, 130, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
		display_string(10, 160, 3, ILI9341_CYAN, "Move right:");
		display_string(20, 195, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
		display_string(10, 225, 3, ILI9341_WHITE, "Shoot:");
		display_string(20, 260, 3, ILI9341_WHITE, button_to_string(game_button_[1]));
	}
}

void menu::display_button_settings() //repair!!
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(25, 35, 4, ILI9341_ORANGE, "BUTTONS");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 95, 3, ILI9341_WHITE, "Move left:");
	display_string(20, 130, 3, ILI9341_WHITE, button_to_string(game_button_[0]));
	tft_->fillRect(0, 145, 240, 3, ILI9341_RED);
	display_string(10, 160, 3, ILI9341_CYAN, "Move right:");
	display_string(20, 195, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
	tft_->fillRect(0, 210, 240, 3, ILI9341_RED);
	display_string(10, 225, 3, ILI9341_CYAN, "Shoot:");
	display_string(20, 260, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
	tft_->fillRect(0, 275, 240, 3, ILI9341_RED);
}

void menu::handle_button_change()
{

}

void menu::handle_buttons_settings()
{
	selected_menu_element_ = 0;
	display_button_settings();
	while (true)
	{
		switch (read_button())
		{
		case 0:
			selected_menu_element_ = (selected_menu_element_ - 1) % 3;
			highlight_selected_element_button_settings();
			break;
		case 1:
			handle_button_change();
			break;
		case 2:
			selected_menu_element_ = (selected_menu_element_ + 1) % 3;
			highlight_selected_element_button_settings();
			break;
		case 3:
			selected_menu_element_ = 0;
			display_settings();
			return;
		default:
			Serial.println("ERROR");
			return;
		}
	}
}

void menu::handle_settings_select()
{
	if (selected_menu_element_ == 0)
		handle_difficulty_settings();
	else
		handle_buttons_settings();
}

void menu::handle_settings()
{
	selected_menu_element_ = 0;
	display_settings();
	while (true)
	{
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

