module textobserver;


TextObserver::TextObserver(Board* board) : subject{board} {
    subject->attach(this);
}

// textobserver-impl.cc
void TextObserver::displayBoard() {
   std::cout << "========" << std::endl;
   
   int count = 0;
   for (auto it = subject->begin(); it != subject->end(); ++it) {
       if (it->isServerPort()) {
           std::cout << "S";
       } else if (it->hasLink()) {
           Link* link = it->getLink();
           char displayChar;
           if (link->getOwner() == 1) {
               displayChar = 'a' + count % 8;
           } else {
               displayChar = 'A' + count % 8;
           }
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
    const Player& player = subject->getPlayer(playerNum);
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
