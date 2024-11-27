export module subject;
import <vector>;
import observer;
export class Subject
{
    std::vector<Observer *> observers;
    public:
        void notifyObservers();
        void attach(Observer *ob);
        void detach(Observer *ob);
        virtual ~Subject()=0;
};