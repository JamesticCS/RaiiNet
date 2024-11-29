#ifndef ABILITY_H
#define ABILITY_H

#include <string>

// Forward declaration of classes Square and Link
class Square;
class Link;

class Ability {
protected:
    bool isUsedVar = false; // Track if the ability has been used

public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Ability() = default;

    // Pure virtual functions that must be overridden in derived classes
    virtual bool execute(Square* square) = 0;  // Execute ability on a Square
    virtual bool execute(Link* link) = 0;      // Execute ability on a Link
    virtual std::string abilityName() const = 0; // Get the name of the ability

    // Check if the ability has been used
    bool isUsed() const {
        return isUsedVar;
    }

    // Set the ability as used
    void setUsed(bool used) {
        isUsedVar = used;
    }
};

#endif // ABILITY_H
