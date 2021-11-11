#include "LoggingObserver.h"

Observer::Observer(){}

Observer::~Observer(){}

Subject::Subject(){
    _observers = new list<Observer*>;
}

Subject::~Subject(){
    delete _observers;
}

void Subject::Attach(Observer* o){
    _observers->push_back(o);
}

void Subject::Detach(Observer* o){
    _observers->remove(o);
}

void Subject::Notify(ILoggable* iLoggable){
    for(list<Observer*>::iterator i = _observers->begin(); i!= _observers->end(); ++i){
        (*i)->Update(iLoggable);
    }
}

LogObserver::LogObserver(){};

LogObserver::~LogObserver(){};

void LogObserver::Update(ILoggable* iLoggable){
    iLoggable->stringToLog();
}
