// virus.cc
#include "virus.h"
Virus::Virus(int strength, int owner, char identifier): Link{strength, owner, identifier} {}

bool Virus::isVirus() const
{
    return true;
}