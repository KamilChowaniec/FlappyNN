#pragma once
#include "WindowC.h"
#include "Pipe.h"
#include "NeuralNetwork.h"
class Berd
{
private:
	
	static int x;
	int y;
	int r;
	double vel;
	static WindowC* Window;
	bool alive;
	SDL_Color color;

public:
	NeuralNetwork brain;
	double fitness;
	int score;
	static void initWindow(WindowC* window) {
		Window = window;
	}
	Berd() {}
	Berd(int y, NeuralNetwork brain);
	void handle(SDL_Event& e);
	void move(vec output);
	vec feedInputs(int dist, int p_y1, int p_y2);
	void draw();
	static int getx() { return x; }
	static void setx(int ix) { x = ix; }
	void collision(Pipe& p);
	void collision();
	template<class T>
	bool isCollided(T & p) {
		return x + r >= p.x && x - r <= p.x + p.w && y + r >= p.y && y - r <= p.y + p.h;
	}
	bool isDead() { return !alive; }
	void sety(int y) { this->y = y; }
	void resurrect() { 
		this->alive = true;
		this->vel = 0;
	}
	NeuralNetwork& getNN() { return brain; }
	void reset();
};

