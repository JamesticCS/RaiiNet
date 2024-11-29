// textobserver.cc

#include "textobserver.h"

TextObserver::TextObserver(Board* board, GameController* controller): subject{board},  controller{controller} {
    subject->attach(this);
}

// textobserver-impl.cc
void TextObserver::displayBoard() {
    Player& p1 = controller->getCurrentPlayer();

    // Always display player 1's links first (top)
    if (p1.getPlayerId() == 1) {
        displayPlayerLinks(p1);
    } else {
        displayPlayerLinks(controller->getPlayer(1));
    }

   std::cout << "========" << std::endl;
   
   int count = 0;
   for (auto it = subject->begin(); it != subject->end(); ++it) {
        Square& square = *it;
       if (square.isServerPort()) {
           std::cout << "S";
       } else if (square.hasLink()) {
           Link* link = square.getLink();
           char displayChar = link->getIdentifier();
           std::cout << displayChar;
       } else {
           std::cout << ".";
       }
       
       count++;
       if (count % 8 == 0) {
           std::cout << std::endl;
       }
   }
   std::cout << "========" << std::endl;

    if (p1.getPlayerId() == 2) {
        displayPlayerLinks(p1);
    } else {
        displayPlayerLinks(controller->getPlayer(2));
    }
}

void TextObserver::displayPlayerInfo(int playerNum) {
    const Player& player = (playerNum == 1) ? controller->getPlayer(1) : controller->getPlayer(2);
    std::cout << "Player " << playerNum << ":" << std::endl;
    std::cout << "Downloaded: " << player.getDataCount() << "D, "
              << player.getVirusCount() << "V" << std::endl;
    std::cout << "Abilities: " << player.getRemainingAbilities() << std::endl;
}

void TextObserver::notify() {
    // Display Player 1 info
    displayPlayerInfo(1);

    // Display board
    displayBoard();

    // Display Player 2 info
    displayPlayerInfo(2);
}
void TextObserver::displayPlayerLinks(const Player& player) {
    int currentPlayerId = controller->getCurrentPlayer().getPlayerId();
    char start = (player.getPlayerId() == 1) ? 'a' : 'A';
    const std::vector<std::unique_ptr<Link>>& links = player.getLinks();

    bool showAll = (player.getPlayerId() == currentPlayerId);

    // First row (a-d or A-D)
    for (int i = 0; i < 4; i++) {
        char id = start + i;
        std::cout << id << ": ";
        for (const auto& link : links) {
            if (link->getIdentifier() == id) {
                if (showAll) {
                    std::cout << link->getRawDisplayString();  // Always show info for current player
                } else {
                    std::cout << link->getDisplayString();  // Use normal display logic for opponent
                }
                break;
            }
        }
        std::cout << " ";
    }
    std::cout << std::endl;

    // Second row (e-h or E-H)
    for (int i = 4; i < 8; i++) {
        char id = start + i;
        std::cout << id << ": ";
        for (const auto& link : links) {
            if (link->getIdentifier() == id) {
                if (showAll) {
                    std::cout << link->getRawDisplayString();
                } else {
                    std::cout << link->getDisplayString();
                }
                break;
            }
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}