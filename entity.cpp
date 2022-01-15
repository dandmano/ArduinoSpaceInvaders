#include "entity.h"

//Entity

entity::entity(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height) :
	tft_(tft),
	x_(x),
	y_(y),
	width_(width),
	height_(height) {}


void entity::move(const int move_x, const int move_y)
{
	if (!is_alive_)return;
	draw_black();
	x_ += move_x;
	y_ += move_y;
	draw();
}

void entity::display()
{
	draw();
}

void entity::kill()
{
	draw_black();
	is_alive_ = false;
}

bool entity::check_collison(const entity* e) const
{
	if (!is_alive_ || !e->get_is_alive())
		return false;
	if (x_<e->x_ + e->width_ && x_ + width_>e->x_ && y_<e->y_ + e->height_ && y_ + height_>e->y_)
		return true;
	return false;
}

//0-left,1-right,2-up,3-down screen-240x320
bool entity::border_collision(const int side) 
{
	switch (side)
	{
	case 0:
		if (x_ <= 0)return true;
		return false;
	case 1:
		if (x_+width_ >= 240)return true;
		return false;
	case 2:
		if (y_ <= 0)return true;
		return false;
	case 3:
		if (y_+height_ >= 320)return true;
		return false;
	default:
		Serial.println("ERROR");
		return false;
	}
}

int entity::get_x() const
{
	return x_;
}

int entity::get_y() const
{
	return y_;
}

int entity::get_width() const
{
	return width_;
}

int entity::get_height() const
{
	return height_;
}

bool entity::get_is_alive() const
{
	return is_alive_;
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
player::player(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height) :entity(tft, x, y, width, height) {}


void player::draw()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_BLUE);
	is_alive_ = true;
}


//Enemy
enemy::enemy(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height) :entity(tft, x, y, width, height) {}

enemy::enemy() :entity(nullptr,0,0,0,0) {}

void enemy::put_variables(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height)
{
	tft_ = tft;
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}

void enemy::draw()
{
	tft_->fillRect(x_, y_, width_, height_, ILI9341_RED);
	is_alive_ = true;
}


//Bullet
bullet::bullet(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height, const long long color):entity(tft,x,y,width,height),color_(color)
{

}

void bullet::draw()
{
	tft_->fillRect(x_, y_, width_, height_, color_);
	is_alive_ = true;
}

