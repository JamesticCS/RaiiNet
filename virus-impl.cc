Virus::Virus(int strength, int owner): Link{strength, owner} {}

bool Virus::isVirus() const override
{
    return true;
}