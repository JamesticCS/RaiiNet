// square.h
#ifndef SQUARE_H
#define SQUARE_H

#include "link.h"
#include <memory>
class Square
{
    std::unique_ptr<Link> link;
    bool firewall = false;
    int firewallOwner = -1;
    int playedID = -1;
    bool serverPort = false;
    bool sideEdge = false;
    bool topOrBottomEdge = false;
    
    // friend class Board;
    public:
        Square() = default;
        Square(Square&&) = default;                    // Move constructor
        Square& operator=(Square&&) = default;         // Move assignment
        Square(const Square&) = delete;                // Copy constructor
        Square& operator=(const Square&) = delete;     // Copy assignment
        Square(bool isServer, bool isSide, bool isTopBottom) 
            : serverPort{isServer}, sideEdge{isSide}, topOrBottomEdge{isTopBottom} {}
        bool hasLink() const;
        bool hasFirewall() const;
        bool isServerPort() const;
        bool isSideEdge() const;
        bool isTopOrBottomEdge() const;
        bool isEmpty() const;
        void placeFirewall(int playerID);
        std::unique_ptr<Link>& getLink();              // Non-const version - can modify
        const std::unique_ptr<Link>& getLink() const;  // Const version - can only read
        void setLink(std::unique_ptr<Link> newLink);
        void removeLink();
        


};
#endif
