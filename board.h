// board.h
#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include "subject.h"
#include <vector>


class Board : public Subject
{
    static const int rows = 8;
    static const int cols = 8;
    std::vector<std::vector<std::unique_ptr<Square>>> grid;
    void setServerPorts();
    void setEdgeSquares();  
    int lastDownloadPlayer = 0;  // Which player got the download
    bool wasDownloadedPieceVirus = false;
    bool downloadHappened = false;
    
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

    void placeLink(int row, int col, std::unique_ptr<Link> link);
    void placeLinkNoNotify(int row, int col, std::unique_ptr<Link> link);
    bool moveLink(int fromRow, int fromCol, int toRow, int toCol);
    bool wasDownloaded() const { return downloadHappened; }
    int getDownloadPlayer() const { return lastDownloadPlayer; }
    bool wasVirusDownloaded() const { return wasDownloadedPieceVirus; }
    void clearDownloadStatus() { downloadHappened = false; }
};
#endif
