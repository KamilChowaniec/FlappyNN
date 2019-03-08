#include "stdafx.h"
#include "GameC.h"
#include <time.h>
#include "NeuralNetwork.h"
using namespace std;

GameC::GameC(unsigned int width, unsigned int height): Window("Flappy Berd", width, height), s_width(width), s_height(height), max_pop(500)
{
	dra = !true;
	del = !true;
	pop_score = 0;
	overall_score = 0;
	gen = 1;
	Window.loadMedia(nullptr);
	srand(time(NULL));
	Berd::setx(50);
	Berd::initWindow(&Window);
	Pipe::initWindow(&Window);
	Timer = SDL_GetTicks();
	pop = max_pop;
	for(int i = 0; i < max_pop; i++) {
		berds.push_back((Berd(rand() % (Window.getscreenheight() - 15) + 15, NeuralNetwork(4, 8, 1))));
	}
	initPipes();
}

void GameC::initPipes() {
	pipes.clear();
	for(int i = 0; i < 4; i++) {
		pipes.push_back(Pipe((i + 1)*0.25*Window.getscreenwidth()));
	}
}


void GameC::start()
{
	while(true) {
		handle();
		mechanic();
		if(dra)drawScene();
		delay();
	}
}

void GameC::mechanic()
{
	for(auto& p : pipes) {
		p.move();
	}
	if(pipes.front().isDead()) {
		pipes.pop_front();
		pipes.push_back(Pipe());
	}

	auto& nextPipe = getNext();
	for(auto& berd : berds) {
		if(!berd.isDead()) {
			berd.score++;
			berd.move(berd.feedInputs(nextPipe.getx(), nextPipe.gety1(), nextPipe.gety2()));
			berd.collision(nextPipe);
			berd.collision();
			if(berd.isDead()) {
				pop--;
			}
		}
	}
	if(pop == 0) {
		repopulate();
		cout << "Generacja " << gen << endl;
		cout << "Population score = " << pop_score << endl;
		cout << "Overall score    = " << overall_score << endl << endl;
		gen++;
	}
}

void GameC::repopulate() {
	pop = max_pop;

	calculateFitness();

	vector<Berd> newBerds;
	newBerds.resize(max_pop);

	for(int i = 0; i < max_pop; i++) {
		double r = rand() / double(RAND_MAX);
		if(r < 0.99)
			newBerds[i] = Berd(rand() % (Window.getscreenheight() - 15) + 15, NeuralNetwork::crossover2(pickOne().brain, pickOne().brain));
		else
			newBerds[i] = pickOne();
	}
	berds.clear();
	berds.resize(max_pop);
	for(int i = 0; i < newBerds.size(); i++) {
		berds[i] = newBerds[i];
		berds[i].reset();
		double r = rand() / double(RAND_MAX);
		if(r < 0.1)
			berds[i].brain.mutate(0.1, 0.01);

	}
	initPipes();
}

Berd GameC::pickOne() {
	double r = (rand() / (double)RAND_MAX);
	int i = 0;
	for(i = 0; i < berds.size() && ((r -= berds[i].fitness) > 0); i++);
	if(i >= berds.size()) i = berds.size() - 1;
	return berds[i];

	/*int wybor;
	int max = 0;
	for (int i = 0; i < berds.size(); i++) {
		if (berds[i].score > max) {
			max = berds[i].score;
			wybor = i;
		}
	}
	return berds[wybor];*/
}

void GameC::calculateFitness() {
	int sum = 0;
	pop_score = 0;
	for(auto& berd : berds) {
		sum += berd.score;
		if(berd.score > pop_score) pop_score = berd.score;
	}
	if(pop_score > overall_score) overall_score = pop_score;

	for(auto& berd : berds)
		berd.fitness = berd.score / (double)sum;
}

void GameC::drawScene()
{
	Window.screenClear();
	for(auto& p : pipes) p.draw();
	for(auto& berd : berds) if(!berd.isDead()){
		berd.draw();
	}
	Window.screenUpdate();
}

void GameC::delay()
{
	int d = 15 - (SDL_GetTicks() - Timer);
	if(del) SDL_Delay(d > 0 ? d : 0);
	Timer = SDL_GetTicks();
}

void GameC::handle()
{
	while(SDL_PollEvent(&e) > 0) {
		if(e.type == SDL_QUIT) exit(0);
		if(e.type == SDL_KEYDOWN) {
			if(e.key.keysym.sym == SDLK_ESCAPE) {
				exit(NULL);
			}
			if(e.key.keysym.sym == SDLK_SPACE) {
				del = !del;
			}
			if(e.key.keysym.sym == SDLK_d) {
				dra = !dra;
			}
		}

		//for (auto& berd : berds) if(!berd.isDead()) berd.handle(e);
	}
}

Pipe& GameC::getNext() {
	for(auto& p : pipes) {
		if(p.getx() + p.getwidth() - Berd::getx() - 15 > 0) return p;
	}
}