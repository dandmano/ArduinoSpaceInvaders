#pragma once
#include "headers.h"
#include "entity.h"

class game
{
	const Adafruit_ILI9341* tft_;
	const SevSeg* sevseg_;
	const int game_difficulty_;
	int* game_button_;
	int lives_;
	const player player_;
	arx::vector <enemy> enemies_;
	arx::vector <bullet> bullets_;
public:
	game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, const int game_difficulty, int* game_button);
	void start_game();
private:
	void display_game();
	void periodic_events();

};
