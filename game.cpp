#include "game.h"

game::game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, const int game_difficulty, int* game_button, const int no_enemies) :
	tft_(tft),
	sevseg_(sevseg),
	game_difficulty_(game_difficulty),
	game_button_(game_button), lives_(3 - game_difficulty),
	player_(player(tft, 110, 300, 20, 20)),
	no_enemies_(no_enemies),
	no_enemies_alive_(no_enemies)
{
	
}

//starting game - creating enemies, displaying objects and handling events
void game::start_game()
{
	//creating enemies
	int x=30, y=20, width = 20, height = 20, k=0;
	for(int i=0;i<5;i++) //enemies - rows
	{
		if (i % 2 == 0)x = 30;
		else x = 10;
		for(int j=0;j<6;j++) //enemies - columns
		{
			enemies_[k].put_variables(tft_, x, y, width, height);
			if (++k >= no_enemies_)break;
			x += 36;
		}
		if (k >= no_enemies_)break;
		y += 36;
	}

	//preparing visual elements
	display_game();
	leds_update();
	sevseg_->setNumber(score_);

	//game loop
	unsigned long previous_millis = 0;
	const unsigned long interval = 50 - game_difficulty_*10;
	unsigned long no_intervals = 0;
	while(game_state_)
	{
		sevseg_->refreshDisplay();
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

void game::display_string(const int x, const int y, const int size, const int color, const String str) const
{
	tft_->setCursor(x, y);
	tft_->setTextColor(color);
	tft_->setTextSize(size);
	tft_->println(str);
}

void game::move_enemies()
{
	int k=0;
	for (int i = 0; i < 5; i++) //enemies - rows
	{
		const int tmp_state = enemies_move_state_[i];
		for (int j = 0; j < 6; j++) //enemies - columns
		{
			if(tmp_state ==0) //row moves (left-0, right-1)
				enemies_[k].move(-15, 0);
			else
				enemies_[k].move(15, 0);

			if (tmp_state == enemies_move_state_[i]&&enemies_[k].border_collision(0)) //check if an enemy out of border
				enemies_move_state_[i] = 1;
			else if (tmp_state == enemies_move_state_[i]&&enemies_[k].border_collision(1))
				enemies_move_state_[i] = 0;
			if (++k >= no_enemies_)break;
		}
		if (k >= no_enemies_)break;
	}
}

void game::enemy_shoot()
{
	
}

//handling periodic events like bullet collision, enemies movement
void game::periodic_events(const unsigned long no_intervals)
{
	read_buttons();
	handle_buttons();
	if (shoot_cooldown_ > 0)shoot_cooldown_--;
	player_bullet_handling();
	if (no_intervals % 50 == 0)move_enemies();
}

//handling button presses
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

//updating leds display
void game::leds_update() //cos nie dziala
{
	switch (lives_)
	{
	case 0:
	{
		digitalWrite(LED_PIN1, LOW);
		digitalWrite(LED_PIN2, LOW);
		digitalWrite(LED_PIN3, LOW);
		break;
	}
	case 1:
	{
		digitalWrite(LED_PIN1, HIGH);
		digitalWrite(LED_PIN2, LOW);
		digitalWrite(LED_PIN3, LOW);
		break;
	}
	case 2:
	{
		digitalWrite(LED_PIN1, HIGH);
		digitalWrite(LED_PIN2, HIGH);
		digitalWrite(LED_PIN3, LOW);
		break;
	}
	case 3:
	{
		digitalWrite(LED_PIN1, HIGH);
		digitalWrite(LED_PIN2, HIGH);
		digitalWrite(LED_PIN3, HIGH);
		break;
	}
	default:
	{
		Serial.println("lives_error");
	}
	}
}

//end game based on scenerio: x=0 - player lost, x=1 - player win
void game::game_end()
{
	tft_->fillScreen(ILI9341_BLACK);
	display_string(70, 100, 4, ILI9341_RED, "GAME");
	display_string(63, 145, 4, ILI9341_RED, "OVER!");
	display_string(45, 190, 3, ILI9341_ORANGE, "SCORE: ");
	display_string(160, 190, 3, ILI9341_ORANGE, String(score_));
	game_state_ = 0;
	lives_ = 0;
	leds_update();
	sevseg_->blank();
}

//player bullet collison managment
void game::player_bullet_handling()
{
	if (player_bullet_)
	{
		player_bullet_->move(0, -7);
		for (int i = 0; i < no_enemies_; i++)
		{
			if (player_bullet_->check_collison(&enemies_[i])) //bullet hit enemy
			{
				enemies_[i].kill();
				no_enemies_alive_--;
				player_bullet_->kill();
				delete player_bullet_;
				player_bullet_ = nullptr;
				score_ += 10;
				sevseg_->setNumber(score_);
				tone(BUZZER_PIN, 320 + game_difficulty_ * 50, 6);
				break;
			}
		}
		if (player_bullet_ && player_bullet_->border_collision(2)) //bullet out of screen
		{
			player_bullet_->kill();
			delete player_bullet_;
			player_bullet_ = nullptr;
		}
		if (no_enemies_alive_ <= 0)
			game_end();
	}
}


