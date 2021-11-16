#include "LoggingObserver.h"

Observer::Observer(){}
Observer::~Observer(){}

Subject::Subject(){
    _observers = new list<Observer*>;
}

Subject::~Subject(){
    delete _observers;
}

/**
 * Attach given Observer object to the list of attached observers of the Subject.
 * 
 * @param o the Observer object to be attached.
 **/
void Subject::Attach(Observer* o){
    _observers->push_back(o);
}

/**
 * Detach given Observer object from the list of attached observers of the Subject.
 * 
 * @param o the Observer object to be detached.
 **/
void Subject::Detach(Observer* o){
    _observers->remove(o);
}

/**
 * Trigger to writing an entry to a log file.
 * 
 * @param iLoggable the ILoggable object containing the entry.
 **/
void Subject::Notify(ILoggable* iLoggable){
    for(list<Observer*>::iterator i = _observers->begin(); i!= _observers->end(); ++i){
        (*i)->Update(iLoggable);
    }
}

LogObserver::LogObserver(){}
LogObserver::~LogObserver(){}

/**
 * Write returned entry of the iLoggable object from its stringToLog() function to a log file.
 * 
 * @param iLoggable the ILoggable object to get the string from.
 **/
void LogObserver::Update(ILoggable* iLoggable){
    // assuming this might have path problems with mac
    ofstream outfile ("./../../gamelog.txt", ios_base::app);
    // get timestamp to add to log file
    std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timestamp = std::put_time(localtime(&current_time), "%Y-%m-%d %H:%M:%S");
    // write to log file
    outfile << timestamp << ": " << iLoggable->stringToLog() << endl;
    outfile.close();
}
