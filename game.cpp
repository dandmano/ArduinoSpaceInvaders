#include "game.h"

game::game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, const int game_difficulty, int* game_button, const int no_enemies) :
	tft_(tft),
	sevseg_(sevseg),
	game_difficulty_(game_difficulty),
	game_button_(game_button), lives_(3 - game_difficulty),
	player_(player(tft, 110, 300, 20, 20)),
	no_enemies_(no_enemies)
{
}

game::~game()
{
	Serial.println("WTFISGOINGON ");
	delete player_bullet_;
}

//starting game - creating enemies, displaying objects and handling events
void game::start_game()
{
	int x=30, y=20, width = 20, height = 20, k=0;
	for(int i=0;i<5;i++) //enemies - rows
	{
		if (i % 2 == 0)x = 30;
		else x = 10;
		for(int j=0;j<6;j++) //enemies - columns
		{
			enemies_[k].put_variables(tft_, x, y, width, height);
			k++;
			if (k >= no_enemies_)break;
			x += 36;
		}
		if (k >= no_enemies_)break;
		y += 36;
	}
	display_game();
	unsigned long previous_millis = 0;
	const unsigned long interval = 50 - game_difficulty_*10;
	unsigned long no_intervals = 0;
	while(true) //petla gry
	{
		unsigned long current_millis = millis();
		if(current_millis-previous_millis>=interval) //actions performed periodically every time interval
		{
			no_intervals++;
			previous_millis = current_millis;
			periodic_events(no_intervals);
		}
	}
}

//reading every single button state
void game::read_buttons()
{
	for (int i = 0; i < 4; i++)
	{
		if (digitalRead(game_button_[i]) == LOW)
			button_state_[i] = true;
		else
			button_state_[i] = false;
	}
}

//displaying player and enemies
void game::display_game()
{
	tft_->fillScreen(ILI9341_BLACK);
	player_.display();
	for (int i = 0; i < no_enemies_; i++)
	{
		enemies_[i].display();
	}
}

//handling periodic events like bullet collision, enemies movement
void game::periodic_events(unsigned long no_intervals)
{
	read_buttons();
	handle_buttons();
	if (shoot_cooldown_ > 0)shoot_cooldown_--;
	if(player_bullet_) //
	{
		player_bullet_->move(0, -5);
		for(int i=0;i<no_enemies_;i++)
		{
			if(player_bullet_->check_collison(&enemies_[i])) //bullet hit enemy
			{
				enemies_[i].kill();
				delete player_bullet_;
				player_bullet_ = nullptr;
				tone(BUZZER_PIN, 320+game_difficulty_*50, 6);
				break;
			}
		}
		if(player_bullet_&&player_bullet_->border_collision(2)) //bullet out of screen
		{
			delete(player_bullet_);
			player_bullet_ = nullptr;
		}
	}

}

void game::handle_buttons()
{
	if(button_state_[0]&& shoot_cooldown_ == 0&&!player_bullet_) //strzelanie
	{
		shoot_cooldown_ = 10;
		tone(BUZZER_PIN, 440-game_difficulty_*50, 6);
		player_bullet_ = new bullet(tft_, player_.get_x()+8, player_.get_y() - 8, 4, 8,ILI9341_CYAN);
		player_bullet_->display();
	}
	if(button_state_[1]&& !player_.border_collision(0)) //ruch w lewo
	{
		player_.move(-4, 0);
	}
	if (button_state_[3]&& !player_.border_collision(1)) //ruch w prawo
	{
		player_.move(4, 0);
	}
}


