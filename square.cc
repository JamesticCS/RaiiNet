export module square;
import link;
import <memory>;
export class Square
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
        Square(bool isServer, bool isSide, bool isTopBottom) 
            : serverPort{isServer}, sideEdge{isSide}, topOrBottomEdge{isTopBottom} {}
        bool hasLink() const;
        bool hasFirewall() const;
        bool isServerPort() const;
        bool isSideEdge() const;
        bool isTopOrBottomEdge() const;
        bool isEmpty() const;
        void placeFirewall(int playerID);
        Link* getLink() const;
        void setLink(std::unique_ptr<Link> newLink);
        void removeLink();


};