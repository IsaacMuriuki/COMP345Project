#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "LoggingObserver.h"

#include<vector>
#include<string>
#include"GameEngine.h"

using std::string, std::vector;

class GameEngine;

class Command : public ILoggable, public Subject{
    private:
        string effect;
    public:
        Command();
        Command(std::string _effect);
        ~Command();
        void saveEffect(std::string newEffect);
        std::string getEffect();
        string stringToLog();
};

class CommandProcessor : public ILoggable, public Subject{
    private:
        GameEngine* gameEngine;
        vector<Command*> cmds;
        string readCommand(); //Gets commands from the console as a string
        void saveCommand(Command* cmd); //Stores the command internally in a collection of Command objects
        bool validate(Command* cmd); //Check if the command is valid in the current game state
    public:
        CommandProcessor();
        CommandProcessor(GameEngine* _gameEngine);
        ~CommandProcessor();
        Command* getCommand();
        void setGameEngine(GameEngine* _gameEngine);
        string stringToLog();
};

class FileCommandProcessorAdapter{
    public:
        FileCommandProcessorAdapter();
        ~FileCommandProcessorAdapter();
        void readFile();
};

#endif