#pragma once
#include "WindowC.h"

class Pipe
{
private:
	static WindowC* Window;
	int x;
	int y1, y2;
	const int interval;
	const int width;
	const int speed;
	SDL_Color color;
public:
	static void initWindow(WindowC* window);
	Pipe(int x = -1);

	void move();
	void draw();

	bool isDead() { return x < -width; }
	int getx() { return x; }
	int gety1() { return y1; }
	int gety2() { return y2; }
	int getwidth() { return width; }
	void changecolor(SDL_Color c) { color = c; }
};

