#include<iostream>
#include<SDL.h>
#include"Object.h"
using namespace std;

void loadImage(string str , SDL_Renderer* render) {
		SDL_Surface* imageSurface = NULL;
		SDL_Texture* backgroundImageTexture = NULL;
		imageSurface = SDL_LoadBMP(str.c_str());
		if (imageSurface == NULL) {
			cout << "Load background image error" << SDL_GetError();
		}
		backgroundImageTexture = SDL_CreateTextureFromSurface(render, imageSurface);
		SDL_RenderCopy(render, backgroundImageTexture, NULL, NULL);
}