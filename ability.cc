// ability.cc
#include "ability.h"
Ability::Ability(char id, std::string name) : identifier{id}, name{name} {}
char Ability::getIdentifier() const { return identifier; }
const std::string& Ability::getName() const { return name; }
