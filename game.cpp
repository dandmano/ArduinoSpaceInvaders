#include "game.h"

game::game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, const int game_difficulty, int* game_button, const int no_enemies) :
	tft_(tft),
	sevseg_(sevseg),
	game_difficulty_(game_difficulty),
	game_button_(game_button), player_(player(tft, 110, 290, 20, 20)),
	lives_(3 - game_difficulty),
	no_enemies_(no_enemies),
	no_enemies_alive_(no_enemies)
{}

//starting game - creating enemies, displaying objects and handling events
void game::start_game()
{
	//creating enemies
	int x = 17, y = 20, width = 20, height = 20;
	for(int i=0;i<5;i++) //enemies - rows
	{
		x = 17;
		for(int j=0;j<6;j++) //enemies - columns
		{
			enemies_[i][j].put_variables(tft_, x, y, width, height);
			x += 37;
		}
		y += 37;
	}

	//preparing visual elements
	display_game();
	leds_update();
	sevseg_->setNumber(score_);

	//game loop
	unsigned long previous_millis = 0;
	const unsigned long interval = 50 - game_difficulty_*15;
	while(game_state_)
	{
		sevseg_->refreshDisplay();
		const unsigned long current_millis = millis();
		if(current_millis-previous_millis>=interval) //actions performed periodically every time interval
		{
			previous_millis = current_millis;
			periodic_events();
		}
	}
}

//functional methods --------------------------------------------------------------------

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

//displays string
void game::display_string(const int x, const int y, const int size, const int color, const String str) const
{
	tft_->setCursor(x, y);
	tft_->setTextColor(color);
	tft_->setTextSize(size);
	tft_->println(str);
}

//handling periodic events like bullet collision, enemies movement
void game::periodic_events()
{
	read_buttons();
	handle_buttons();
	handle_player_bullet();
	handle_enemies_movement();
	handle_enemies_shoot();
}

