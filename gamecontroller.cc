// gameController.cc
#include "gamecontroller.h"
/*
#include "linkboost.h"  // For LinkBoostAbility
#include "firewall.h"   // For FirewallAbility
#include "scan.h"       // For ScanAbility
#include "download.h"   // For DownloadAbility
#include "polarize.h"   // For PolarizeAbility
*/

GameController::GameController(int numPlayers, std::string link1File, std::string link2File):
 board{std::make_unique<Board>()} {
    // random seeding
    std::srand(std::time(nullptr));

    if (numPlayers != 2 && numPlayers != 4) {
        throw std::invalid_argument("Invalid number of players");
    }
    for (int i = 1; i <= numPlayers; ++i) {
        players.emplace_back(i);
    }
    display = std::make_unique<TextObserver>(board.get(), this);

    // Get links for each player
    std::vector<LinkInfo> p1Links;
    if (link1File.empty()) {
        p1Links = getRandomizedLinks(1);
    } else {
        p1Links = parseLinksFile(link1File, 1);
    }

    std::vector<LinkInfo> p2Links;
    if (link2File.empty()) {
        p2Links = getRandomizedLinks(2);
    } else {
        p2Links = parseLinksFile(link2File, 2);
    }
    
    initializeGame(p1Links, p2Links);  // Use custom initialization
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
    /*
    else if (command == "abilities")
    {
      getCurrentPlayer().displayAbilities();
    } */


    /*
    else if (command == "ability") {
    Player& current = getCurrentPlayer();

    // Check if the player has already used an ability this turn
    if (current.hasUsedAbilityThisTurn()) {
        std::cout << "You've already used an ability this turn!\n";
        return;
    }

    int abilityId;
    if (!(iss >> abilityId)) {  // Read the ability ID
        std::cout << "Invalid ability format! Use: ability <number> <args>\n\n";
        return;
    }

    std::string args;
    std::getline(iss >> std::ws, args);  // Read the remaining arguments (e.g., position)

    std::unique_ptr<Ability> ability;
    std::unique_ptr<Ability> ability;
    switch (abilityId) {
        case 1: 
            ability = std::make_unique<LinkBoost>(board.get());  // Pass the Board* to LinkBoost
            break;
        case 2: 
            ability = std::make_unique<Firewall>(board.get());  // Pass the Board* to Firewall
            break;
        case 3: 
            ability = std::make_unique<Scan>(board.get());  // Pass the Board* to Scan
            break;
        case 4: 
            ability = std::make_unique<Download>(current);  // Pass the Player& to Download
            break;
        case 5: 
            ability = std::make_unique<Polarize>(board.get());  // Pass the Board* to Polarize
            break;
        default:
            std::cout << "Invalid ability ID! Must be between 1-5\n\n";
        return;
}


    if (ability->execute(current, args)) {
        current.setAbilityUsedThisTurn(true);
        current.useAbility(abilityId);  // Assuming Player has a method to track ability use
    } else {
        std::cout << "Invalid ability usage!\n\n";
    }
    return;
}

*/


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

   // If we didn't quit, show final game state
    if (isGameOver()) {
        board->notifyObservers();  // Show final board state
        displayGameOver();
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
                   
                    int opponentPlayerId;
                    if (getCurrentPlayer().getPlayerId() == 1) {
                        opponentPlayerId = 2;
                    } else {
                        opponentPlayerId = 1;
                    }

                    bool moveSuccessful = 
                    board->moveLink(row, col, newRow, newCol,
                     getCurrentPlayer(), getPlayer(opponentPlayerId));

                    if (moveSuccessful) {
                        return true;
                    }
                    return false;
               }
           }
       }
   }
   return false;  // Piece not found
}


Player& GameController::getPlayer(int playerId) {
        for (auto& player : players) {
            if (player.getPlayerId() == playerId) {
                return player;
            }
        }
        return players[0];  // Should never happen if used correctly
}

void GameController::displayGameOver() {
    std::cout << "\n=== GAME OVER ===\n";
    
    // Find who won/lost and announce it
    for (const auto& player : players) {
        if (player.hasWon()) {
            std::cout << "Player " << player.getPlayerId() << " wins by downloading 4 data!\n";
            break;
        }
        else if (player.hasLost()) {
            std::cout << "Player " << player.getPlayerId() << " loses by downloading 4 viruses!\n";
            break;
        }
    }

    // Show final scores for both players
    std::cout << "\nFinal Score:\n";
    
    // Player 1
    std::cout << "Player 1:\n";
    std::cout << "Data Downloads: " << getPlayer(1).getDataCount() << "\n";
    std::cout << "Virus Downloads: " << getPlayer(1).getVirusCount() << "\n";
    
    // Player 2
    std::cout << "Player 2:\n";
    std::cout << "Data Downloads: " << getPlayer(2).getDataCount() << "\n";
    std::cout << "Virus Downloads: " << getPlayer(2).getVirusCount() << "\n";
    
    std::cout << "===============\n";
}


