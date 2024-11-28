// gameController.h
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "player.h"
#include "textobserver.h"
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "link.h"
#include "virus.h"
#include "data.h"

class GameController {
private:
    std::unique_ptr<Board> board;
    std::vector<Player> players;
    int currentPlayerIndex = 0;
    std::unique_ptr<TextObserver> display;

public:
    GameController(int numPlayers);

    enum class Direction { UP, DOWN, LEFT, RIGHT };
    Player& getCurrentPlayer();
    void nextTurn();
    void runGame();
    bool isGameOver() const;
    void handleCommand(const std::string & cmd);
    Direction stringToDirection(const std::string& dir);
    bool makeMove(char piece, Direction dir);  // Returns if move was valid
    void initializeGame() const;
    int getNumPlayers() const;
};
#endif

