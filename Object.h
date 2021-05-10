#pragma once
#include<SDL.h>
#include<iostream>
using namespace std;

class Object {
	public:
		void loadImage(string str, SDL_Renderer* render);
};