#include <SDL2/SDL.h>

int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;

	enum Direction{
		DOWN,
		LEFT,
		RIGHT,
		UP
	};

	bool running = true;
	int dir =0;
	SDL_Rect head {500,500,10,10};
	while(running){
		// check input
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT) { running = false; }
			if(e.type == SDL_KEYDOWN) {
				if(e.key.keysym.sym == SDLK_DOWN) { dir = DOWN;  }
				if(e.key.keysym.sym == SDLK_UP)   { dir = UP;    }
				if(e.key.keysym.sym == SDLK_LEFT) { dir = LEFT;  }
				if(e.key.keysym.sym == SDLK_RIGHT){ dir = RIGHT; }
			}
		}
		// Move
		switch(dir){
			case DOWN:
				head.y += 10; break;
			case UP:
				head.y -= 10; break;
			case LEFT:
				head.x -= 10; break;
			case RIGHT:
				head.x += 10; break;
		}	
		// Clear Window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw Body
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &head);

		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}	
	return 0;
}
