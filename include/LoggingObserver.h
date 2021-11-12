#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>    
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

        /**
         * Attach given Observer object to the list of attached observers of the Subject.
         * 
         * @param o the Observer object to be attached.
         **/
        virtual void Attach(Observer* o);

        /**
         * Detach given Observer object from the list of attached observers of the Subject.
         * 
         * @param o the Observer object to be detached.
         **/
        virtual void Detach(Observer* o);

        /**
         * Trigger to writing an entry to a log file.
         * 
         * @param iLoggable the ILoggable object containing the entry.
         **/
        virtual void Notify(ILoggable* iLoggable);
};

class LogObserver : public Observer{
    public:
        LogObserver();
        ~LogObserver();

        /**
         * Write returned entry of the iLoggable object from its stringToLog() function to a log file.
         * 
         * @param iLoggable the ILoggable object to get the string from.
         **/
        void Update(ILoggable* iLoggable);
};