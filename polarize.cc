#include "polarize.h"
#include "data.h"
#include "virus.h"
#include <iostream>

Polarize::Polarize() : used(false) {}

bool Polarize::execute(Square* square) {
    if (used || !square || !square->hasLink()) {
        return false;  // The ability has been used or no link is present
    }

    Link* link = square->getLink();
    
    // If the link is downloaded, polarization is not possible
    if (link->isDownloaded()) {
        return false;
    }

    // Save the current type of the link (Virus or Data)
    bool wasVirus = link->isVirus();
    
    // Create a new link with the opposite type (Data ↔ Virus)
    std::unique_ptr<Link> newLink;
    if (wasVirus) {
        newLink = std::make_unique<Data>(link->getStrength(), link->getOwner(), link->getIdentifier());
    } else {
        newLink = std::make_unique<Virus>(link->getStrength(), link->getOwner(), link->getIdentifier());
    }

    // Set the new polarized link on the square
    square->setLink(newLink.get());

    // If the link was revealed, reveal the new link as well
    if (link->isRevealed()) {
        newLink->reveal();
    }

    // Mark the ability as used
    used = true;

    std::cout << "Polarized link at (" << square->getRow() << ", " << square->getCol() << ") "
              << (wasVirus ? "Virus" : "Data") << " to "
              << (wasVirus ? "Data" : "Virus") << ".\n";

    return true;
}

bool Polarize::execute(Link* link) {
    if (used || !link || link->isDownloaded()) {
        return false;  // The ability has been used or the link is downloaded
    }

    // Save the current type of the link (Virus or Data)
    bool wasVirus = link->isVirus();
    
    // Create a new link with the opposite type (Data ↔ Virus)
    std::unique_ptr<Link> newLink;
    if (wasVirus) {
        newLink = std::make_unique<Data>(link->getStrength(), link->getOwner(), link->getIdentifier());
    } else {
        newLink = std::make_unique<Virus>(link->getStrength(), link->getOwner(), link->getIdentifier());
    }

    // If the link was revealed, reveal the new link as well
    if (link->isRevealed()) {
        newLink->reveal();
    }

    // Set the new polarized link on the same location
    // Here we assume there's a method to replace the link directly, for example:
    // link->replaceWith(newLink.get());
    
    // Mark the ability as used
    used = true;

    std::cout << "Polarized link " << link->getIdentifier() << " from "
              << (wasVirus ? "Virus" : "Data") << " to "
              << (wasVirus ? "Data" : "Virus") << ".\n";

    return true;
}

std::string Polarize::abilityName() const {
    return "Polarize";  // Return the name of the ability
}
