#include <SDL2/SDL.h>

class Apple {
public:
    Apple(int x, int y);
    void respawn();
    SDL_Rect getRect() const;
    void render(SDL_Renderer* renderer) const;  // Marked as const

private:
    SDL_Rect rect;
};

Apple::Apple(int x, int y) {
    rect = {x, y, 10, 10};
}

void Apple::respawn() {
    rect.x = rand() % 100 * 10;
    rect.y = rand() % 100 * 10;
}

SDL_Rect Apple::getRect() const {
    return rect;
}

void Apple::render(SDL_Renderer* renderer) const {  // Marked as const
    SDL_RenderFillRect(renderer, &rect);
}

