// polarize.h
#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"

class Polarize : public Ability {
public:
    Polarize();
    bool execute(Board& board, Player& player, Player& opponent, const std::string& args) override;
};

#endif
