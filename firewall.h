// firewall.h
#ifndef FIREWALL_H
#define FIREWALL_H
#include "ability.h"

class Firewall : public Ability {
public:
    Firewall();
    bool execute(Board& board, Player& player, Player& opponent, const std::string& args) override;
};

#endif
