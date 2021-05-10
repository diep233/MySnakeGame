#include<iostream>
#include<windows.h>
#include<string>
#include"SDL.h"
#include"MyGame.h"
#include"SDL_image.h"
#include"SDL_mixer.h"

void game::run() {
	init();
	playBackgroundMusic();
	int indexMenu = showMenu();
	if (indexMenu == 0) {
		setRundomFood();
		gameLoop();
		close();
	}
	else {
		close();
	}
}

void game::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Unable to initialize SDL" << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	window = SDL_CreateWindow("Wellcome to my snake game!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, heightBoard, widthBoard, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Unable to create window" << SDL_GetError();
	}
	screen = SDL_GetWindowSurface(window);
	render = SDL_CreateRenderer(window, -1, 0);

	for (int i = 0; i < coordidateHeight; ++i) {
		for (int j = 0; j < coordidateWidth; ++j)
			array[i][j] = empty;
	}

	if (TTF_Init() == -1) {
		cout << "TTF Initialization Error" << TTF_GetError();
	}
}
void game::gameLoop() {
	while (!quit) {
		timeStartAFrame = SDL_GetTicks();

		keyBoardEvent();
		update();
		renderAll();
		timeRenderAFrame = SDL_GetTicks() - timeStartAFrame;

		if (timeRenderAFrame < DELAY_TIME) {
			SDL_Delay(100);
		}
	}
}
void game::keyBoardEvent() {
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
						dir = LEFT;
					}
				break;
			}
		}
	}

}

void game::update() {
	SDL_Point newPoint = snakeHeadPoint;
	switch (dir)
	{
	case LEFT:
		newPoint.x -= 1;
		
		break;
	case RIGHT:
		newPoint.x += 1;

		break;
	case UP:
		newPoint.y -= 1;
		break;
	case DOWN:
		newPoint.y += 1;
		break;
	}

	if (newPoint.x > coordidateWidth - 1)
	{
		newPoint.x = 0;
	}
	else if (newPoint.x < 0) newPoint.x = coordidateWidth - 1;

	if (newPoint.y > coordidateHeight - 1)
	{
		newPoint.y = 2;
	}
	else if (newPoint.y < 2) newPoint.y = coordidateHeight - 1;
	
	SDL_Point nextBodyPoint;
	nextBodyPoint = snakeHeadPoint;
	if (array[newPoint.x][newPoint.y] == food) {
		snakeBody.push_back(nextBodyPoint);
		array[nextBodyPoint.x][nextBodyPoint.y] = body;
		array[newPoint.x][newPoint.y] = head;
		snakeSize++;

		playSoundEffect();
		setRundomFood();
	}
	else if (array[newPoint.x][newPoint.y] == empty) {
		nextBodyPoint = snakeHeadPoint;
		array[newPoint.x][newPoint.y] = head;
		if (snakeSize == 1) {
			array[nextBodyPoint.x][nextBodyPoint.y] = empty;
		}
		else {
			array[nextBodyPoint.x][nextBodyPoint.y] = body;
			array[snakeBody[0].x][snakeBody[0].y] = empty;
			for (int i = 0; i < snakeBody.size() - 1; ++i) {
				snakeBody[i] = snakeBody[i + 1];
			}
			snakeBody[snakeBody.size() - 1] = nextBodyPoint;
		}
	}
	else {
		snakeBody.push_back(nextBodyPoint);
		array[newPoint.x][newPoint.y] = head;
		//showGameOver();
		displayResourceNAMessageBox();
		quit = true;
	}

	snakeHeadPoint = newPoint;

}
void game::renderAll() {

	SDL_Rect blockPosition;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);

	loadBackgroundImage();

	SDL_SetRenderDrawColor(render, 61, 199, 16, 0);
	blockPosition.x = foodPoint.x * 16;
	blockPosition.y = foodPoint.y * 16;
	blockPosition.w = blockPosition.h = 16;
	SDL_RenderFillRect(render, &blockPosition);

	SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
	for (int i = 0; i < snakeBody.size(); ++i) {
		blockPosition.x = snakeBody[i].x * 16;
		blockPosition.y = snakeBody[i].y * 16;
		SDL_RenderFillRect(render, &blockPosition);
	}

	SDL_SetRenderDrawColor(render, 242, 209, 17, 0xFF);
	blockPosition.x = snakeHeadPoint.x * 16;
	blockPosition.y = snakeHeadPoint.y * 16;
	SDL_RenderFillRect(render, &blockPosition);

	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	blockPosition.x = 0;
	blockPosition.y = 0;
	blockPosition.w = 640;
	blockPosition.h = 32;
	SDL_RenderFillRect(render, &blockPosition);

	showScores();

	SDL_RenderPresent(render);
}

