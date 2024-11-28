// data.h
#ifndef DATA_H
#define DATA_H

#include "link.h" 
class Data: public Link
{
    public:
        Data(int strength, int owner, char identifier);
        bool isVirus() const override;
};
#endif
