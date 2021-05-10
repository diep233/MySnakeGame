#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
using namespace std;

class TextObject {
	public:
		enum textColor
		{
			GREEN = 0,
			YELLOW = 1,
			WHITE = 2
		};
		void setText(string str);
		void setColor(int type);
		void setRect(int x, int y, int w, int h);
		void show(SDL_Renderer* render);
		void applySurface(SDL_Surface* textSurface, SDL_Surface* screen, int x, int y);
		string getText();
		SDL_Rect getRect();
	private:
		string textString;
		SDL_Color textColor;
		SDL_Rect textRect;
		SDL_Surface* textSurface = NULL;
		SDL_Texture* textTexture = NULL;
		TTF_Font* font = TTF_OpenFont("OpenSans-Bold.ttf", 24);
};