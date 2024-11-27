export module gamecontroller;

import board;
import player;
import <memory>
import <vector>

export class GameController {
private:
    std::unique_ptr<Board> board;
    std::vector<Player> players;
    int currentPlayerIndex = 0;

public:
    GameController(int numPlayers);
    
    Player& getCurrentPlayer();
    void nextTurn();
    int getNumPlayers() const;
    void runGame();
};
