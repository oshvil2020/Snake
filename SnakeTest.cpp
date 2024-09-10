#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include "Snake.h"

// Test Snake construction
TEST(SnakeTest, SnakeInitialPosition) {
    Snake snake;
    
    // Check initial size
    ASSERT_EQ(snake.getSize(), 1) << "Snake should start with size 1.";
    
    // Check initial position
    SDL_Rect initialPosition = snake.getHead();
    EXPECT_EQ(initialPosition.x, 500) << "Snake head should start at x = 500.";
    EXPECT_EQ(initialPosition.y, 500) << "Snake head should start at y = 500.";
}

// Test Snake movement
TEST(SnakeTest, SnakeMove) {
    Snake snake;

    // Move snake down
    snake.move(Snake::DOWN);
    SDL_Rect newPosition = snake.getHead();
    EXPECT_EQ(newPosition.y, 510) << "Snake should move down by 10 units.";

    // Move snake right
    snake.move(Snake::RIGHT);
    newPosition = snake.getHead();
    EXPECT_EQ(newPosition.x, 510) << "Snake should move right by 10 units.";
}

// Test Snake growing
TEST(SnakeTest, SnakeGrow) {
    Snake snake;

    // Check initial size
    EXPECT_EQ(snake.getSize(), 1) << "Initial snake size should be 1.";

    // Grow the snake
    snake.grow();
    EXPECT_EQ(snake.getSize(), 11) << "Snake size should be increased by 10 after growing.";
}

// Test collision with a rectangle
TEST(SnakeTest, SnakeCollision) {
    Snake snake;
    SDL_Rect rect = {500, 500, 10, 10};

    // Check collision with a rectangle
    EXPECT_TRUE(snake.checkCollision(rect)) << "Snake should collide with the given rectangle at the initial position.";
    
    // Move snake and check for no collision
    snake.move(Snake::DOWN);
    EXPECT_FALSE(snake.checkCollision(rect)) << "Snake should not collide after moving down.";
}

// Test self-collision
TEST(SnakeTest, SnakeSelfCollision) {
    Snake snake;

    // Grow and move snake to create self-collision scenario
    for (int i = 0; i < 10; ++i) {
        snake.grow();
        snake.move(Snake::RIGHT);
    }
    
    // Simulate self-collision by making the snake move into itself
    snake.move(Snake::LEFT);
    snake.checkSelfCollision();

    // Check that the snake has reset its size after self-collision
    EXPECT_EQ(snake.getSize(), 1) << "Snake should reset its size to 1 after self-collision.";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

