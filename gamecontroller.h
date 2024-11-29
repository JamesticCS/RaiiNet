// gameController.h
#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "board.h"
#include "player.h"
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "link.h"
#include "virus.h"
#include "data.h"
#include "textobserver.h"

class TextObserver;

class GameController {
private:
    std::unique_ptr<Board> board;
    std::vector<Player> players;
    int currentPlayerIndex = 0;
    std::unique_ptr<TextObserver> display;
    void displayGameOver();
    struct LinkInfo {
        bool isVirus;
        int strength;
        char identifier;
    };
    
    std::vector<LinkInfo> getDefaultLinks(int playerId) const;  // Returns standard V1,D4,V3,etc. for a player
    std::vector<LinkInfo> getRandomizedLinks(int playerId) const;  // Randomizes the default links
public:
    GameController(int numPlayers, std::string link1File = "", std::string link2File = "");

    enum class Direction { UP, DOWN, LEFT, RIGHT };
    Player& getCurrentPlayer();
    void nextTurn();
    void runGame();
    bool isGameOver() const;
    void handleCommand(const std::string & cmd);
    
    Direction stringToDirection(const std::string& dir);
    bool makeMove(char piece, Direction dir);  // Returns if move was valid
    void initializeGame(const std::vector<LinkInfo>& p1Links, const std::vector<LinkInfo>& p2Links);  // Custom initialization
    std::vector<LinkInfo> parseLinksFile(const std::string& filename, int playerId) const;
    int getNumPlayers() const;
    Player& getPlayer(int playerId);
};
#endif

