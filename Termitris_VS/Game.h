#ifndef GAME_H
#define GAME_H

#include <vector>

// Define the size of the game board
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

// Define the shapes of the blocks
const std::vector<std::vector<std::vector<int>>> SHAPES = {
    // I shape
    {{1, 1, 1, 1}},
    // O shape
    {{1, 1}, {1, 1}},
    // T shape
    {{0, 1, 0}, {1, 1, 1}},
    // S shape
    {{0, 1, 1}, {1, 1, 0}},
    // Z shape
    {{1, 1, 0}, {0, 1, 1}},
    // J shape
    {{1, 0, 0}, {1, 1, 1}},
    // L shape
    {{0, 0, 1}, {1, 1, 1}}
};

// Forward declaration of the Board class
class Board;

// Block class
class Block {
public:
    Block();
    void rotate();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();
    bool isCollision(const Board& board) const;
    const std::vector<std::vector<int>>& getShape() const { return shape; } // Accessor for shape
    int getX() const { return x; } // Accessor for x
    int getY() const { return y; } // Accessor for y
    // ... Other member functions and variables
private:
    std::vector<std::vector<int>> shape;
    int x, y; // Position of the block
};

// Board class
class Board {
public:
    Board();
    void placeBlock(const Block& block);
    int clearLines();
    void render();
    // ... Other member functions and variables
    friend class Block; // Allow Block to access Board's private members
private:
    int grid[BOARD_HEIGHT][BOARD_WIDTH];
};

// Score class
class Score {
public:
    Score();
    void increaseScore(int linesCleared);
    int getScore() const;
    // ... Other member functions and variables
private:
    int score;
};

// Game class
class Game {
public:
    Game();
    void start();
    void update();
    void render();
    void handleInput(char key);
    bool isGameOver() const;
    int getScore() const;
    // ... Other member functions and variables
private:
    Board board;
    Block currentBlock;
    Score score;
    int difficultyLevel;
    bool gameOver;
};

#endif // GAME_H
