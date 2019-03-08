#include "stdafx.h"
#include "Pipe.h"

WindowC* Pipe::Window = nullptr;
void Pipe::initWindow(WindowC * window)
{
	Window = window;
}

Pipe::Pipe(int x): interval(rand()%70+180), width(70), speed(4)
{
	if(x==-1) this->x = Window->getscreenwidth();
	else this->x = x;
	y1 = rand() % (int(0.8*Window->getscreenheight() - interval -2)) + 0.1*Window->getscreenheight();
	y2 = y1 + interval;
	color = { 255,255,255,255 };
}

void Pipe::move()
{
	x -= speed;
}

void Pipe::draw()
{
	Window->drawRect(x, 0, width, y1, WindowC::filled,color);
	Window->drawRect(x, y2, width, Window->getscreenheight() - y2, WindowC::filled,color);
	//color = { 255,255,255,255 };
}
