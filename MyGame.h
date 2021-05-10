#pragma once
#include<iostream>
#include<vector>
#include<SDL.h>
#include"SDL_image.h"
#include"SDL_mixer.h"
#include"SDL_ttf.h"
#include"TextObject.h"

using namespace std;

class game {

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
	SDL_Surface* backgroundImageSurface = NULL;
	SDL_Surface* textSurface = NULL;
	SDL_Surface* screen = NULL;
	SDL_Event event;
	SDL_Renderer* render = NULL;
	SDL_Color white = { 255,255,255 };
	SDL_Color black = { 0,0,0 };
	SDL_Texture* messageTexture;
	SDL_Rect srcrectMessageRect;
	SDL_Rect dstrectMessageRect;
	SDL_Rect blockPosition;

	Mix_Chunk* effectMusic = NULL;
	Mix_Music* backgroundMusic = NULL;

	enum direction { LEFT, RIGHT, UP, DOWN };
	enum block { head, body, food, empty };

	direction dir = RIGHT;

	SDL_Point snakeHeadPoint = { 2, 2 };
	SDL_Point foodPoint = { 0, 0 };
	vector<SDL_Point> snakeBody;
	block array[coordidateHeight][coordidateWidth];

	public: 
		void run();
		void playBackgroundMusic();
		void init();
		void showScores();
		void gameLoop();
		void keyBoardEvent();
		void update();
		void renderAll();
		void setRundomFood();
		void playSoundEffect();
		void close();
		void loadBackgroundImage();
		SDL_Texture* loadImage(string str);
		int showMenu();
		void displayResourceNAMessageBox();
		bool checkMouse();
		void showGameOver();
};
