#include "stdafx.h"
#include "Berd.h"

WindowC* Berd::Window = nullptr;
int Berd::x = NULL;

Berd::Berd(int y, NeuralNetwork brain): brain(brain), y(y)
{
	r = 15;
	vel = 5;
	fitness = 0;
	score = 0;
	color = {(Uint8)(rand() % 255),(Uint8)(rand() % 255),(Uint8)(rand() % 255),(Uint8)255};
}

void Berd::handle(SDL_Event & e)
{
	switch(e.type) {
	case SDL_KEYDOWN:
		switch(e.key.keysym.sym) {
		case SDLK_SPACE:
			vel = -10;
		}

	}
}

void Berd::move(vec output)
{
	y += vel;
	vel += 0.4;
	if(vel > 20) vel = 20;
	if(output[0] > 0.5) {
		vel = -10;
	}

}

vec Berd::feedInputs(int x, int p_y1, int p_y2) {
	vec inputs(4);
	inputs[0] = y / (double)Window->getscreenheight();
	inputs[1] = x / (double)Window->getscreenwidth();
	inputs[2] = p_y1 / (double)Window->getscreenheight();
	inputs[3] = p_y2 / (double)Window->getscreenheight();
	return brain.feedforward(inputs);
}

void Berd::draw()
{
	Window->drawCircle(x, y, r, color);
}

void Berd::collision(Pipe& p)
{
	SDL_Rect PipeRect1 = {p.getx(),0,p.getwidth(),p.gety1()};
	if(isCollided(PipeRect1)) {
		alive = false;
		p.changecolor({255,0,0,255});
		return;
	}

	SDL_Rect PipeRect2 = {p.getx(),p.gety2(),p.getwidth(),Window->getscreenheight() - p.gety2()};
	if(isCollided(PipeRect2)) {
		p.changecolor({255,0,0,255});
		alive = false;
		return;
	}
}

void Berd::collision()
{
	if(y - r < 0 || y + r > Window->getscreenheight()) alive = false;

}

void Berd::reset()
{
	y = rand() % Window->getscreenheight();
	vel = 0;
	score = 0;
	fitness = 0;
	alive = true;
}

