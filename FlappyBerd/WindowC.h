#pragma once
#include "TextureC.h"
#include <math.h>
#include <vector>
#include <sstream>
class WindowC
{
private:

	SDL_Window* Window;
	const char *name;
	TTF_Font *Font;
	TextureC loadTexture(const char *path, SDL_Color colorkey = { 1,2,3,4 });
	SDL_Renderer* Renderer;
	const int s_width, s_height;
	TextureC number[11];
	TextureC circle;
public:
	TextureC loadTextTexture(const char *text, SDL_Color textColor);
	TextureC CreateTextureFromWindow();
	enum Rec { filled, empty };
	enum Line { horizontal, vertical };
	WindowC(char *s = "", int width = 800, int height = 600);
	bool init();
	void changefont(const char* path, int size);
	bool loadMedia(TextureC* textures);
	void renderTexture(TextureC texture, int x, int y, int w = 0, int h = 0, SDL_Color colormode = { 255,255,255,255 }, double angle = 0);
	void renderSpriteTexture(TextureC texture, int x, int y, int w, int h, SDL_Rect onSprite, SDL_Color colormode = { 255,255,255,255 }, double angle = 0);
	void screenUpdate();
	void screenClear(SDL_Color color = { 0,0,0,0 });
	void drawCircle(int x, int y, int r, SDL_Color color = { 255,255,255,255 });

	void drawRect(int x, int y, int w, int h, Rec = filled, SDL_Color color = { 255,255,255,255 });
	void drawLine(int x, int y, int l, Line type, SDL_Color color);
	void drawPixel(int x, int y, SDL_Color color);
	void drawnumber(int x, int y, int n);
	int numlen(int n);
	void drawnumber(int x, int y, double n);

	int getscreenwidth() { return s_width; }
	int getscreenheight() { return s_height; }
};