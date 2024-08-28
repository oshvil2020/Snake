#include <SDL2/SDL.h>

int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, 
					SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;
	bool running = true;

	while(running){
		// check input
		while(SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT) { running = false; }
		}
		// Move


		// Clear Window
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw Body
		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}	
	return 0;
}
