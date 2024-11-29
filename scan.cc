// scan.cc
#include "scan.h"

Scan::Scan() : Ability('S', "Scan") {}

bool Scan::execute(Board& board, Player& player, Player& opponent, const std::string& args) {
    if (args.empty()) return false;
    
    // Can only scan opponent's links
    Link* link = opponent.getLinkByIdentifier(args[0]);
    if (!link) return false;
    
    // Reveal the link
    link->reveal();
    return true;
}