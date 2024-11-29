#include "linkboost.h"
#include "link.h"

LinkBoost::LinkBoost(Board* board) : board{board} {}

bool LinkBoost::execute(Square* square) {
    return false;  // Can't boost a square
}

bool LinkBoost::execute(Link* link) {
    if (used || !link || link->isDownloaded()) return false;
    link->setMovementRange(link->getMovementRange() + 1);  // Boost the link's movement range
    used = true;
    return true;
}

std::string LinkBoost::abilityName() const {
    return "Link Boost";
}
