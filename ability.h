// ability.h
#ifndef ABILITY_H
#define ABILITY_H

#include "board.h"
#include "player.h"

class Ability {
protected:
    char identifier;  // First letter of ability name 
    std::string name;

public:
    Ability(char id, std::string name);
    virtual ~Ability() = default;
    
    // Pure virtual execute - each ability must implement
    virtual bool execute(Board& board, Player& player, Player& opponent, 
                        const std::string& args) = 0;
    
    // Getters
    char getIdentifier() const;
    const std::string& getName() const;
};

#endif
