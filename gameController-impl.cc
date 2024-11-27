// gamecontroller-impl.cc
module gamecontroller;

GameController::GameController(int numPlayers) : board{std::make_unique<Board>()} {
    for (size_t i = 1; i <= numPlayers; ++i) {
        players.emplace_back(i);  // Create players with IDs 1 to numPlayers
    }
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

void GameController::runGame() {
    // Placeholder for game logic
}
