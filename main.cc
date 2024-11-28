// main.cc
#include "gamecontroller.h"

int main() {
    GameController game{2};  // 2-player game
    game.initializeGame();   // Set up initial board state
    game.runGame();         // Start game loop
    return 0;
}