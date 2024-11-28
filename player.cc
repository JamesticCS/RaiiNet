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