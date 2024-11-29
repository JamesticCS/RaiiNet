// board.cc
#include "board.h"
Board::Board() {
    // Initialize grid
    grid.resize(rows);
    for(int i = 0; i < rows; i++) {
        grid[i].resize(cols);
        for(int j = 0; j < cols; j++) {
            grid[i][j] = std::make_unique<Square>();
        }
    }
    setServerPorts();
    setEdgeSquares();
}



void Board::setServerPorts() {
    // Top server ports
    grid[0][3] = std::make_unique<Square>(true, false, true);
    grid[0][4] = std::make_unique<Square>(true, false, true);
    grid[7][3] = std::make_unique<Square>(true, false, true);
    grid[7][4] = std::make_unique<Square>(true, false, true);
}

void Board::setEdgeSquares() {
    for(int i = 1; i < rows-1; ++i) {
        for(int j = 1; j < cols-1; ++j) {
            grid[i][j] = std::make_unique<Square>(false, false, false);
        }
    }
    
    for(int j = 0; j < cols; ++j) {
        if (j != 3 && j != 4) {
            grid[0][j] = std::make_unique<Square>(false, (j == 0 || j == cols-1), true);
        }
    }
    
    for(int j = 0; j < cols; ++j) {
        if (j != 3 && j != 4) {
            grid[7][j] = std::make_unique<Square>(false, (j == 0 || j == cols-1), true);
        }
    }
    
    for(int i = 1; i < rows-1; ++i) {
        grid[i][0] = std::make_unique<Square>(false, true, false);
        grid[i][cols-1] = std::make_unique<Square>(false, true, false);
    }
}


bool Board::isValidPosition(int row, int col) const {
   return row >= 0 && row < rows && col >= 0 && col < cols;
}

Board::BoardIterator::BoardIterator(Board* board, int currRow, int currCol) : board{board}, currRow{currRow}, currCol{currCol} {}

Square& Board::BoardIterator::operator*()
{
    return *(board->grid[currRow][currCol]);
}

bool Board::BoardIterator::operator!=(const BoardIterator& other)
{
    return (board != other.board) || (currRow != other.currRow) ||  (currCol != other.currCol);
}

Board::BoardIterator& Board::BoardIterator::operator++()
{
    ++currCol;
    if (currCol >= 8)
    {
        ++currRow;
        currCol = 0;
    }
    return *this;
}

Board::BoardIterator Board::begin() { 
    return BoardIterator{this, 0, 0}; 
}

Board::BoardIterator Board::end() { 
    return BoardIterator{this, 8, 0}; 
}

void Board::placeLink(int row, int col, Link* link) {
    if (isValidPosition(row, col)) {
        grid[row][col]->setLink(link);
        notifyObservers();
    }
}

void Board::placeLinkNoNotify(int row, int col, Link* link) {
    if (isValidPosition(row, col)) {
        grid[row][col]->setLink(link);
    }
}

bool Board::isServerPortAt(int row, int col) const {
    if (isValidPosition(row, col)) {
        return grid[row][col]->isServerPort();
    }
    return false;
}

bool Board::hasLinkAt(int row, int col) const {
    if (isValidPosition(row, col)) {
        return grid[row][col]->hasLink();
    }
    return false;
}

char Board::getLinkDisplayChar(int row, int col) const {
    if (!isValidPosition(row, col) || !grid[row][col]->hasLink()) {
        return '.';
    }
    Link* link = grid[row][col]->getLink();;
    return link->getIdentifier();
}

bool Board::moveLink(int fromRow, int fromCol, int toRow, int toCol, Player& currentPlayer, Player& otherPlayer) {
    if (!isValidPosition(fromRow, fromCol)) {
        return false;
    }

    auto& fromSquare = grid[fromRow][fromCol];
    if (!fromSquare->hasLink()) {
        return false;
    }

    Link* movingLink = fromSquare->getLink();
    int currentPlayerId = currentPlayer.getPlayerId();
    
    // Check if moving off edge
    bool movingOffP1Edge = (currentPlayerId == 1 && fromRow == 7 && toRow == 8);
    bool movingOffP2Edge = (currentPlayerId == 2 && fromRow == 0 && toRow == -1);
    
    // Allow moving off opponent's edge and handle download
    if (movingOffP1Edge || movingOffP2Edge) {
        currentPlayer.downloadLink(movingLink);
        fromSquare->removeLink();
        notifyObservers();
        return true;
    }
    
    if (!isValidPosition(toRow, toCol)) {
        return false;
    }

    auto& toSquare = grid[toRow][toCol];
    
    // Can't move onto own server ports
    if (isOwnServerPort(toRow, toCol, currentPlayerId)) {
        return false;
    }
    
    // Check if moving onto own piece
    if (toSquare->hasLink() && toSquare->getLink()->getOwner() == currentPlayerId) {
        return false;
    }
    
    // Handle battle if moving onto opponent's piece
    if (toSquare->hasLink()) {
        Link* attacker = movingLink;
        Link* defender = toSquare->getLink();
        
        // Reveal both links
        attacker->reveal();
        defender->reveal();
        
        // Battle resolution
        if (attacker->getStrength() >= defender->getStrength()) {
            // Attacker wins - download defender
            currentPlayer.downloadLink(defender);
            toSquare->setLink(attacker);
            fromSquare->removeLink();
        } else {
            // Defender wins - download attacker
            otherPlayer.downloadLink(attacker);
            fromSquare->removeLink();
        }
  //      notifyObservers();
        return true;
    }
    
    // Handle moving into opponent's server port
    if (isOpponentServerPort(toRow, toCol, currentPlayerId)) {
        otherPlayer.downloadLink(movingLink);  // OPPONENT downloads the piece
        fromSquare->removeLink();
      //  notifyObservers();
        return true;
    }
    
    // Normal movement
    toSquare->setLink(movingLink);
    fromSquare->removeLink();
   // notifyObservers();
    return true;
}


bool Board::isP1ServerPort(int row, int col) const {
    return row == 0 && (col == 3 || col == 4);
}

bool Board::isP2ServerPort(int row, int col) const {
    return row == 7 && (col == 3 || col == 4);
}

bool Board::isOpponentServerPort(int row, int col, int playerId) const {
    if (playerId == 1) {
        return isP2ServerPort(row, col);
    } else {
        return isP1ServerPort(row, col);
    }
}

bool Board::isOwnServerPort(int row, int col, int playerId) const {
    if (playerId == 1) {
        return isP1ServerPort(row, col);
    } else {
        return isP2ServerPort(row, col);
    }
}