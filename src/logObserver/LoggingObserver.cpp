#include "LoggingObserver.h"

Observer::Observer(){};

Observer::~Observer(){};

Subject::Subject(){};

Subject::~Subject(){};

LogObserver::LogObserver(){};

LogObserver::~LogObserver(){};

void LogObserver::Update(ILoggable log){
    log.stringToLog();
}
