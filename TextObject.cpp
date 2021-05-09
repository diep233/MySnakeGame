#include<SDL.h>
#include"TextObject.h"
using namespace std;

void TextObject::setText(string str) {
	textString = str;
}

void TextObject::setColor(int type) {
	if (type == RED) {
		textColor = { 255,0,0 };
	}
	else if (type == BLACK) {
		textColor = { 0,0,0 };
	}
	else if(type == WHITE) {
		textColor = { 255,255,255 };
	}
}

void TextObject::setRect(int x, int y, int w, int h) {
	textRect.x = x;
	textRect.y = y;
	textRect.w = w;
	textRect.h = h;
}

SDL_Rect TextObject::getRect() {
	return textRect;
}

void TextObject::show(SDL_Surface* screenSurface, SDL_Renderer* render) {
	textSurface = TTF_RenderText_Solid(font, textString.c_str(), textColor);

	if (textSurface == NULL) {
		cout << "textSurface error!" << SDL_GetError();
	}

	textTexture = SDL_CreateTextureFromSurface(render, textSurface);

	if (textTexture == NULL) {
		cout << "Create Texture Error!" << SDL_GetError();
	}

	SDL_RenderCopy(render, textTexture, NULL, &textRect);

	SDL_RenderPresent(render);
}