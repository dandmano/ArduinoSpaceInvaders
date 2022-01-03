#include "headers.h"

class entity
{
public:
	Adafruit_ILI9341 tft;
	int x, y; //2d position
	int const width, height;
	bool is_alive;
	entity(const Adafruit_ILI9341& tft, const int x, const int y, const int width, const int height, const int is_alive) :tft(tft), x(x), y(y), width(width), height(height), is_alive(is_alive) {}
	void move(const int movex, const int movey)
	{
		if (!is_alive)return;
		draw_black();
		x += movex;
		y += movey;
		draw();
	}
	bool check_collison(const entity& e) const
	{
		if (e.is_alive)return false;
		if (x<e.x + e.width && x + width>e.x && y<e.y + e.height && y + height>e.y)
			return true;
		return false;
	}
	bool virtual out_of_screen() ///240x320
	{

	}
private:
	void virtual draw()
	{
		tft.fillRect(x, y, width, height, ILI9341_RED);
		is_alive = true;
	}
	void virtual draw_black()
	{
		tft.fillRect(x, y, width, height, ILI9341_BLACK);
		is_alive = false;
	}
};

class player :public entity
{
public:
	player(Adafruit_ILI9341 tft, int x, int y, int width, int height) :entity(tft, x, y, width, height, true) {}
private:
	void draw() override
	{
		tft.fillRect(x, y, width, height, ILI9341_RED);
		is_alive = true;
	}
	void draw_black() override
	{
		tft.fillRect(x, y, width, height, ILI9341_BLACK);
		is_alive = false;
	}
};

class bullet :public entity
{
public:
	bullet(Adafruit_ILI9341 tft, int x, int y, int width, int height) :entity(tft, x, y, width, height, true) {}
private:
	void draw() override
	{
		tft.fillRect(x, y, width, height, ILI9341_ORANGE);
		is_alive = true;
	}
	void draw_black() override
	{
		tft.fillRect(x, y, width, height, ILI9341_BLACK);
		is_alive = false;
	}
};