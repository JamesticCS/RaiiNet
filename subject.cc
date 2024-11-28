// subject.cc
#include "subject.h"
Subject::~Subject(){}

void Subject::notifyObservers()
{
    for (auto ob: observers)
    {
        ob->notify();
    }
}

void Subject::attach(Observer *ob)
{
    observers.emplace_back(ob);
}

void Subject::detach(Observer *ob)
{
   for (auto it = observers.begin(); it != observers.end(); ++it)
   {
        if (*it == ob)
        {
            observers.erase(it);
            break;
        }
   }
}