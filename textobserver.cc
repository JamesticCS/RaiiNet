// textobserver.cc

#include "textobserver.h"
TextObserver::TextObserver(Board* board) : subject{board} {
    subject->attach(this);
}

// textobserver-impl.cc
void TextObserver::displayBoard() {
   std::cout << "========" << std::endl;
   
   int count = 0;
   for (auto it = subject->begin(); it != subject->end(); ++it) {
        Square& square = *it;
       if (square.isServerPort()) {
           std::cout << "S";
       } else if (square.hasLink()) {
           Link* link = square.getLink().get();
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
}

void TextObserver::displayPlayerInfo(int playerNum) {
    // For now just display placeholder values
    std::cout << "Player " << playerNum << ":" << std::endl;
    std::cout << "Downloaded: 0D, 0V" << std::endl;
    std::cout << "Abilities: 5" << std::endl;
}

void TextObserver::notify() {
    // Display Player 1 info
    displayPlayerInfo(1);

    // Display board
    displayBoard();

    // Display Player 2 info
    displayPlayerInfo(2);
}
