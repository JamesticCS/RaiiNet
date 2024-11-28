// virus.h

#ifndef VIRUS_H
#define VIRUS_H

#include "link.h" 
class Virus: public Link
{
    public:
        Virus(int strength, int owner, char identifier);
        bool isVirus() const override;
};
#endif
