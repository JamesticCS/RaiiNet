// board.h
#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "subject.h"
#include <vector>
#include "player.h"

class Board : public Subject
{
    static const int rows = 8;
    static const int cols = 8;
    std::vector<std::vector<std::unique_ptr<Square>>> grid;
    void setServerPorts();
    void setEdgeSquares();  
    bool isP1ServerPort(int row, int col) const;
    bool isP2ServerPort(int row, int col) const;
    
    public:
        Board();
        bool hasLinkAt(int row, int col) const;
        bool isValidPosition(int row, int col) const;  
        bool isServerPortAt(int row, int col) const;
        char getLinkDisplayChar(int row, int col) const;  // Returns piece letter

        class BoardIterator
        {
            Board *board;
            int currRow;
            int currCol;
            BoardIterator(Board* board, int currRow, int currCol);
            
            public:
                Square& operator*();

                bool operator!=(const BoardIterator& other);

                BoardIterator & operator++();
                friend class Board;
        };

    BoardIterator begin();
    
    BoardIterator end();

    void placeLink(int row, int col, Link* link);
    void placeLinkNoNotify(int row, int col, Link* link);
    bool moveLink(int fromRow, int fromCol, int toRow, int toCol, Player& currentPlayer, Player& otherPlayer);
    bool isOpponentServerPort(int row, int col, int playerId) const;
    bool isOwnServerPort(int row, int col, int playerId) const;
};
#endif
