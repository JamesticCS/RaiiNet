// scan.h
#ifndef SCAN_H
#define SCAN_H
#include "ability.h"

class Scan : public Ability {
public:
    Scan();
    bool execute(Board& board, Player& player, Player& opponent, const std::string& args) override;
};
#endif