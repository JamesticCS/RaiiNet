// square.h
#ifndef SQUARE_H
#define SQUARE_H

#include "link.h"
#include <memory>
class Square
{
    Link *link = nullptr;
    bool firewall = false;
    int firewallOwner = -1;
    int playedID = -1;
    bool serverPort = false;
    bool sideEdge = false;
    bool topOrBottomEdge = false;
    
    // friend class Board;
    public:
        Square() = default;
        Square(bool isServer, bool isSide, bool isTopBottom) 
            : serverPort{isServer}, sideEdge{isSide}, topOrBottomEdge{isTopBottom} {}
        bool hasLink() const;
        bool hasFirewall() const;
        bool isServerPort() const;
        bool isSideEdge() const;
        bool isTopOrBottomEdge() const;
        bool isEmpty() const;
        void placeFirewall(int playerID);
        Link* getLink();            
        void setLink(Link* newLink);
        void removeLink();
        


};
#endif