std::vector<GameController::LinkInfo> GameController::getDefaultLinks(int playerId) const {
    
    char startChar;

    if (playerId == 1) {
        startChar = 'a';
    } else if (playerId == 2) {
        startChar = 'A';
    } else if (playerId == 3) {
        startChar = 'i';
    } else {
        startChar = 'I';
    }
    // static cast to avoid compiler warning 
    return {
        {true, 1, startChar},             // V1
        {false, 4, static_cast<char>(startChar + 1)}, // D4
        {true, 3, static_cast<char>(startChar + 2)},  // V3
        {true, 2, static_cast<char>(startChar + 3)},  // V2
        {false, 3, static_cast<char>(startChar + 4)}, // D3
        {true, 4, static_cast<char>(startChar + 5)},  // V4
        {false, 2, static_cast<char>(startChar + 6)}, // D2
        {false, 1, static_cast<char>(startChar + 7)}  // D1
    };
}

std::vector<GameController::LinkInfo> GameController::getRandomizedLinks(int playerId) const {
    std::vector<LinkInfo> links = getDefaultLinks(playerId);
    
    // Shuffle pairs of type and strength while preserving identifiers
    std::vector<std::pair<bool, int>> typeStrengthPairs;
    for (const auto& link : links) {
        typeStrengthPairs.push_back({link.isVirus, link.strength});
    }
    
    // Shuffle the types/strengths
    for (int i = typeStrengthPairs.size() - 1; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(typeStrengthPairs[i], typeStrengthPairs[j]);
    }
    
    // Reassign the shuffled properties while keeping identifiers in sequence
    char id;
    if (playerId == 1) {
        id = 'a';
    } else {
        id = 'A';
    }

    for (size_t i = 0; i < links.size(); i++, id++) {
        links[i].isVirus = typeStrengthPairs[i].first;
        links[i].strength = typeStrengthPairs[i].second;
        links[i].identifier = id;
    }
    
    return links;
}


std::vector<GameController::LinkInfo> GameController::parseLinksFile(const std::string& filename, int playerId) const {
    std::vector<LinkInfo> links;
    std::ifstream file{filename};
    std::string token;
    
    char identifier;
    if (playerId == 1) {
        identifier = 'a';
    } else {
        identifier = 'A';
    }

    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    while (links.size() < 8 && file >> token) {
        if (token.length() < 2) {
            throw std::runtime_error("Invalid link format in file: " + token);
        }

        LinkInfo info;
        info.isVirus = (token[0] == 'V');
        if (token[0] != 'V' && token[0] != 'D') {
            throw std::runtime_error("Link must be V or D: " + token);
        }

        info.strength = token[1] - '0';
        if (info.strength < 1 || info.strength > 4) {
            throw std::runtime_error("Link strength must be 1-4: " + token);
        }

        info.identifier = identifier++;
        links.push_back(info);
    }

    if (links.size() != 8) {
        throw std::runtime_error("File must contain exactly 8 links");
    }

    return links;
}

void GameController::initializeGame(const std::vector<LinkInfo>& p1Links, const std::vector<LinkInfo>& p2Links) {
    Player& p1 = getPlayer(1);
    Player& p2 = getPlayer(2);
    
    // Create and add Player 1's links
    for (const auto& link : p1Links) {
        if (link.isVirus) {
            p1.addLink(std::make_unique<Virus>(link.strength, 1, link.identifier));
        } else {
            p1.addLink(std::make_unique<Data>(link.strength, 1, link.identifier));
        }
    }
    
    // Create and add Player 2's links
    for (const auto& link : p2Links) {
        if (link.isVirus) {
            p2.addLink(std::make_unique<Virus>(link.strength, 2, link.identifier));
        } else {
            p2.addLink(std::make_unique<Data>(link.strength, 2, link.identifier));
        }
    }
    
    // Place Player 1's links on board
    board->placeLinkNoNotify(0, 0, p1.getLinkByIdentifier('a'));
    board->placeLinkNoNotify(0, 1, p1.getLinkByIdentifier('b'));
    board->placeLinkNoNotify(0, 2, p1.getLinkByIdentifier('c'));
    board->placeLinkNoNotify(1, 3, p1.getLinkByIdentifier('d'));
    board->placeLinkNoNotify(1, 4, p1.getLinkByIdentifier('e'));
    board->placeLinkNoNotify(0, 5, p1.getLinkByIdentifier('f'));
    board->placeLinkNoNotify(0, 6, p1.getLinkByIdentifier('g'));
    board->placeLinkNoNotify(0, 7, p1.getLinkByIdentifier('h'));

    // Place Player 2's links on board
    board->placeLinkNoNotify(7, 0, p2.getLinkByIdentifier('A'));
    board->placeLinkNoNotify(7, 1, p2.getLinkByIdentifier('B'));
    board->placeLinkNoNotify(7, 2, p2.getLinkByIdentifier('C'));
    board->placeLinkNoNotify(6, 3, p2.getLinkByIdentifier('D'));
    board->placeLinkNoNotify(6, 4, p2.getLinkByIdentifier('E'));
    board->placeLinkNoNotify(7, 5, p2.getLinkByIdentifier('F'));
    board->placeLinkNoNotify(7, 6, p2.getLinkByIdentifier('G'));
    board->placeLinkNoNotify(7, 7, p2.getLinkByIdentifier('H'));
}
