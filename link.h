// link.h
#ifndef LINK_H
#define LINK_H

// import player;

class Link
{
    int strength;
    bool revealed;
    // Player * owner; when player class is implemented
    int owner;
    char identifier; 
    protected:
        Link(int strength, int owner, char identifier);

    public:
        virtual ~Link() = default;
        int getStrength() const;
        bool isRevealed() const;
        int getOwner() const;
        void reveal();
        Link& battle(Link &other);
        char getIdentifier() const;
        virtual bool isVirus() const = 0; // pure virtual

};
#endif
