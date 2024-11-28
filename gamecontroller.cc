// gameController.cc
#include "gamecontroller.h"
GameController::GameController(int numPlayers) : board{std::make_unique<Board>()} {

    if (numPlayers != 2 && numPlayers != 4) {
        throw std::invalid_argument("Invalid number of players");
    }
    for (int i = 1; i <= numPlayers; ++i) {
        players.emplace_back(i);  // Create players with IDs 1 to numPlayers
    }
    display = std::make_unique<TextObserver>(board.get());
}

Player& GameController::getCurrentPlayer() {
    return players[currentPlayerIndex];
}

void GameController::nextTurn() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

int GameController::getNumPlayers() const {
    return players.size();
}

void GameController::initializeGame() const {
    // Placeholder

    board->placeLinkNoNotify(0, 0, std::make_unique<Virus>(1, 1, 'a'));  // a: V1
    board->placeLinkNoNotify(0, 1, std::make_unique<Data>(4, 1, 'b'));   // b: D4
    board->placeLinkNoNotify(0, 2, std::make_unique<Virus>(3, 1, 'c'));  // c: V3
    board->placeLinkNoNotify(1, 3, std::make_unique<Virus>(2, 1, 'd'));  // d: V2 (row 1 due to server port)
    board->placeLinkNoNotify(1, 4, std::make_unique<Data>(3, 1, 'e'));   // e: D3 (row 1 due to server port)
    board->placeLinkNoNotify(0, 5, std::make_unique<Virus>(4, 1, 'f'));  // f: V4
    board->placeLinkNoNotify(0, 6, std::make_unique<Data>(2, 1, 'g'));   // g: D2
    board->placeLinkNoNotify(0, 7, std::make_unique<Data>(1, 1, 'h'));   // h: D1

    // Player 2 setup (A through H)
    board->placeLinkNoNotify(7, 0, std::make_unique<Virus>(1, 2, 'A'));  // A: V1
    board->placeLinkNoNotify(7, 1, std::make_unique<Data>(4, 2, 'B'));   // B: D4
    board->placeLinkNoNotify(7, 2, std::make_unique<Virus>(3, 2, 'C'));  // C: V3
    board->placeLinkNoNotify(6, 3, std::make_unique<Virus>(2, 2, 'D'));  // D: V2 (row 6 due to server port)
    board->placeLinkNoNotify(6, 4, std::make_unique<Data>(3, 2, 'E'));   // E: D3 (row 6 due to server port)
    board->placeLinkNoNotify(7, 5, std::make_unique<Virus>(4, 2, 'F'));  // F: V4
    board->placeLinkNoNotify(7, 6, std::make_unique<Data>(2, 2, 'G'));   // G: D2
    board->placeLinkNoNotify(7, 7, std::make_unique<Data>(1, 2, 'H'));   // H: D1
}

bool GameController::isGameOver() const
{
    for (const auto& player : players) {
        if (player.hasWon() || player.hasLost()) {
            return true;
        }
    }
    return false;
}

void GameController::handleCommand(const std::string& cmd) {
    std::istringstream iss{cmd};
    std::string command;
    iss >> command;

    if (command == "quit") {
        exit(0);
    }
    else if (command == "board") {
        board->notifyObservers();
    }
    else if (command == "move") {
        char piece;
        std::string dir;
        iss >> piece >> dir;
        
        try {
            Direction direction = stringToDirection(dir);
            if (makeMove(piece, direction)) {
                std::cout << "==========================\n\n\n";
                nextTurn();  // Only switch turns if move was successful
            } else {
                std::cout << "Invalid move!" << std::endl;
                std::cout << "==========================\n\n\n";
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid direction!" << std::endl;
            std::cout << "==========================\n\n\n";
        }
    }
}

void GameController::runGame() {
   std::string command;
   while (!isGameOver()) {
       board->notifyObservers();
       std::cout << "Player " << getCurrentPlayer().getPlayerId() << "'s turn: ";
       std::getline(std::cin, command);
       
       if (command == "quit") break;
       handleCommand(command);
   }
}

GameController::Direction GameController::stringToDirection(const std::string& dir) {
    std::string lowerDir = dir;
    // lowercase convertsion
    // https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
    std::transform(lowerDir.begin(), lowerDir.end(), lowerDir.begin(), ::tolower);


    if (lowerDir == "up") return Direction::UP;
    if (lowerDir == "down") return Direction::DOWN;
    if (lowerDir == "left") return Direction::LEFT;
    if (lowerDir == "right") return Direction::RIGHT;
    throw std::invalid_argument("Invalid direction");
}


bool GameController::makeMove(char piece, Direction dir) {
   // Find current player's piece on board matching the letter

    int playerId = getCurrentPlayer().getPlayerId();
    bool isValidPiece = false;
    if (playerId == 1) {
    // Player 1: piece must be between 'a' and 'h'
    isValidPiece = (piece >= 'a' && piece <= 'h');
    } else if (playerId == 2) {
    // Player 2: 
    isValidPiece = (piece >= 'A' && piece <= 'H');
    } else if (playerId == 3) {
    // Player 3:
    isValidPiece = (piece >= 'i' && piece <= 'p');
    } else if (playerId == 4) {
    // Player 4:
    isValidPiece = (piece >= 'I' && piece <= 'P');
    } 
    
    if (!isValidPiece) {
        return false;
    }
   
   for (int row = 0; row < 8; ++row) {
       for (int col = 0; col < 8; ++col) {
           if (board->hasLinkAt(row, col)) {
               char displayChar = board->getLinkDisplayChar(row, col);
               if (displayChar == piece) {
                   // Found the piece, calculate new position
                   int newRow = row;
                   int newCol = col;
                   
                   switch(dir) {
                       case Direction::UP: newRow--; break;
                       case Direction::DOWN: newRow++; break;
                       case Direction::LEFT: newCol--; break;
                       case Direction::RIGHT: newCol++; break;
                   }
                   
                   // Try to move the piece
                    return board->moveLink(row, col, newRow, newCol);
               }
           }
       }
   }
   return false;  // Piece not found
}

