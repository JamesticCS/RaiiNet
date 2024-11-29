#ifndef FIREWALL_H
#define FIREWALL_H

#include "ability.h"
#include "square.h"

class Firewall : public Ability {
public:
    bool execute(Square* square) override;
    bool execute(Link* link) override;
    std::string abilityName() const override;
    
private:
    bool used = false;
};

#endif // FIREWALL_H
