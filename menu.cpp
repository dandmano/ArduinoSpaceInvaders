#include "menu.h"
#include "game.h"

menu::menu(const Adafruit_ILI9341* tft, const SevSeg* sevseg) :
	tft_(tft),
	sevseg_(sevseg)
{}

//functional methods --------------------------------------------------------------------

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

//displays string
void menu::display_string(const int x, const int y, const int size, const int color, const String str) const
{
	tft_->setCursor(x, y);
	tft_->setTextColor(color);
	tft_->setTextSize(size);
	tft_->println(str);
}

//returns string of current game difficulty
String menu::game_difficulty_to_string()
{
	if (game_difficulty_ == 0)
		return "Easy";
	if (game_difficulty_ == 1)
		return "Normal";
	return "Hard";
}

//returns string of button 
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
		Serial.println("BUTTON TO STRING ERROR");
		return "ERROR";
	}
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

//display methods -----------------------------------------------------------------------

//displays main menu
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

//displays settings
void menu::display_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(25, 35, 4, ILI9341_CYAN, "SETTINGS");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 95, 3, ILI9341_WHITE, "Difficulty");
	tft_->fillRect(0, 130, 240, 3, ILI9341_RED);
	display_string(10, 145, 3, ILI9341_ORANGE, "Buttons");
	tft_->fillRect(0, 180, 240, 3, ILI9341_RED);
	display_string(10, 195, 3, ILI9341_ORANGE, "Editor");
	tft_->fillRect(0, 230, 240, 3, ILI9341_RED);
}

//displays authors
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

//displays difficulty settings
void menu::display_difficulty_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(30, 45, 3, ILI9341_ORANGE, "DIFFICULTY");
	tft_->fillRect(0, 95, 240, 3, ILI9341_RED);
	display_string(60, 120, 4, ILI9341_CYAN, game_difficulty_to_string());
	tft_->fillRect(0, 165, 240, 3, ILI9341_RED);
}

//displays button settings
void menu::display_button_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(25, 35, 4, ILI9341_ORANGE, "BUTTONS");
	tft_->fillRect(0, 80, 240, 3, ILI9341_RED);
	display_string(10, 90, 3, ILI9341_WHITE, "Move left:");
	display_string(20, 125, 3, ILI9341_WHITE, button_to_string(game_button_[1]));
	tft_->fillRect(0, 160, 240, 3, ILI9341_RED);
	display_string(10, 170, 3, ILI9341_CYAN, "Move right:");
	display_string(20, 205, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
	tft_->fillRect(0, 240, 240, 3, ILI9341_RED);
	display_string(10, 250, 3, ILI9341_CYAN, "Shoot:");
	display_string(20, 285, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
	tft_->fillRect(0, 318, 240, 3, ILI9341_RED);
}

//displays button change helper
void menu::display_button_change_helper()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(10, 120, 3, ILI9341_CYAN, "Press button");
	display_string(10, 155, 3, ILI9341_CYAN, "to bind");
}

//displays editor settings
void menu::display_editor_settings()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(50, 25, 4, ILI9341_ORANGE, "EDITOR");
	tft_->fillRect(0, 70, 240, 3, ILI9341_RED);
	display_string(40, 80, 3, ILI9341_CYAN, "Number of:");
	display_string(60, 115, 3, ILI9341_CYAN, "enemies");
	tft_->fillRect(0, 150, 240, 3, ILI9341_RED);
	display_string(100, 165, 4, ILI9341_BLUE, String(no_enemies_));
	tft_->fillRect(0, 215, 240, 3, ILI9341_RED);
}

//highlight-display methods -------------------------------------------------------------

//highlights selected element in menu
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

//highlights selected element in settings
void menu::highlight_selected_element_settings() const
{
	if (selected_menu_element_ == 0)
	{
		display_string(10, 95, 3, ILI9341_WHITE, "Difficulty");
		display_string(10, 145, 3, ILI9341_ORANGE, "Buttons");
		display_string(10, 195, 3, ILI9341_ORANGE, "Editor");
	}
	else if (selected_menu_element_ == 1)
	{
		display_string(10, 95, 3, ILI9341_ORANGE, "Difficulty");
		display_string(10, 145, 3, ILI9341_WHITE, "Buttons");
		display_string(10, 195, 3, ILI9341_ORANGE, "Editor");
	}
	else
	{
		display_string(10, 95, 3, ILI9341_ORANGE, "Difficulty");
		display_string(10, 145, 3, ILI9341_ORANGE, "Buttons");
		display_string(10, 195, 3, ILI9341_WHITE, "Editor");
	}
}

