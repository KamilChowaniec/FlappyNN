#pragma once
#include "WindowC.h"
#include "Pipe.h"
#include "Berd.h"
#include <vector>
#include <list>
using namespace std;

class GameC
{
private:
	bool dra;
	bool del;
	int pop_score;
	int overall_score;
	int gen;
	int pop;
	const int max_pop;
	Uint32 Timer;
	SDL_Event e;
	vector<Berd> berds;
	list<Pipe> pipes;
	WindowC Window;
	const int s_width;
	const int s_height;
public:
	GameC(unsigned int width=1600, unsigned int height=900);
	void initPipes();
	void start();
	void mechanic();
	void repopulate();
	Berd pickOne();
	void calculateFitness();
	void drawScene();
	void delay();
	void handle();

	Pipe & getNext();

};

