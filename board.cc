export module board;


import square;
import subject;
import <vector>;


export class Board : public Subject
{
    static const int rows = 8;
    static const int cols = 8;
    std::vector<std::vector<Square>> grid; 
    void setServerPorts();
    void setEdgeSquares();
    bool isValidPosition(int row, int col) const;  
    bool isServerPortAt(int row, int col) const;
    bool hasLinkAt(int row, int col) const;
    char getLinkDisplayChar(int row, int col) const;  // Returns piece letter  

    public:
        Board();

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
    bool moveLink(int fromRow, int fromCol, int toRow, int toCol);
};