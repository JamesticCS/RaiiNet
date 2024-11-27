export module player;

export class Player {
   int playerId;
   int downloadedData = 0;
   int downloadedVirus = 0; 
   int remainingAbilities = 5;

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
};