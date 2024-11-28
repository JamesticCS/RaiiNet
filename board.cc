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

void Board::placeLink(int row, int col, std::unique_ptr<Link> link) {
    if (isValidPosition(row, col)) {
        grid[row][col]->setLink(std::move(link));
        notifyObservers();
    }
}

void Board::placeLinkNoNotify(int row, int col, std::unique_ptr<Link> link) {
    if (isValidPosition(row, col)) {
        grid[row][col]->setLink(std::move(link));
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
    Link* link = grid[row][col]->getLink().get();;
    return link->getIdentifier();
}

bool Board::moveLink(int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidPosition(fromRow, fromCol) || !isValidPosition(toRow, toCol)) {
        return false;
    }

    auto& fromSquare = grid[fromRow][fromCol];
    auto& toSquare = grid[toRow][toCol];

    if (!fromSquare->hasLink()) {
        return false;
    }

    if (toSquare->hasLink()) {
        return false;
    }

    toSquare->setLink(std::move(fromSquare->getLink())); 
    notifyObservers();
    return true;
}

