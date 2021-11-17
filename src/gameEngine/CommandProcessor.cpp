#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "CommandProcessor.h"
#include "Utilities.h"

using std::string, std::cout, std::cin, std::endl, std::ifstream;
namespace fs = std::filesystem;

// CommandProcessor class definition

CommandProcessor::CommandProcessor(){
    std::cout << "\nCommand Processor initialized." << std::endl;
}

CommandProcessor::CommandProcessor(GameEngine* _gameEngine) : CommandProcessor::CommandProcessor(){
    gameEngine = _gameEngine;
}

CommandProcessor::~CommandProcessor(){
    gameEngine = nullptr;
}

/* Gets commands from the console as a string */
string CommandProcessor::readCommand(){
    //Take in the user input
    string cmdstr;
    cout << "\nEnter your command: " << endl;
    cin.clear(); 
    cin.sync();
    
    cin >> cmdstr; 
    cout << endl;
    
    return cmdstr;
}

/* Stores the command internally in a collection of Command objects */
void CommandProcessor::saveCommand(Command* cmd){
    savedCmds.push_back(cmd);
}

/* Check if the command is valid in the current game state */
bool CommandProcessor::validate(Command* cmd){

    string cmdID = cmd->getEffect();

    //Check if the command is valid in the current state
    vector<string> stateCmds = gameEngine->getCurrentState()->getCmds();
    if(std::find(stateCmds.begin(), stateCmds.end(), cmdID) != stateCmds.end()) {
        return true;    
    } 
    else
    {
        //If the current state does not consider the command valid, prints an error message
        string errorMsg =  "Error: Command '" + cmd->getEffect() + "' not recognized in state '" + gameEngine->getCurrentState()->getName() + "'";
        cmd->saveEffect(errorMsg);
        cout << errorMsg << endl; 
        return false;
    }
}

Command* CommandProcessor::getCommand(){

    string cmdstr = readCommand();
    Command* cmd = new Command(cmdstr);
    bool validCmd = validate(cmd); //Validates the command and execute the appropriate state transition
    saveCommand(cmd);
    
    if(validCmd) return cmd;
    else return nullptr;
}

void CommandProcessor::setGameEngine(GameEngine* _gameEngine){
    gameEngine = _gameEngine;
}

// FileCommandProcessorAdapter class definition

FileCommandProcessorAdapter::FileCommandProcessorAdapter(){
    
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filename){
    readFile(filename);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    
}

/**
 * Saves the content of a file into a vector of command strings.
 * 
 * @param filename the path to the commands file.
 **/
void FileCommandProcessorAdapter::readFile(string filename, bool append){
    
    string filepath = "../../cmds/" + filename; //for mac -> "../cmds/"

    std::ifstream input;
    input.open(filepath.c_str());

    if (!input) {
        cout << "\nInvalid filename..." << endl;
        return;
    }

    if(!append){
        queue<string> empty;
        std::swap(cmdstrings, empty);
    }
    
    cout << "Reading from " << filename << " ..." << endl;

    string cmdstr;
	while (getline(input, cmdstr)) {
        cout << cmdstr << endl;
		cmdstrings.push(cmdstr);
	}

    cout << "\nEnd of file..." << endl;
}

void FileCommandProcessorAdapter::readFile(string filename){
    readFile(filename, false);
}

/* Gets commands from the console as a string */
string FileCommandProcessorAdapter::readCommand(){
    
    if(cmdstrings.empty()) return "";

    string cmdstr = cmdstrings.front();
    cout << "Read Command: " << cmdstr << endl;
    cmdstrings.pop();
    return cmdstr;
}

// Command class definition

Command::Command(){
    effect = "null";
}

Command::Command(string _effect){
    saveEffect(effect = _effect);
}

Command::~Command(){

}

void Command::saveEffect(string newEffect){
    effect = newEffect;
}

string Command::getEffect(){
    return effect;
}