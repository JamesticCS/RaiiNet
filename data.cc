// data.cc
#include "data.h"
Data::Data(int strength, int owner, char identifier): Link{strength, owner, identifier} {}

bool Data::isVirus() const
{
    return false;
}