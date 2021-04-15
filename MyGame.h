#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>
#include"SDL_image.h"
#include"SDL_mixer.h"

using namespace std;

class game{

	const int heightBoard = 640;
	const int widthBoard = 640;
	const static int coordidateWidth = 40;
	const static int coordidateHeight = 40;
	const int FPS = 60;
	const int DELAY_TIME = 1000 / FPS;

	int snakeSize = 1;

	Uint32 timeStartAFrame;
	Uint32 timeRenderAFrame;

	bool quit = false;

	SDL_Window* window = NULL;
	SDL_Surface* gScreenSurFace = NULL;
	
	SDL_Event event;

	Mix_Chunk* effectMusic = NULL;
	Mix_Music* backgroundMusic = NULL;

	enum direction { LEFT, RIGHT, UP, DOWN };
	enum block { head, body, food, empty };

	direction dir = RIGHT;
	direction beforeDir = RIGHT;

	SDL_Point snakeHeadPoint = { 2, 2 };
	SDL_Point foodPoint;
	vector<SDL_Point> snakeBody;
	block array[coordidateHeight][coordidateWidth];

	public: 
		SDL_Renderer* render = NULL;
		void createBody(int number);
		void run();
		void playBackgroundMusic();
		void init();
		void gameLoop();
		void keyBoardEvent();
		void update();
		void renderAll();
		void setRundomFood();
		void playSoundEffect();
		void close();
};
