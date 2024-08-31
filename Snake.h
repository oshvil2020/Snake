#include <SDL2/SDL.h>
#include <deque>

class Snake {
public:
    enum Direction { DOWN, LEFT, RIGHT, UP };

    Snake();
    void move(int dir);
    void grow();
    bool checkCollision(const SDL_Rect& rect);
    void checkSelfCollision();
    void render(SDL_Renderer* renderer);

private:
    std::deque<SDL_Rect> body;
    int size;
};

Snake::Snake() : size(1) {
    body.push_front({500, 500, 10, 10});
}

void Snake::move(int dir) {
    SDL_Rect head = body.front();
    switch (dir) {
        case DOWN: head.y += 10; break;
        case UP: head.y -= 10; break;
        case LEFT: head.x -= 10; break;
        case RIGHT: head.x += 10; break;
    }
    body.push_front(head);
    if (body.size() > size) {
        body.pop_back();
    }
}

void Snake::grow() {
    size += 10;
}

bool Snake::checkCollision(const SDL_Rect& rect) {
    SDL_Rect head = body.front();
    return head.x == rect.x && head.y == rect.y;
}

void Snake::checkSelfCollision() {
    SDL_Rect head = body.front();
    for (auto it = body.begin() + 1; it != body.end(); ++it) {
        if (head.x == it->x && head.y == it->y) {
            size = 1;
            body.resize(size);
        }
    }
}

void Snake::render(SDL_Renderer* renderer) {
    for (const auto& segment : body) {
        SDL_RenderFillRect(renderer, &segment);
    }
}

