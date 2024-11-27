module link;

int Link::getStrength() const
{
    return strength;
}

bool Link::isRevealed() const
{
    return revealed;
}

int Link::getOwner() const
{
    return owner;
}

void Link::reveal()
{
    revealed = true;
}

Link & Link::battle(Link &other)
{
    if (this->getStrength() >= other.getStrength)
    {
        return *this;
    }
    else
    {
        return other;
    }
}