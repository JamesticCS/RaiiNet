Virus::Virus(int strength, int owner): Link{strength, owner} {}

bool Data::isVirus() const override
{
    return true;
}