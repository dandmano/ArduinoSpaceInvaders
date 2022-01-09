#include "entity.h"

//Entity

entity::entity(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height) :tft_(tft), x_(x), y_(y), width_(width), height_(height) {}

void entity::move(const int move_x, const int move_y)
{
	if (!is_alive_)return;
	draw_black();
	x_ += move_x;
	y_ += move_y;
	draw();
}

bool entity::check_collison(const entity& e) const
{
	if (e.is_alive_)return false;
	if (x_<e.x_ + e.width_ && x_ + width_>e.x_ && y_<e.y_ + e.height_ && y_ + height_>e.y_)
		return true;
	return false;
}

bool entity::out_of_screen() ///240x320
{

}

void entity::draw()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_RED);
	is_alive_ = true;
}
void entity::draw_black()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_BLACK);
	is_alive_ = false;
}

//Player

player::player(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height) :entity(tft, x, y, width, height, true) {}

void player::draw()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_BLUE);
	is_alive_ = true;
}
void player::draw_black()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_BLACK);
	is_alive_ = false;
}

//Enemy
enemy::enemy(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height) :entity(tft, x, y, width, height, true) {}

void enemy::draw()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_RED);
	is_alive_ = true;
}
void enemy::draw_black()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_BLACK);
	is_alive_ = false;
}



//Bullet

void bullet::draw()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_ORANGE);
	is_alive_ = true;
}
void bullet::draw_black()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_BLACK);
	is_alive_ = false;
}