void game::setRundomFood() {
	srand(time(0));
	foodPoint.x = rand() % 40;
	foodPoint.y = rand() % 38 + 2;
	array[foodPoint.x][foodPoint.y] = food;
}
void game::playBackgroundMusic() {
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
void game::playSoundEffect() {
	effectMusic = Mix_LoadWAV("beep.wav");
	if (effectMusic == NULL) {
		cout << "Unable to load effect sound" << SDL_GetError();
	}

	Mix_PlayChannel(-1, effectMusic, 0);
}

void game::close() {
	SDL_Delay(1000);
	SDL_FreeSurface(textSurface);
	SDL_DestroyWindow(window);
	Mix_FreeMusic(backgroundMusic);
	Mix_FreeChunk(effectMusic);
	TTF_Quit();
	SDL_Quit();
}

void game::showScores() {

	TextObject showScore;
	showScore.setText("Snake++ Score: " + to_string((snakeSize - 1) * 10));
	showScore.setColor(TextObject::WHITE);
	showScore.setRect((heightBoard / 2) - 100, 0, 200, 42);
	showScore.show(render);
}

void game::loadBackgroundImage() {
	SDL_Texture* loadBackgroundImg = loadImage("ImageBackground3.bmp");
	SDL_RenderCopy(render, loadBackgroundImg, NULL, NULL);

}

void game::displayResourceNAMessageBox()
{
	int msgboxID = MessageBox(
		NULL,
		(LPCWSTR)L"GAME OVER!",
		(LPCWSTR)L"GAME OVER!",
		 MB_OK | MB_DEFBUTTON2
	);
}

SDL_Texture* game::loadImage(string str) {
	SDL_Surface* imageSurface = NULL;
	SDL_Texture* backgroundImageTexture = NULL;
	imageSurface = SDL_LoadBMP(str.c_str());
	if (imageSurface == NULL) {
		cout << "Load background image error" << SDL_GetError();
	}
	backgroundImageTexture = SDL_CreateTextureFromSurface(render, imageSurface);
	
	return backgroundImageTexture;

}

bool checkMouseCoordidate(int xMouse, int yMouse, SDL_Rect rect) {
	if (xMouse >= rect.x && xMouse <= rect.x + rect.w &&
		yMouse >= rect.y && yMouse <= rect.y + rect.h)
		return true;
	return false;
}

int game::showMenu() {
	TTF_Font* font = TTF_OpenFont("OpenSans-Bold.ttf", 50);
	SDL_Texture* loadImg = loadImage("ImageBackground1.bmp");
	SDL_RenderCopy(render, loadImg, NULL, NULL);
	//loadImage("ImageBackground1.bmp", render);
	const int menuItem = 2;

	SDL_Rect arr[menuItem];

	TextObject text[menuItem];
	text[0].setText("Play Game");
	text[0].setColor(TextObject::YELLOW);
	text[0].setRect(210, 400, 200, 50);

	text[1].setText("Exit");
	text[1].setColor(TextObject::YELLOW);
	text[1].setRect(210, 500, 80, 50);
	
	bool running = true;
	while (running) {
		for (int i = 0; i < menuItem; ++i) {
			text[i].show(render);
		}
		SDL_Event event;
		int xMouse;
		int yMouse;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					return 1;
					break;
				case SDL_MOUSEMOTION:
				{
					xMouse = event.motion.x;
					yMouse = event.motion.y;
					for (int i = 0; i < menuItem; ++i) {

						if (checkMouseCoordidate(xMouse, yMouse, text[i].getRect())) {
							text[i].setColor(TextObject::GREEN);
						}
						else {
							text[i].setColor(TextObject::YELLOW);
						}
					}
				}
					break;
				case SDL_MOUSEBUTTONDOWN:
				{
					xMouse = event.motion.x;
					yMouse = event.motion.y;
					for (int i = 0; i < menuItem; ++i) {

						if (checkMouseCoordidate(xMouse, yMouse, text[i].getRect()))
							return i;
					}
				}
				break;
			}
		}
	}
				
}

void game::showGameOver() {
	TTF_Font* font = TTF_OpenFont("OpenSans-Bold.ttf", 50);
	SDL_Texture* loadImg = loadImage("ImageBackground1.bmp");
	SDL_RenderCopy(render, loadImg, NULL, NULL);
	TextObject gameOverText;
	gameOverText.setText("GAME OVER");
	gameOverText.setColor(TextObject::YELLOW);
	gameOverText.setRect(210, 400, 200, 50);
	gameOverText.show(render);
}
