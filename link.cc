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

std::string Link::getDisplayString() const {
    if (!revealed && !downloaded) {
        return "?";
    }
    char typeChar;
    if (isVirus()) {
        typeChar = 'V';
    } else {
        typeChar = 'D';
    }
    // std::string(1, typeChar) creates string a length 1
    return std::string(1, typeChar) + std::to_string(strength);
}

std::string Link::getRawDisplayString() const {
    char typeChar;
    if (isVirus()) {
        typeChar = 'V';
    } else {
        typeChar = 'D';
    }
    // std::string(1, typeChar) creates string a length 1
    return std::string(1, typeChar) + std::to_string(strength);
}

bool Link::isDownloaded() const { return downloaded; }
void Link::setDownloaded() { downloaded = true; }