//highlights selected element in button settings
void menu::highlight_selected_element_button_settings()
{
	if (selected_menu_element_ == 0)
	{
		display_string(10, 90, 3, ILI9341_WHITE, "Move left:");
		display_string(20, 125, 3, ILI9341_WHITE, button_to_string(game_button_[1]));
		display_string(10, 170, 3, ILI9341_CYAN, "Move right:");
		display_string(20, 205, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
		display_string(10, 250, 3, ILI9341_CYAN, "Shoot:");
		display_string(20, 285, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
	}
	else if (selected_menu_element_ == 1)
	{
		display_string(10, 90, 3, ILI9341_CYAN, "Move left:");
		display_string(20, 125, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
		display_string(10, 170, 3, ILI9341_WHITE, "Move right:");
		display_string(20, 205, 3, ILI9341_WHITE, button_to_string(game_button_[3]));
		display_string(10, 250, 3, ILI9341_CYAN, "Shoot:");
		display_string(20, 285, 3, ILI9341_CYAN, button_to_string(game_button_[0]));
	}
	else
	{
		display_string(10, 90, 3, ILI9341_CYAN, "Move left:");
		display_string(20, 125, 3, ILI9341_CYAN, button_to_string(game_button_[1]));
		display_string(10, 170, 3, ILI9341_CYAN, "Move right:");
		display_string(20, 205, 3, ILI9341_CYAN, button_to_string(game_button_[3]));
		display_string(10, 250, 3, ILI9341_WHITE, "Shoot:");
		display_string(20, 285, 3, ILI9341_WHITE, button_to_string(game_button_[0]));
	}
}

//handler functions ---------------------------------------------------------------------

//method handle user operations in menu
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
		case 3:
			break;
		default:
			Serial.println("MENU SELECT ERROR");
		}
		delay(150);
	}
}

//method performs the appropriate actions depending on the selection in the menu
void menu::handle_menu_select()
{
	if (selected_menu_element_ == 0)
	{
		game game_ = game(tft_, sevseg_, game_difficulty_, game_button_, no_enemies_);
		game_.start_game();
		read_button();
		display_main_menu();
	}
	else if (selected_menu_element_ == 1)
	{
		handle_settings();
	}
	else if (selected_menu_element_ == 2)
	{
		display_authors();
		read_button();
		display_main_menu();
		selected_menu_element_ = 0;
	}
}

//settings handling
void menu::handle_settings()
{
	selected_menu_element_ = 0;
	display_settings();
	while (true)
	{
		const int button = read_button();
		if (button == 0)
		{
			selected_menu_element_--;
			if (selected_menu_element_ < 0)selected_menu_element_ = 2;
			highlight_selected_element_settings();
		}
		else if (button == 2)
		{
			selected_menu_element_ = (selected_menu_element_ + 1) % 3;
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

//setting select handling
void menu::handle_settings_select()
{
	if (selected_menu_element_ == 0)
		handle_difficulty_settings();
	else if (selected_menu_element_ == 1)
		handle_buttons_settings();
	else
		handle_editor_settings();
}

//dificulty settings handling
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

//handle button settings
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
			Serial.println("BUTTON SETTINGS ERROR");
			return;
		}
	}
}

//button change handling
void menu::handle_button_change()
{
	display_button_change_helper();
	const int x = menu_button_[read_button()];
	switch (selected_menu_element_)
	{
	case 0:
		game_button_[1] = x;
		break;
	case 1:
		game_button_[3] = x;
		break;
	case 2:
		game_button_[0] = x;
		break;
	default:
		Serial.println("BUTTON CHANGE ERROR");
	}
	selected_menu_element_ = 0;
	display_button_settings();
}


//editor settings handling
void menu::handle_editor_settings()
{
	display_editor_settings();
	int x = 0;
	while (x != 1 && x != 3)
	{
		delay(100);
		x = read_button();
		if (x == 0)
		{
			if (no_enemies_ < 30)
			{
				no_enemies_++;
				tft_->fillRect(50, 160, 100, 50, ILI9341_BLACK);
				display_string(100, 165, 4, ILI9341_BLUE, String(no_enemies_));
			}
		}
		else if (x == 2)
		{
			if (no_enemies_ > 1)
			{
				no_enemies_--;
				tft_->fillRect(50, 160, 100, 50, ILI9341_BLACK);
				display_string(100, 165, 4, ILI9341_BLUE, String(no_enemies_));
			}
		}
	}
	selected_menu_element_ = 0;
	display_settings();
}