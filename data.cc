export module data;

import link; 
export class Data: public Link
{
    public:
        Data(int strength, int owner);
        bool isVirus() const override;
};