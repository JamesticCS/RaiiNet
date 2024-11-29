#include "firewall.h"

bool Firewall::execute(Square* square) {
    if (used || !square || square->hasLink() || square->isServerPort()) 
        return false;
    square->placeFirewall(/* player id needed */);
    used = true;
    return true;
}

bool Firewall::execute(Link* link) {
    return false;
}

std::string Firewall::abilityName() const {
    return "Firewall";
}
