#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "LoggingObserver.h"

#include<vector>
#include<string>

class Command : public ILoggable, public Subject{
    private:
        std::string effect;
    public:
        Command();
        Command(std::string effect);
        ~Command();
        void saveEffect(std::string newEffect);
        string stringToLog();
};

class CommandProcessor : public ILoggable, public Subject{
    private:
        std::vector<Command*> cmds;
        void readCommand(std::string cmdName); //Gets commands from the console as a string
        void saveCommand(std::string cmdName); //Stores the command internally in a collection of Command objects
        bool validate(Command cmd); //Check if the command is valid in the current game state
    public:
        CommandProcessor();
        ~CommandProcessor();
        Command* getCommand();
        string stringToLog();
};

class FileCommandProcessorAdapter{
    public:
        FileCommandProcessorAdapter();
        ~FileCommandProcessorAdapter();
        void readFile();
};

#endif