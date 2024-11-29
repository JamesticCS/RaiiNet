// player.h

#ifndef PLAYER_H
#define PLAYER_H
#include "link.h"
#include <vector>
#include <memory>
// #include "ability.h"
#include <iostream>
class Player {
   int playerId;
   int downloadedData = 0;
   int downloadedVirus = 0; 
   int remainingAbilities = 5;
   std::vector<std::unique_ptr<Link>> links;
 // std::vector<std::unique_ptr<Ability>> abilities;
   bool UsedAbilityThisTurn = false;  

public:
   explicit Player(int id); // must explicility create player
   
   // Download tracking 
   void incrementDataCount();
   void incrementVirusCount();
   
   // Status checks
   bool hasWon() const;
   bool hasLost() const;
   
   // Getters
   int getPlayerId() const;
   int getDataCount() const; 
   int getVirusCount() const;
   int getRemainingAbilities() const;

   // Link management

   void addLink(std::unique_ptr<Link> link);
   void downloadLink(Link* link);  // Marks link as downloaded and updates counters
   Link* getLinkByIdentifier(char id) const;
   const std::vector<std::unique_ptr<Link>>& getLinks() const;

   // abilities
   /*
   void displayAbilities() const;
   void addAbility(std::unique_ptr<Ability> ability);

   bool hasUsedAbilityThisTurn() const;
   void setAbilityUsedThisTurn(bool used); */
};
#endif
