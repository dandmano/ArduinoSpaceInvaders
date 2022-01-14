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
	player player_;
	bullet *player_bullet_;
	enemy enemies_[31];
	int no_enemies_;
	int shoot_cooldown_=0;//*interval ~0,5s for easy
	
public:
	game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, int game_difficulty, int* game_button, int no_enemies);
	~game();
	void start_game();
	void read_buttons();
private:
	void display_game();
	void periodic_events(unsigned long no_intervals);
	void handle_buttons();
};
