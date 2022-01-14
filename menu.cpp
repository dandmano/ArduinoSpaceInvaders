#include "menu.h"
#include "game.h"

menu::menu(const Adafruit_ILI9341* tft, const SevSeg* sevseg) :
	tft_(tft),
	sevseg_(sevseg)
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

//single button press
int menu::read_button()
{
	while (true)
	{
		for (int i = 0; i < 4; i++)
			if (digitalRead(menu_button_[i]) == LOW)
			{
				tone(BUZZER_PIN, 440, 10);
				return i;
			}
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
		switch (read_button())
		{
		case 0:
			selected_menu_element_ -= 1;
			if (selected_menu_element_ < 0)
				selected_menu_element_ = 2;
			highlight_selected_element_menu();
			break;
		case 2:
			selected_menu_element_ = (selected_menu_element_ + 1) % 3;
			highlight_selected_element_menu();
			break;
		case 1:
			handle_menu_select();
			break;
		default:
			Serial.println("error menu select");
		}
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
			game_difficulty_ = game_difficulty_ + 1;
			game_difficulty_ %= 3;
			tft_->fillRect(0, 120, 240, 40, ILI9341_BLACK);
			display_string(60, 120, 4, ILI9341_CYAN, game_difficulty_to_string());
			break;
		case 2:
			game_difficulty_ = game_difficulty_ - 1;
			if (game_difficulty_ < 0)game_difficulty_ = 2;
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
		return "Up button";
	case 6:
		return "Left button";
	case 5:
		return "Down button";
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
		display_string(10, 90, 3, ILI9341_WHITE, "Move left:");
		display_string(20, 125, 3, ILI9341_WHITE, button_to_string(game_button_[0]));
		display_string(10, 170, 3, ILI9341_CYAN, "Move right:");
		display_string(20, 205, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
		display_string(10, 250, 3, ILI9341_CYAN, "Shoot:");
		display_string(20, 285, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
	}
	else if (selected_menu_element_ == 1)
	{
		display_string(10, 90, 3, ILI9341_CYAN, "Move left:");
		display_string(20, 125, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
		display_string(10, 170, 3, ILI9341_WHITE, "Move right:");
		display_string(20, 205, 3, ILI9341_WHITE, button_to_string(game_button_[3]));
		display_string(10, 250, 3, ILI9341_CYAN, "Shoot:");
		display_string(20, 285, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
	}
	else
	{
		display_string(10, 90, 3, ILI9341_CYAN, "Move left:");
		display_string(20, 125, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
		display_string(10, 170, 3, ILI9341_CYAN, "Move right:");
		display_string(20, 205, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
		display_string(10, 250, 3, ILI9341_WHITE, "Shoot:");
		display_string(20, 285, 3, ILI9341_WHITE, button_to_string(game_button_[1]));
	}
}

void menu::display_button_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(25, 35, 4, ILI9341_ORANGE, "BUTTONS");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 90, 3, ILI9341_WHITE, "Move left:");
	display_string(20, 125, 3, ILI9341_WHITE, button_to_string(game_button_[0]));
	tft_->fillRect(0, 160, 240, 3, ILI9341_RED);
	display_string(10, 170, 3, ILI9341_CYAN, "Move right:");
	display_string(20, 205, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
	tft_->fillRect(0, 240, 240, 3, ILI9341_RED);
	display_string(10, 250, 3, ILI9341_CYAN, "Shoot:");
	display_string(20, 285, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
	tft_->fillRect(0, 318, 240, 3, ILI9341_RED);
}

void menu::display_button_change_helper()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(10, 120, 3, ILI9341_CYAN, "Press button");
	display_string(10, 155, 3, ILI9341_CYAN, "to bind");
}

void menu::handle_button_change()
{
	display_button_change_helper();
	const int x = menu_button_[read_button()];
	switch (selected_menu_element_)
	{
	case 0:
		game_button_[0] = x;
		break;
	case 1:
		game_button_[3] = x;
		break;
	case 2:
		game_button_[1] = x;
		break;
	default:
		Serial.println("BUTTON CHANGE ERROR");
	}
	selected_menu_element_ = 0;
	display_button_settings();
}

void menu::button_change_error()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(10, 120, 3, ILI9341_RED, "All buttons");
	display_string(10, 155, 3, ILI9341_RED, "must be ");
	display_string(10, 190, 3, ILI9341_RED, "different!");
	read_button();
	selected_menu_element_ = 0;
	display_button_settings();
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
			selected_menu_element_ = selected_menu_element_ - 1;
			if (selected_menu_element_ < 0)selected_menu_element_ = 2;
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
			if (game_button_[0] == game_button_[1] || game_button_[0] == game_button_[3] || game_button_[1] == game_button_[3])
			{
				button_change_error();
				break;
			}
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
			selected_menu_element_ = selected_menu_element_ - 1;
			if (selected_menu_element_ < 0)selected_menu_element_ = 1;
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
	if(selected_menu_element_==0)
	{
		game* game_ = new game(tft_, sevseg_, game_difficulty_, game_button_,no_enemies_);
		game_->start_game();
		delay(1000);
		delete game_;
	}
	else if(selected_menu_element_ == 1)
	{
		handle_settings();
	}
	else if(selected_menu_element_ == 2)
	{
		display_authors();
		read_button();
		display_main_menu();
		selected_menu_element_ = 0;
	}
}

