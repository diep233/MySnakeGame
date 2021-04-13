#pragma once
#include<vector>
#include<SDL.h>

class snake {
	int a;
};

class snakeBody {
	int b;
};

class snakeTail {
	int c;
};

class snakek{
	public:
		int x, y;
		int x0, y0;
		void loop();
		void update();
		void run();
		/*snakeHead head;
		snakeTail tail;
		vector<snakeBody> body;*/
		SDL_Rect snakePosition;
};
