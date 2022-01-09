#include "game.h"

game::game(const Adafruit_ILI9341* tft, const SevSeg* sevseg, const int game_difficulty, int* game_button) :tft_(tft), sevseg_(sevseg), game_difficulty_(game_difficulty), game_button_(game_button)
{
	player_ = new player(tft, )
}
