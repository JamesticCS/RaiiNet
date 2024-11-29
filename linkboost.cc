// linkboost.cc
#include "linkboost.h"

LinkBoost::LinkBoost() : Ability('L', "Link Boost") {}
bool LinkBoost::execute(Board& board, Player& player, Player& opponent, const std::string& args) {
    if (args.empty()) return false;
    
    // Find the link to boost
    Link* link = player.getLinkByIdentifier(args[0]);
    if (!link) return false;
    
    // Set the link's boost status
    link->setLinkBoosted(true);
    return true;
}