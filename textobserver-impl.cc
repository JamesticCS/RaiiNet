module textobserver;
import subject;

TextObserver::TextObserver(Board* board) : subject{board} {
    subject->attach(this);
}

void TextObserver::displayBoard() {
    std::cout << "========" << std::endl;
    
    int currRow = 0;
    for (auto it = subject->begin(); it != subject->end(); ++it) {
        Square& square = *it;
        
        // Print appropriate character
        if (square.isServerPort()) {
            std::cout << "S";
        } else if (square.isEmpty()) {
            std::cout << ".";
        } else {
            // Will need to get link info here once Link class exists
            std::cout << "X";  // Placeholder
        }

        // New line after every 8 squares
        if (++currRow % 8 == 0) std::cout << std::endl;
    }
    
    std::cout << "========" << std::endl;
}

void TextObserver::displayPlayerInfo(int playerNum) {
    // Will update later once player class exists
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
