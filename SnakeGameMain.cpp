#include<iostream>
#include"SDL.h"
#include"SDL_image.h"
#include"SDL_mixer.h"
using namespace std;

const int heightBoard = 640;
const int widthBoard = 640;
const int gridWidth = 20;
const int gridHeight = 20;
const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

int foodX, foodY;
int snakeSize = 1;

Uint32 timeStartAFrame;
Uint32 timeRenderAFrame;

bool quit = false;

string path;

SDL_Window* window = NULL;
SDL_Surface* gScreenSurFace = NULL;
SDL_Surface* gHeadImage = NULL;
SDL_Surface* foodImage = NULL;
SDL_Renderer* render = NULL;
SDL_Texture* texture = NULL;
SDL_Texture* foodTexture = NULL;
SDL_Event event;
SDL_Rect headImage_Position;
SDL_Rect foodImage_Position;

Mix_Chunk* effectMusic = NULL;
Mix_Music* backgroundMusic = NULL;

enum direction { LEFT, RIGHT, UP, DOWN };
enum block {head, body, food, empty};

direction dir = RIGHT;
direction beforeDir = RIGHT;

void initWindow();
void gameLoop();
void keyBoardEvent();
void update();
void renderAll();
void setRundomFood();
void playBackgroundMusic();
void playSoundEffect();
void close();
void checkPosion();

class position {
public:
	int x_coordinate, y_coordinate;
	position(int x, int y) {
		x_coordinate = x;
		y_coordinate = y;
	}
};

class snake
{	
	
public:
	void drawSnakeHead() {
		headImage_Position.x = headImage_Position.y = 100;
		headImage_Position.w = headImage_Position.h = 20;
	
		gHeadImage = IMG_Load("png.png");
		texture = SDL_CreateTextureFromSurface(render, gHeadImage);

		SDL_RenderCopy(render, texture, NULL, &headImage_Position);
		SDL_RenderPresent(render);
	}
};

/*class snakeBody
{
public:
	snakeBody();
	~snakeBody();
};

class snakeTail
{
public:
	snakeTail();
	~snakeTail();
};*/

int main(int argc, char* argv[]) {

	initWindow();
	return 0;
}

//Initializes the subsystems
void initWindow() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "unable to initialize SDL" << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	window = SDL_CreateWindow("Wellcome to my snake game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, heightBoard, widthBoard, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "unable to create window" << SDL_GetError();
	}
	else
	{
		gScreenSurFace = SDL_GetWindowSurface(window);
	}

	playBackgroundMusic();

	render = SDL_CreateRenderer(window, -1, 0);

	snake sHead;
	setRundomFood();

	sHead.drawSnakeHead();

	gameLoop();
	close();

}

void close() {
	SDL_Delay(200);
	SDL_FreeSurface(gHeadImage);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	Mix_FreeMusic(backgroundMusic);
	Mix_FreeChunk(effectMusic);
	SDL_Quit();
}


//Play background music

void playBackgroundMusic() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout << SDL_GetError();
	}
	backgroundMusic = Mix_LoadMUS("BackgroundMusic.mp3");
	if (backgroundMusic == NULL) {
		cout << "Unable to load music" << SDL_GetError();
	}
	Mix_PlayMusic(backgroundMusic, -1);
}

void playSoundEffect() {
	effectMusic = Mix_LoadWAV("moveDirSoun.wav");
	if (effectMusic == NULL) {
		cout << "Unable to load effect sound" << SDL_GetError();
	}

	Mix_PlayChannel(-1, effectMusic, 0);
}

