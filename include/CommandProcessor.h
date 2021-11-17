#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#include<vector>
#include<string>
#include<queue>
#include"GameEngine.h"

using std::string, std::vector, std::queue;

class GameEngine;

class Command{
    private:
        string effect;
    public:
        Command();
        Command(std::string _effect);
        ~Command();
        void saveEffect(std::string newEffect);
        string getEffect();
        vector<string> getParams();
};

class CommandProcessor{
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
        Command* getCommand();
        void setGameEngine(GameEngine* _gameEngine);
};

class FileLineReader {
    private:
        queue<string> cmdstrings;
        const std::string EXIT_CMD = "exit";
    public:
        FileLineReader();
        ~FileLineReader();
        bool readFile(string filename);
        string readLineFromFile();
};

class FileCommandProcessorAdapter : public CommandProcessor{
    private: 
        FileLineReader* flr;
        string readCommand() override; //Gets commands from the command queue
    public:
        FileCommandProcessorAdapter();
        FileCommandProcessorAdapter(FileLineReader* _flr);
        ~FileCommandProcessorAdapter();
};

#endif