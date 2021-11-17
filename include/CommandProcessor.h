#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include "LoggingObserver.h"

#include<vector>
#include<string>
#include<queue>
#include"GameEngine.h"

using std::string, std::vector, std::deque;

class GameEngine;

class Command : public ILoggable, public Subject{
    private:
        string effect;
    public:
        Command();
        Command(std::string _effect);
        ~Command();
        Command(const Command& cmd);
        Command& operator=(Command&& cmd);
        friend std::ostream &operator<<(std::ostream &os, const Command &cmd);
        void saveEffect(std::string newEffect);
        string getEffect();
        string getDescription();
        vector<string> getParams();
        string stringToLog();
        Command *clone();
};
class CommandProcessor : public ILoggable, public Subject{
    protected:
        GameEngine* gameEngine;
        vector<Command*> savedCmds;
        virtual string readCommand(); //Gets commands from the console as a string
        void saveCommand(Command* cmd); //Stores the command internally in a collection of Command objects
        bool validate(Command* cmd); //Check if the command is valid in the current game state
    public:
        CommandProcessor();
        CommandProcessor(GameEngine* _gameEngine);
        ~CommandProcessor();
        CommandProcessor(const CommandProcessor& cmdProcessor);
        CommandProcessor& operator=(CommandProcessor&& cmdProcessor);
        Command* getCommand();
        void setGameEngine(GameEngine* _gameEngine);
        string stringToLog();
        CommandProcessor *clone();
};

class FileLineReader {
    private:
        deque<string> cmdstrings;
        const std::string EXIT_CMD = "exit";
    public:
        FileLineReader();
        ~FileLineReader();
        FileLineReader(const FileLineReader& flr);
        FileLineReader& operator=(FileLineReader&& flr);
        bool readFile(string filename);
        string readLineFromFile();
        FileLineReader *clone();
};

class FileCommandProcessorAdapter : public CommandProcessor{
    private: 
        FileLineReader* flr;
        string readCommand() override; //Gets commands from the command queue
        FileCommandProcessorAdapter& operator=(FileCommandProcessorAdapter&& flrToCmdAdapter);
    public:
        FileCommandProcessorAdapter();
        FileCommandProcessorAdapter(FileLineReader* _flr);
        ~FileCommandProcessorAdapter();
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter& flrToCmdAdapter);
        FileCommandProcessorAdapter *clone();
};

#endif