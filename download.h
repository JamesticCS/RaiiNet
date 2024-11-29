#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "ability.h"
#include "square.h"
#include "link.h"

class Download : public Ability {
public:
    bool execute(Square* square) override;
    bool execute(Link* link) override;
    std::string abilityName() const override;
    
private:
    bool used = false;
};

#endif // DOWNLOAD_H
