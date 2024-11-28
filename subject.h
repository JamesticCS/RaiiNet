// subject.h
#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"
class Subject
{
    std::vector<Observer *> observers;
    public:
        void notifyObservers();
        void attach(Observer *ob);
        void detach(Observer *ob);
        virtual ~Subject()=0;
};
#endif
