#pragma once
#include "headers.h"

class entity
{
protected:
	const Adafruit_ILI9341* tft_;
	int x_, y_;
	int width_, height_;
	bool is_alive_ = false;
public:
	entity(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
//getters
	int get_x() const;
	int get_y() const;
	int get_width() const;
	int get_height() const;
	bool get_is_alive() const;
//functional methods
	void display();
	void kill();
	void move(const int move_x, const int move_y);
	bool check_collison(const entity* e) const;
	//0-left,1-right,2-up,3-down
	bool virtual border_collision(int side);
protected:
	void virtual draw();
	void draw_black();
};

class player :public entity
{
public:
	player(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
private:
	void draw() override;
};


class enemy :public entity
{
public:
	enemy(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
	enemy();
	void put_variables(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height);
private:
	void draw() override;
};

class bullet :public entity
{
public:
	bullet(const Adafruit_ILI9341* tft, const int x, const int y, const int width, const int height, const long long color);
private:
	long long color_;
	void draw() override;
};
