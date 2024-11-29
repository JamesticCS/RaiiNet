// player.cc
#include "player.h"
Player::Player(int id) : playerId{id} {}

void Player::incrementDataCount() {
   downloadedData++;
}

void Player::incrementVirusCount() {
   downloadedVirus++;
} 

bool Player::hasWon() const {
   return downloadedData >= 4;
}

bool Player::hasLost() const {
   return downloadedVirus >= 4;
}

int Player::getPlayerId() const {
   return playerId;
}

int Player::getDataCount() const {
   return downloadedData;
}

int Player::getVirusCount() const {
   return downloadedVirus;
}

int Player::getRemainingAbilities() const {
   return remainingAbilities;
}

void Player::addLink(std::unique_ptr<Link> link) {
    links.emplace_back(std::move(link));
}

void Player::downloadLink(Link* link) {
    link->setDownloaded();
    if (link->isVirus()) {
        incrementVirusCount();
    } else {
        incrementDataCount();
    }
}

Link* Player::getLinkByIdentifier(char id) const {
    for (const auto& link : links) {
        if (link->getIdentifier() == id) {
            return link.get();
        }
    }
    return nullptr;
}

 const std::vector<std::unique_ptr<Link>>& Player::getLinks() const { return links; }