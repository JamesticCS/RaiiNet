export module virus;


export class Virus: public Link
{
    public:
        Virus(int strength, int owner);
        bool isVirus() const override;
};