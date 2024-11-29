// player.h

#ifndef PLAYER_H
#define PLAYER_H
#include "link.h"
#include <vector>
#include <memory>
class Player {
   int playerId;
   int downloadedData = 0;
   int downloadedVirus = 0; 
   int remainingAbilities = 5;
   std::vector<std::unique_ptr<Link>> links;


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
};
#endif
