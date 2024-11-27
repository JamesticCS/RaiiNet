export module virus;

import link; 
export class Virus: public Link
{
    public:
        Virus(int strength, int owner);
        bool isVirus() const override;
};