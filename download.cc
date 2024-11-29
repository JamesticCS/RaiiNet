// download.cc
#include "download.h"

Download::Download() : Ability('D', "Download") {}

bool Download::execute(Board& board, Player& player, Player& opponent, const std::string& args) {
    if (args.empty()) return false;
    
    // Find opponent's link to download
    Link* link = opponent.getLinkByIdentifier(args[0]);
    if (!link) return false;
    
    // Download the link
    player.downloadLink(link);
    // Remove from board if it's still there
    board.removeLinkByIdentifier(args[0]);
    return true;
}