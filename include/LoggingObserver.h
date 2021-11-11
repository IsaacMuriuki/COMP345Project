#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable{
    public:
        virtual string stringToLog() = 0;
};

class Observer{
    public:
        ~Observer();
        virtual void Update(ILoggable* iLoggable) = 0;
    protected:
        Observer();
};

class Subject{
    private:
        list<Observer*> *_observers;
    public:
        Subject();
        ~Subject();
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify(ILoggable* iLoggable);
};

class LogObserver : public Observer{
    public:
        LogObserver();
        ~LogObserver();
        void Update(ILoggable* iLoggable);
};