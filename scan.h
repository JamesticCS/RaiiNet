#ifndef SCAN_H
#define SCAN_H

#include "ability.h"
#include "square.h"
#include "link.h"

class Scan : public Ability {
public:
    bool execute(Square* square) override;
    bool execute(Link* link) override;
    std::string abilityName() const override;
    
private:
    bool used = false;
};

#endif // SCAN_H