//end game screen and display reset
void game::game_end()
{
	if (enemy_bullet_)
		enemy_bullet_->kill();
	if (player_bullet_)
		player_bullet_->kill();

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

//change of the current enemy place
void game::change_curr_enemy() 
{
	if(enemies_move_state_==1)
	{
		if(--curr_mov_ene_col_<0)
		{
			curr_mov_ene_col_ = 5;
			if (--curr_mov_ene_row_ < 0)
			{
				curr_mov_ene_row_ = 4;
				if (enemies_move_state_ != enemies_move_state_next_) // change of dirrection
				{
					enemies_move_state_ = enemies_move_state_next_;
					curr_mov_ene_col_ = 0;
				} 
			}
		}
	}
	else
	{
		if (++curr_mov_ene_col_ > 5)
		{
			curr_mov_ene_col_ = 0;
			if (--curr_mov_ene_row_ < 0)
			{
				curr_mov_ene_row_ = 4;
				if (enemies_move_state_ != enemies_move_state_next_) // change of dirrection
				{
					enemies_move_state_ = enemies_move_state_next_;
					curr_mov_ene_col_ = 5;
				}
			}
		}
	}
}

//display, update methods ---------------------------------------------------------------

//displaying player and enemies
void game::display_game()
{
	tft_->fillScreen(ILI9341_BLACK);
	player_.display();
	int k = 0;
	for (int i = 0; i < 5; i++) //enemies - rows
	{
		curr_mov_ene_row_= i;
		for (int j = 0; j < 6; j++) //enemies - columns
		{
			curr_mov_ene_col_ = j;
			enemies_[i][j].display();
			if (first_enemy_in_column_[j] < i) //setting first enemies
				first_enemy_in_column_[j] = i;
			k++;
			if(k>=no_enemies_)return;
		}
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

//handler functions ---------------------------------------------------------------------

//handling button presses
void game::handle_buttons()
{
	if (button_state_[0] && shoot_cooldown_ == 0 && !player_bullet_) //strzelanie
	{
		shoot_cooldown_ = 10;
		tone(BUZZER_PIN, 440 - game_difficulty_ * 50, 6);
		player_bullet_ = new bullet(tft_, player_.get_x() + 8, player_.get_y() - 8, 4, 8, ILI9341_CYAN);
		player_bullet_->display();
	}
	if (button_state_[1] && !player_.border_collision(0)) //ruch w lewo
	{
		player_.move(-6, 0);
	}
	if (button_state_[3] && !player_.border_collision(1)) //ruch w prawo
	{
		player_.move(6, 0);
	}
}

//player bullet collison managment
void game::handle_player_bullet()
{
	if (shoot_cooldown_ > 0)shoot_cooldown_--;
	if (!player_bullet_)
		return;

	player_bullet_->move(0, -9);
	for (int i = 0; i < 5; i++) //enemies - rows
	{
		for (int j = 0; j < 6; j++) //enemies - columns
		{
			if(!enemies_[i][j].get_is_alive())continue;
			if (!player_bullet_->check_collison(&enemies_[i][j]))continue;
			enemies_[i][j].kill();
			player_bullet_->kill();
			delete player_bullet_;
			player_bullet_ = nullptr;
			first_enemy_in_column_[j]--;
			no_enemies_alive_--;
			score_ += 10;
			sevseg_->setNumber(score_);
			tone(BUZZER_PIN, 320 , 6);
			goto checkborder;
		}
	}
	checkborder:
	if (player_bullet_ && player_bullet_->border_collision(2)) //bullet out of screen
	{
		player_bullet_->kill();
		delete player_bullet_;
		player_bullet_ = nullptr;
	}
	if (no_enemies_alive_ <= 0)
		game_end();
}

//method is moving enemies on map
void game::handle_enemies_movement()
{
	while (!enemies_[curr_mov_ene_row_][curr_mov_ene_col_].get_is_alive()&&no_enemies_alive_>0)
		change_curr_enemy();
	if(enemies_move_state_==1)
	{
		enemies_[curr_mov_ene_row_][curr_mov_ene_col_].move(9, 0);
		if (enemies_[curr_mov_ene_row_][curr_mov_ene_col_].border_collision(1))
			enemies_move_state_next_ = 0;
	}
	else
	{
		enemies_[curr_mov_ene_row_][curr_mov_ene_col_].move(-9, 0);
		if (enemies_[curr_mov_ene_row_][curr_mov_ene_col_].border_collision(0))
			enemies_move_state_next_ = 1;
	}
	change_curr_enemy();
}

//method is creating and moving enemy bullet
void game::handle_enemies_shoot()
{
	if (enemy_shoot_cooldown_ > 0)enemy_shoot_cooldown_--;
	if(!enemy_bullet_ && enemy_shoot_cooldown_<=0)
	{
		int x = random(0, 6);
		while (first_enemy_in_column_[x] < 0)
			x = random(0, 6);
		enemy_bullet_ = new bullet(tft_, enemies_[first_enemy_in_column_[x]][x].get_x()+8, enemies_[first_enemy_in_column_[x]][x].get_y()+20,4,8,ILI9341_ORANGE);
		enemy_bullet_->display();
		tone(BUZZER_PIN, 800 , 6);
		enemy_shoot_cooldown_ = 16-game_difficulty_*2;
	}
	if(enemy_bullet_)
	{
		enemy_bullet_->move(0, 5+game_difficulty_);
		if(enemy_bullet_->check_collison(&player_))
		{
			tone(BUZZER_PIN, 400, 15);
			lives_--;
			leds_update();
			if (lives_ == 0)
				game_end();
			enemy_bullet_->kill();
			delete enemy_bullet_;
			enemy_bullet_ = nullptr;
			player_.move(0, 0);
		}
		if(enemy_bullet_&&enemy_bullet_->border_collision(3))
		{
			enemy_bullet_->kill();
			delete enemy_bullet_;
			enemy_bullet_ = nullptr;
		}
	}
}
