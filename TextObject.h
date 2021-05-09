#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
using namespace std;

class TextObject {
	public:
		enum textColor
		{
			RED = 0,
			WHITE = 1,
			BLACK = 2
		};
		void setText(string str);
		void setColor(int type);
		void setRect(int x, int y, int w, int h);
		void show(SDL_Surface* textSurface, SDL_Renderer* render);
		void createText(TTF_Font* font, SDL_Surface* textSurface);
		void applySurface(SDL_Surface* textSurface, SDL_Surface* screen, int x, int y);
		SDL_Rect getRect();
	private:
		string textString;
		SDL_Color textColor;
		SDL_Rect textRect;
		SDL_Surface* textSurface = NULL;
		SDL_Texture* textTexture = NULL;
		TTF_Font* font = TTF_OpenFont("OpenSans-Bold.ttf", 30);
		SDL_Color white = { 255,255,255 };
		SDL_Color black = { 0,0,0 };
		
};