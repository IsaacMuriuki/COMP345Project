#pragma once
#include <list>
#include <string>
#include <iostream>
using namespace std;

class ILoggable{
    public:
        virtual string stringToLog() = 0;
};

class Observer{
    public:
        Observer();
        ~Observer();
        virtual void Update(ILoggable* iLoggable) = 0;
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