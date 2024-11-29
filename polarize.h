#ifndef POLARIZE_H
#define POLARIZE_H

#include "ability.h"
#include "square.h"
#include "link.h"
#include "data.h"
#include "virus.h"

class Polarize : public Ability {
public:
    bool execute(Square* square) override;
    bool execute(Link* link) override;
    std::string abilityName() const override;
    
private:
    bool used = false;
};

#endif // POLARIZE_H
