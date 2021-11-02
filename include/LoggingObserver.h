#pragma once
#include <list>
#include <string>
using namespace std;

class ILoggable{
    public:
        virtual ~ILoggable() {};
        virtual string stringToLog() = 0;
};

class Observer{
    public:
        ~Observer();
        virtual void Update(ILoggable) = 0;
    protected:
        Observer();
};

class Subject{
    public:
        virtual void Notify(ILoggable);
};

class LogObserver : public Observer{
    public:
        LogObserver();
        ~LogObserver();
        void Update(ILoggable);
};