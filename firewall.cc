// firewall.cc
#include "firewall.h"
#include <sstream>

Firewall::Firewall() : Ability('F', "Firewall") {}

bool Firewall::execute(Board& board, Player& player, Player& opponent, const std::string& args) {
    std::istringstream iss(args);
    int row, col;
    if (!(iss >> row >> col)) return false;
    
    // Validate position
    if (!board.isValidPosition(row, col)) return false;
    if (board.hasLinkAt(row, col)) return false;
    if (board.isServerPortAt(row, col)) return false;
    
    // Place firewall
    board.placeFirewall(row, col, player.getPlayerId());
    return true;
}
