#include <SDL2/SDL.h>
#include <deque>

/**
 * Represents a Snake with movement and collision detection.
 */
class Snake {
public:
    /**
     * Enumeration for possible movement directions.
     */
    enum Direction { DOWN, LEFT, RIGHT, UP };

    /**
     * Constructs a Snake object, initializes with default size and position.
     */
    Snake();

    /**
     * Moves the snake in the given direction.
     * @param dir Direction to move the snake.
     */
    void move(int dir);

    /**
     * Increases the size of the snake.
     */
    void grow();

    /**
     * Checks if the snake's head collides with the given rectangle.
     * @param rect SDL_Rect object representing another object.
     * @return True if there is a collision, false otherwise.
     */
    bool checkCollision(const SDL_Rect& rect);

    /**
     * Checks if the snake collides with itself. Resets the snake if collision occurs.
     */
    void checkSelfCollision();

    /**
     * Renders the snake on the given SDL_Renderer.
     * @param renderer SDL_Renderer object used for rendering.
     */
    void render(SDL_Renderer* renderer);

private:
    std::deque<SDL_Rect> body; /**< Holds the segments of the snake's body. */
    int size; /**< The size of the snake, represented by the number of segments. */
};

// Implementation of the Snake methods

/**
 * Constructs a Snake object, initializes with default size and position.
 */
Snake::Snake() : size(1) {
    body.push_front({500, 500, 10, 10});
}

/**
 * Moves the snake in the given direction.
 * @param dir Direction to move the snake.
 */
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

/**
 * Increases the size of the snake.
 */
void Snake::grow() {
    size += 10;
}

/**
 * Checks if the snake's head collides with the given rectangle.
 * @param rect SDL_Rect object representing another object.
 * @return True if there is a collision, false otherwise.
 */
bool Snake::checkCollision(const SDL_Rect& rect) {
    SDL_Rect head = body.front();
    return head.x == rect.x && head.y == rect.y;
}

/**
 * Checks if the snake collides with itself. Resets the snake if collision occurs.
 */
void Snake::checkSelfCollision() {
    SDL_Rect head = body.front();
    for (auto it = body.begin() + 1; it != body.end(); ++it) {
        if (head.x == it->x && head.y == it->y) {
            size = 1;
            body.resize(size);
        }
    }
}

/**
 * Renders the snake on the given SDL_Renderer.
 * @param renderer SDL_Renderer object used for rendering.
 */
void Snake::render(SDL_Renderer* renderer) {
    for (const auto& segment : body) {
        SDL_RenderFillRect(renderer, &segment);
    }
}

