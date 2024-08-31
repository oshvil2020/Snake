#include <SDL2/SDL.h>
#include <vector>
#include <deque>
#include <algorithm>
#include "Snake.h"
#include "Apple.h"

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Snake snake;
    std::vector<Apple> apples;
    bool running;
    int dir;

    void handleEvents();
    void update();
    void render();
};

Game::Game() : running(true), dir(0) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    for (int i = 0; i < 100; ++i) {
        apples.emplace_back(rand() % 100 * 10, rand() % 100 * 10);
    }
}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(25);
    }
}

void Game::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_DOWN) { dir = Snake::DOWN; }
            if (e.key.keysym.sym == SDLK_UP) { dir = Snake::UP; }
            if (e.key.keysym.sym == SDLK_LEFT) { dir = Snake::LEFT; }
            if (e.key.keysym.sym == SDLK_RIGHT) { dir = Snake::RIGHT; }
        }
    }
}

void Game::update() {
    snake.move(dir);

    for (auto& apple : apples) {
        if (snake.checkCollision(apple.getRect())) {
            snake.grow();
            apple.respawn();
        }
    }

    snake.checkSelfCollision();
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    snake.render(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (const auto& apple : apples) {
        apple.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

