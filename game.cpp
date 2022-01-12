#include "game.h"

game::game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, const int game_difficulty, int* game_button) :tft_(tft), sevseg_(sevseg), game_difficulty_(game_difficulty), game_button_(game_button),lives_(3-game_difficulty),
	player_(new player(tft, 110, 300, 20, 20))
{
}

void game::start_game()
{
	int x=30, y=20, width = 20, height = 20;
	for(int i=0;i<2;i++) //dodawanie przeciwnikow - linie
	{
		if (i % 2 == 0)x = 30;
		else x = 10;
		for(int j=0;j<6;j++) //dodawanie przeciwnikow - kolumny
		{
			enemies_.Append(new enemy(tft_, x, y, width, height));
			x += 36;
		}
		y += 36;
	}
	display_game();
	unsigned long previous_millis = 0;
	const unsigned long interval = 50 - game_difficulty_*10;
	unsigned long no_intervals = 0;
	while(true) //petla gry
	{
		Serial.println("petlaerrror!!!!");
		unsigned long current_millis = millis();
		if(current_millis-previous_millis>=interval) //wykonywanie akcji co interwal (dla easy 50ms)
		{
			no_intervals++;
			previous_millis = current_millis;
			periodic_events(no_intervals);
		}
	}
}

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

void game::display_game()
{
	tft_->fillScreen(ILI9341_BLACK);
	player_->display();
	auto tmp_enemies = enemies_;
	int i = 0;
	while(true)
	{
		tmp_enemies.getCurrent()->display();;
		Serial.println(i);
		delay(10);
		i++;
		if(!tmp_enemies.next())
		{
			Serial.println("!!!!!!!!!!!!");
			break;
		}
	} 
	Serial.println("afterwhile");
}

void game::periodic_events(unsigned long no_intervals)
{
	read_buttons();
	if (shoot_cooldown_ > 0)shoot_cooldown_--;
	if(player_bullet_)
	{
		player_bullet_->move(0, 5);
		auto tmp = enemies_;
		do
		{
			if (player_bullet_->check_collison(tmp.getCurrent()))
			{
				tmp.DeleteCurrent();
				delete(player_bullet_);
				player_bullet_ = nullptr;
				tone(BUZZER_PIN, 440, 6);
				tone(BUZZER_PIN, 320, 10);
			}
		} while (tmp.next());
		if(player_bullet_->border_collision(2)&&!player_bullet_)
		{
			delete(player_bullet_);
			player_bullet_ = nullptr;
		}
	}

}

void game::handle_buttons()
{
	if(button_state_[0]&& shoot_cooldown_ == 0&&player_bullet_==nullptr) //strzelanie
	{
		shoot_cooldown_ = 10;
		player_bullet_ = new bullet(tft_, player_->get_x() + 8, player_->get_y() + 8, 4, 8,ILI9341_CYAN);
	}
	if(button_state_[1]&& !player_->border_collision(0)) //ruch w lewo
	{
		player_->move(-5, 0);
	}
	if (button_state_[3]&& !player_->border_collision(1)) //ruch w prawo
	{
		player_->move(5, 0);
	}
}


