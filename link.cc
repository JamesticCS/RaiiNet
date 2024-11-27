export module link;

// import player;

export class Link
{
    int strength;
    bool revealed;
    // Player * owner; when player class is implemented
    int owner;
    protected:
        Link(int strength, int owner) : strength{strength}, revealed{false}, owner{owner} {}
        

    public:
        virtual ~Link() = default;
        int getStrength() const;
        bool isRevealed() const;
        int getOwner() const;
        void reveal();
        Link battle(Link &other);
        virtual bool isVirus() const = 0; // pure virtual

};