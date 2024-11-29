#ifndef LINKBOOST_H
#define LINKBOOST_H

#include "ability.h"
#include "link.h"

class LinkBoost : public Ability {
public:
    bool execute(Square* square) override;  // Can't boost a square
    bool execute(Link* link) override;
    std::string abilityName() const override;
    
private:
    bool used = false;
};

#endif // LINKBOOST_H
