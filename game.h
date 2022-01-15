#pragma once
#include "headers.h"
#include "entity.h"

class game
{
	const Adafruit_ILI9341* tft_;
	const SevSeg* sevseg_;
	const int game_difficulty_;
	//default for game - 0 shoot, 1 left, 2 - , 3 right
	int* game_button_;
	bool button_state_[4]={false,false,false,false};
	int lives_;
	int score_ = 0;
	player player_;
	bullet *player_bullet_;
	enemy enemies_[31];
	//i-rows, 0-left, 1-right
	int enemies_move_state_[5]={ 0,1,0,1,0 };
	int no_enemies_;
	int no_enemies_alive_;
	int shoot_cooldown_=0;//*interval ~0,5s for easy
	//game started - 1, game over - 0
	int game_state_ = 1;
public:
	game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, int game_difficulty, int* game_button, int no_enemies);
	void start_game();
private:
	void read_buttons();
	void display_game();
	void display_string(const int x, const int y, const int size, const int color, const String str) const;
	void move_enemies();
	void enemy_shoot();
	void periodic_events(unsigned long no_intervals);
	void handle_buttons();
	void leds_update();
	void game_end();
	void player_bullet_handling();
};
