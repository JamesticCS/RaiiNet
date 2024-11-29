// polarize.cc
#include "polarize.h"

Polarize::Polarize() : Ability('P', "Polarize") {}

bool Polarize::execute(Board& board, Player& player, Player& opponent, const std::string& args) {
    if (args.empty()) return false;
    
    // Can be opponent's or player's link
    Link* link = player.getLinkByIdentifier(args[0]);
    if (!link) {
        link = opponent.getLinkByIdentifier(args[0]);
    }
    if (!link) return false;
    
    // Change type (will need to add this functionality to Link class)
    link->toggleType();
    link->reveal();  // Reveal since we've changed it
    return true;
}
