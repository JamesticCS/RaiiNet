export module gamecontroller;

import board;
import player;
import <memory>;
import <vector>;
import <string>;
import <sstream>;
import textobserver;  

export class GameController {
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
    void initalizeGame() const;
    int getNumPlayers() const;
};
