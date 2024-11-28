module board;

Board::Board() : grid(rows, std::vector<Square>(cols)) {
    setServerPorts();
    setEdgeSquares();
}
void Board::setServerPorts() {
    // Top server ports
    grid[0][3] = Square(true, false, true);
    grid[0][4] = Square(true, false, true);
    // Bottom server ports
    grid[7][3] = Square(true, false, true);
    grid[7][4] = Square(true, false, true);
}

void Board::setEdgeSquares() {
    // Set all non-edge squares to default
    for(int i = 1; i < rows-1; ++i) {
        for(int j = 1; j < cols-1; ++j) {
            grid[i][j] = Square(false, false, false);
        }
    }
    
    // Set top row (skipping server ports at positions 3,4)
    for(int j = 0; j < cols; ++j) {
        if (j != 3 && j != 4) {
            grid[0][j] = Square(false, (j == 0 || j == cols-1), true);
        }
    }
    
    // Set bottom row (skipping server ports at positions 3,4)
    for(int j = 0; j < cols; ++j) {
        if (j != 3 && j != 4) {
            grid[7][j] = Square(false, (j == 0 || j == cols-1), true);
        }
    }
    
    // Set left and right edges (excluding corners which were set in top/bottom)
    for(int i = 1; i < rows-1; ++i) {
        grid[i][0] = Square(false, true, false);      // Left edge
        grid[i][cols-1] = Square(false, true, false); // Right edge
    }
}


bool Board::isValidPosition(int row, int col) const {
   return row >= 0 && row < rows && col >= 0 && col < cols;
}

Board::BoardIterator::BoardIterator(Board* board, int currRow, int currCol) : board{board}, currRow{currRow}, currCol{currCol} {}

Square& Board::BoardIterator::operator*()
{
    return board->grid[currRow][currCol];
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

void Board::placeLink(int row, int col, std::unique_ptr<Link> link) {
    if (isValidPosition(row, col)) {
        grid[row][col].setLink(std::move(link));
        notifyObservers();
    }
}

bool Board::isServerPortAt(int row, int col) const {
    if (isValidPosition(row, col)) {
        return grid[row][col].isServerPort();
    }
    return false;
}

bool Board::hasLinkAt(int row, int col) const {
    if (isValidPosition(row, col)) {
        return grid[row][col].hasLink();
    }
    return false;
}

char Board::getLinkDisplayChar(int row, int col) const {
    if (!isValidPosition(row, col) || !grid[row][col].hasLink()) {
        return '.';
    }
    Link* link = grid[row][col].getLink();
    if (link->getOwner() == 1) {
        return 'a' + col;  // Player 1 pieces are a-h
    } else {
        return 'A' + col;  // Player 2 pieces are A-H
    }
}

bool Board::moveLink(int fromRow, int fromCol, int toRow, int toCol) {
    // Validate positions
    if (!isValidPosition(fromRow, fromCol) || !isValidPosition(toRow, toCol)) {
        return false;
    }

    Square& fromSquare = grid[fromRow][fromCol];
    Square& toSquare = grid[toRow][toCol];

    // Check if source has a link
    if (!fromSquare.hasLink()) {
        return false;
    }

    // Check if destination is empty or has opponent's link (for battle)
    if (toSquare.hasLink()) {
        // For now, just block the move if destination has any link
        // Will implement battle mechanics later
        return false;
    }

    // Move is valid, transfer the link
    toSquare.setLink(fromSquare.getLink());
    fromSquare.removeLink();
    notifyObservers();
    
    return true;
}

