// linkboost.h
#ifndef LINKBOOST_H
#define LINKBOOST_H
#include "ability.h"

class LinkBoost : public Ability {
public:
    LinkBoost();
    bool execute(Board& board, Player& player, Player& opponent, const std::string& args) override;
};

#endif