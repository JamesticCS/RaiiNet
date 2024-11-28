// link.cc
#include "link.h"

Link::Link(int strength, int owner, char identifier):
 strength{strength}, revealed{false}, owner{owner},
  identifier{identifier} {}
int Link::getStrength() const
{
    return strength;
}

bool Link::isRevealed() const
{
    return revealed;
}

int Link::getOwner() const
{
    return owner;
}

void Link::reveal()
{
    revealed = true;
}

Link & Link::battle(Link &other)
{
    if (this->getStrength() >= other.getStrength())
    {
        return *this;
    }
    else
    {
        return other;
    }
}

char Link::getIdentifier() const
{
    return identifier;
}