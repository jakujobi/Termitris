#include "Game.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime> // For time()

// Block Class Implementation
Block::Block() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    // Initialize block with a random shape
    shape = SHAPES[rand() % SHAPES.size()];
    x = BOARD_WIDTH / 2 - shape[0].size() / 2;
    y = 0;
}

void Block::rotate() {
    // Rotate the block (clockwise)
    std::vector<std::vector<int>> rotatedShape;
    for (size_t i = 0; i < shape[0].size(); ++i) {
        std::vector<int> row;
        for (int j = static_cast<int>(shape.size()) - 1; j >= 0; --j) {
            row.push_back(shape[j][i]);
        }
        rotatedShape.push_back(row);
    }
    shape = rotatedShape;
}

void Block::moveLeft() {
    x--;
}

void Block::moveRight() {
    x++;
}

void Block::moveDown() {
    y++;
}

void Block::moveUp() {
    y--;
}

bool Block::isCollision(const Board& board) const {
    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j]) {
                int x_pos = x + j;
                int y_pos = y + i;

                // Check for collision with the board boundaries
                if (x_pos < 0 || x_pos >= BOARD_WIDTH || y_pos >= BOARD_HEIGHT) {
                    return true;
                }

                // Check for collision with other blocks on the board
                if (y_pos >= 0 && board.grid[y_pos][x_pos]) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Board Class Implementation
Board::Board() {
    // Initialize the game board (empty)
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            grid[i][j] = 0;
        }
    }
}

void Board::placeBlock(const Block& block) {
    const auto& shape = block.getShape();
    int x = block.getX();
    int y = block.getY();

    for (size_t i = 0; i < shape.size(); ++i) {
        for (size_t j = 0; j < shape[i].size(); ++j) {
            if (shape[i][j]) {
                grid[y + i][x + j] = 1;
            }
        }
    }
}

int Board::clearLines() {
    int linesCleared = 0;
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        bool lineComplete = true;
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (grid[i][j] == 0) {
                lineComplete = false;
                break;
            }
        }
        if (lineComplete) {
            linesCleared++;
            // Move all lines above down
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < BOARD_WIDTH; ++j) {
                    grid[k][j] = grid[k - 1][j];
                }
            }
            // Clear the top line
            for (int j = 0; j < BOARD_WIDTH; ++j) {
                grid[0][j] = 0;
            }
        }
    }
    return linesCleared;
}

void Board::render() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            std::cout << (grid[i][j] ? '#' : ' ');
        }
        std::cout << std::endl;
    }
}

// Score Class Implementation
Score::Score() : score(0) {}

void Score::increaseScore(int linesCleared) {
    score += linesCleared * 100;
}

int Score::getScore() const {
    return score;
}

// Game Class Implementation
Game::Game() : gameOver(false), difficultyLevel(1), score() {
    currentBlock = Block();
}

void Game::start() {
    currentBlock = Block();
}

void Game::update() {
    currentBlock.moveDown();
    if (currentBlock.isCollision(board)) {

        currentBlock.moveUp();
        board.placeBlock(currentBlock);
        int linesCleared = board.clearLines();
        score.increaseScore(linesCleared);
        currentBlock = Block();

        if (currentBlock.isCollision(board)) {
            gameOver = true;
        }
    }
}

void Game::render() {
    system("cls"); // Clear the console (Windows-specific)
    board.render();
    std::cout << "Score: " << score.getScore() << std::endl;
}

void Game::handleInput(char key) {
    switch (key) {
    case 'a': // Move left
    case 'A':
    case 75: // Left arrow key (ASCII code)
        currentBlock.moveLeft();
        if (currentBlock.isCollision(board)) {
            currentBlock.moveRight(); // Revert if collision
        }
        break;

    
    case 'd': // Move right
    case 'D':
    case 77: // Right arrow key (ASCII code)
        currentBlock.moveRight();
        if (currentBlock.isCollision(board)) {
            currentBlock.moveLeft(); // Revert if collision
        }
        break;
    case 's': // Move down
    case 'S':
    case 80: // Down arrow key (ASCII code)
        currentBlock.moveDown();
        if (currentBlock.isCollision(board)) {
            currentBlock.moveUp(); // Revert if collision
        }
        break;
    case 'w': // Rotate
    case 'W':
    case 72: // Up arrow key (ASCII code)
        currentBlock.rotate();
        if (currentBlock.isCollision(board)) {
            currentBlock.rotate(); // Revert if collision
            currentBlock.rotate();
            currentBlock.rotate(); // Rotate back to original position
        }
        break;
    }
}

bool Game::isGameOver() const {
    return gameOver;
}

int Game::getScore() const {
    return score.getScore();
}