#pragma once
#include "headers.h"

class entity
{
protected:
	const Adafruit_ILI9341* tft_;
	int x_, y_; //2d position
	int const width_, height_;
	bool is_alive_ = false;
public:
	entity(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
	void move(const int move_x, const int move_y);
	bool check_collison(const entity& e) const;
	bool virtual out_of_screen();
protected:
	void virtual draw();
	void virtual draw_black();
};

class player :public entity
{
public:
	player(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
private:
	void draw() override;
	void draw_black() override;
};


class enemy :public entity
{
public:
	enemy(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
private:
	void draw() override;
	void draw_black() override;
};

class bullet :public entity
{
public:
	bullet(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
private:
	void draw() override;
	void draw_black() override;
};
