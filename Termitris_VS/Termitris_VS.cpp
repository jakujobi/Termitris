// Termitris_VS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Game.h"
#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include<windows.h>           // for windows
//#include<unistd.h>               // for linux 

int main() {
    Game game;
    game.start();

    while (!game.isGameOver()) {
        if (_kbhit()) {
            char key = _getch();
            game.handleInput(key);
        }
        game.update();
        game.render();
        // Sleep to control the speed of the game loop
        Sleep(50); // Sleep for 50 milliseconds (Windows-specific)
    }

    std::cout << "Game Over! Your score: " << game.getScore() << std::endl;
    return 0;
}