#pragma once
#include "headers.h"
#include "entity.h"

class game
{
//game consts
	const Adafruit_ILI9341* tft_; //display screen
	const SevSeg* sevseg_; //7 segment display
//game settings
	const int game_difficulty_; 
	int* game_button_; //default for game - 0 shoot, 1 left, 2 - , 3 right
	bool button_state_[4]={false,false,false,false};
//game entities
	player player_;
	bullet* player_bullet_=nullptr;
	enemy enemies_[5][6];
	bullet* enemy_bullet_=nullptr;
//game variables
	int lives_; 
	int score_ = 0;
	int game_state_ = 1; //game started - 1, game over - 0
	int enemies_move_state_ = 1; //0-left, 1-right
	int enemies_move_state_next_ = 0; //0-left, 1-right
	int first_enemy_in_column_[6] = {0}; //row of the first enemy in column
	int curr_mov_ene_row_;
	int curr_mov_ene_col_;
	int no_enemies_;
	int no_enemies_alive_;
	int shoot_cooldown_=0;//*interval ~0,5s for easy
	int enemy_shoot_cooldown_ = 2;

public:
	game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, int game_difficulty, int* game_button, int no_enemies);
	void start_game();
private:
//functional methods
	void read_buttons();
	void display_string(const int x, const int y, const int size, const int color, const String str) const;
	void periodic_events();
	void game_end();
	void change_curr_enemy();
//display, update methods
	void display_game();
	void leds_update();
//handler functions
	void handle_buttons();
	void handle_player_bullet();
	void handle_enemies_movement();
	void handle_enemies_shoot();
};
