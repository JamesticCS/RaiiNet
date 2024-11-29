// download.h
#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "ability.h"

class Download : public Ability {
public:
    Download();
    bool execute(Board& board, Player& player, Player& opponent, const std::string& args) override;
};

#endif
