#include "scan.h"

bool Scan::execute(Square* square) {
    return false;
}

bool Scan::execute(Link* link) {
    if (used || !link) return false;
    link->reveal();
    used = true;
    return true;
}

std::string Scan::abilityName() const {
    return "Scan";
}
