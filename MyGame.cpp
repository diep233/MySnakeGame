#include<iostream>
#include<string>
#include"SDL.h"
#include"MyGame.h"
#include"SDL_image.h"
#include"SDL_mixer.h"

void game::run() {
	init();
	playBackgroundMusic();
	setRundomFood();
	gameLoop();
	close();
}

void game::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Unable to initialize SDL" << SDL_GetError();
		exit(EXIT_FAILURE);
	}
	window = SDL_CreateWindow("Wellcome to my snake game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, heightBoard, widthBoard, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Unable to create window" << SDL_GetError();
	}
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
		showScores();
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
		newPoint.y = 0;
	}
	else if (newPoint.y < 0) newPoint.y = coordidateHeight - 1;
	
	SDL_Point nextBodyPoint;
	if (array[newPoint.x][newPoint.y] == food) {
		nextBodyPoint = snakeHeadPoint;
		snakeBody.push_back(nextBodyPoint);
		array[nextBodyPoint.x][nextBodyPoint.y] = body;
		array[newPoint.x][newPoint.y] = head;
		snakeSize++;
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
		quit = true;
	}

	snakeHeadPoint = newPoint;

}
void game::renderAll() {

	SDL_Rect blockPosition;
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);

	SDL_SetRenderDrawColor(render, 255, 0, 0, 0);
	blockPosition.x = foodPoint.x * 16;
	blockPosition.y = foodPoint.y * 16;
	blockPosition.w = blockPosition.h = 16;
	SDL_RenderFillRect(render, &blockPosition);

	SDL_SetRenderDrawColor(render, 255, 255, 0, 0xFF);
	blockPosition.x = snakeHeadPoint.x * 16;
	blockPosition.y = snakeHeadPoint.y * 16;
	SDL_RenderFillRect(render, &blockPosition);

	SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
	for (int i = 0; i < snakeBody.size(); ++i) {
		blockPosition.x = snakeBody[i].x * 16;
		blockPosition.y = snakeBody[i].y * 16;
		SDL_RenderFillRect(render, &blockPosition);
	}

	showScores();

	SDL_RenderPresent(render);
}

void game::setRundomFood() {
	srand(time(0));
	foodPoint.x = rand() % coordidateWidth;
	foodPoint.y = rand() % coordidateHeight + 2;
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
	effectMusic = Mix_LoadWAV("moveDirSound.wav");
	if (effectMusic == NULL) {
		cout << "Unable to load effect sound" << SDL_GetError();
	}

	Mix_PlayChannel(-1, effectMusic, 0);
}

void game::close() {
	SDL_Delay(5000);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyWindow(window);
	Mix_FreeMusic(backgroundMusic);
	Mix_FreeChunk(effectMusic);
	TTF_Quit();
	SDL_Quit();
}

void game::showScores() {
	gFont = TTF_OpenFont("OpenSans-Bold.ttf", 24);

	string title = "Snakle++ Score: " + to_string((snakeSize - 1) * 10);

	surfaceMessage = TTF_RenderText_Solid(gFont, title.c_str(), white);
	
	if (surfaceMessage == NULL) {
		cout << "Text render error" << SDL_GetError();
	}

	Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
	
	if (Message == NULL) {
		cout << "Createe Texture Error" << SDL_GetError();
	}

	srcrectMessageRect.x = (heightBoard / 2) - 100;
	srcrectMessageRect.y = 0;
	srcrectMessageRect.w = 200;
	srcrectMessageRect.h = 42;

	dstrectMessageRect.x = (heightBoard / 2) - 100 + 50;
	dstrectMessageRect.y = 0;
	dstrectMessageRect.w = 200;
	dstrectMessageRect.h = 42;

	SDL_RenderCopy(render, Message, NULL, &srcrectMessageRect);
}