void check() {
	int count = 0;
	switch (beforeDir)
	{
	case RIGHT:
		if (headImage_Position.x % 20) break;
		while (count * 20 - headImage_Position.x < 0)
			count++;
		while (headImage_Position.x != count * 20) {
			timeStartAFrame = SDL_GetTicks();
			headImage_Position.x++;
			renderAll();
			timeRenderAFrame = SDL_GetTicks() - timeStartAFrame;

			if (timeRenderAFrame < DELAY_TIME) {
				SDL_Delay(DELAY_TIME - timeRenderAFrame);
			}
		}
		break;
	case LEFT:
		if (headImage_Position.x % 20) break;
		while (headImage_Position.x - (count * 20) > 20)
			count++;
		while (headImage_Position.x != count * 20) {
			timeStartAFrame = SDL_GetTicks();
			headImage_Position.x --;
			renderAll();
			timeRenderAFrame = SDL_GetTicks() - timeStartAFrame;

			if (timeRenderAFrame < DELAY_TIME) {
				SDL_Delay(DELAY_TIME - timeRenderAFrame);
			}
		}
		break;
	case UP:
		if (headImage_Position.y % 20) break;
		while (headImage_Position.y - (count * 20) > 20)
			count++;
		while (headImage_Position.y != count * 20) {
			timeStartAFrame = SDL_GetTicks();
			headImage_Position.y --;
			renderAll();
			timeRenderAFrame = SDL_GetTicks() - timeStartAFrame;

			if (timeRenderAFrame < DELAY_TIME) {
				SDL_Delay(DELAY_TIME - timeRenderAFrame);
			}
		}
		break;
	case DOWN:
		if (headImage_Position.y % 20) break;
		while ((count * 20) - headImage_Position.y < 0)
			count++;
		while(headImage_Position.y != count * 20) {
			timeStartAFrame = SDL_GetTicks();
			headImage_Position.y++;
			renderAll();
			timeRenderAFrame = SDL_GetTicks() - timeStartAFrame;

			if (timeRenderAFrame < DELAY_TIME) {
				SDL_Delay(DELAY_TIME - timeRenderAFrame);
			}
		}
		break;
	}
}

void keyBoardEvent() {

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quit = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_DOWN:
				if (dir != UP || snakeSize == 1) {
					if (dir == DOWN) {
						break;
					}
					else {
						playSoundEffect();
						dir = DOWN;
					}

				}
				break;
			case SDLK_UP:
				if (dir != DOWN || snakeSize == 1) {
					if (dir == UP) {
						break;
					}
					else {
						playSoundEffect();
						dir = UP;
					}
				}
				break;
			case SDLK_RIGHT:
				if (dir != LEFT || snakeSize == 1) {
					if (dir == RIGHT) {
						break;
					}
					else {
						playSoundEffect();
						dir = RIGHT;
					}
				}
				break;
			case SDLK_LEFT:
				if (dir != RIGHT || snakeSize == 1)
					if (dir == LEFT) {
						break;
					}
					else {
						playSoundEffect();
						dir = LEFT;
					}
				break;
			}
		}
	}

}

void setRundomFood() {
	srand(time(0));
	//(rand() % 32) * 20
	foodImage_Position.x = 1;
	foodImage_Position.y = 100;
	foodImage_Position.w = foodImage_Position.h = 20;
	foodImage = SDL_LoadBMP("foodImage.bmp");
	foodTexture = SDL_CreateTextureFromSurface(render, foodImage);
}

void gameLoop() {
	while (!quit) {
		timeStartAFrame = SDL_GetTicks();

		keyBoardEvent();
		update();
		renderAll();

		timeRenderAFrame = SDL_GetTicks() - timeStartAFrame;

		if (timeRenderAFrame < DELAY_TIME) {
			SDL_Delay(DELAY_TIME - timeRenderAFrame);
		}
	}
}

void renderAll() {

	SDL_RenderClear(render);

	//Render food
	SDL_RenderCopy(render, foodTexture, NULL, &foodImage_Position);
	//Render Head
	SDL_RenderCopy(render, texture, NULL, &headImage_Position);



	SDL_RenderPresent(render);
}

void update() {

	switch (dir)
	{
	case LEFT:
		check();
		headImage_Position.x -= 1;
		beforeDir = dir;
		break;
	case RIGHT:
		check();
		headImage_Position.x += 1;
		beforeDir = dir;
		break;
	case UP:
		check();
		headImage_Position.y -= 1;
		beforeDir = dir;
		break;
	case DOWN:
		check();
		headImage_Position.y += 1;
		beforeDir = dir;
		break;
	}

	if (headImage_Position.x > widthBoard - 1)
	{
		headImage_Position.x = -20;
	}
	else if (headImage_Position.x < -19) headImage_Position.x = widthBoard - 1;

	if (headImage_Position.y > heightBoard - 1)
	{
		headImage_Position.y = 0;
	}
	else if (headImage_Position.y < -19) headImage_Position.y = heightBoard - 1;

	if (headImage_Position.x == foodImage_Position.x && headImage_Position.y == foodImage_Position.y) {
		foodImage_Position.x = (rand() % 32) * 20;
		foodImage_Position.y = 100;
	}
}

