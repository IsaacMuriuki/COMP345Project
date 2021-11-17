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

    // Notifies observer of the command.
    Notify(this);
}

/* Check if the command is valid in the current game state */
bool CommandProcessor::validate(Command* cmd){

    vector<string> tokens = cmd->getParams();
    string cmdID = tokens[0];

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

/**
 * Returns an entry of the command to be logged.
 * 
 * @return entry as a string.
 * */
string CommandProcessor::stringToLog(){
    return "Command: " + savedCmds[savedCmds.size() - 1]->getEffect();
}

// FileLineReader class definition

FileLineReader::FileLineReader(){
    
}

FileLineReader::~FileLineReader(){
    
}

string FileLineReader::readLineFromFile(){
    if(cmdstrings.empty()) return "";

    string cmdstr = cmdstrings.front();
    cout << "Read Command: " << cmdstr << endl;
    cmdstrings.pop();
    return cmdstr;
}

/**
 * Saves the content of a file into a vector of command strings.
 * 
 * @param filename the path to the commands file.
 * @return wether or not the file was successfully parsed.
 **/
bool FileLineReader::readFile(string filename){
    
    string filepath = "../../cmds/" + filename; //for mac -> "../cmds/"

    std::ifstream input;
    input.open(filepath.c_str());

    if (!input) {
        cout << "\nInvalid filename..." << endl;
        return false;
    }

    queue<string> empty;
    std::swap(cmdstrings, empty);
    
    cout << "\nReading from " << filename << " ..." << endl;

    string cmdstr;
	while (getline(input, cmdstr)) {
        cout << cmdstr << endl;
		cmdstrings.push(cmdstr);
	}

    cmdstrings.push(EXIT_CMD); //Add exit command at the end

    cout << "\nEnd of file..." << endl;

    return true;
}

// FileCommandProcessorAdapter class definition

FileCommandProcessorAdapter::FileCommandProcessorAdapter(){
    
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* _flr){
    flr = _flr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    
}

/* Gets commands from the console as a string */
string FileCommandProcessorAdapter::readCommand(){
    return flr->readLineFromFile();
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

     // Notifies observer of the command's effect.
    Notify(this);
}

string Command::getEffect(){
    return effect;
}

string Command::getDescription(){
    string cmd = split(effect, ' ')[0];
    if(cmd == "loadmap"){
        return "Loaded a map.";
    } else if(cmd == "validatemap"){
        return "Validated a map.";
    } else if(cmd == "addplayer"){
        return "Added a player.";
    } else if(cmd == "gamestart"){
        return "Game started.";
    } else if(cmd == "replay"){
        return "Replaying the game.";
    } else if (cmd == "quit"){
        return "Quit game";
    } else {
        return cmd;
    }
}

vector<string> Command::getParams(){
    return split(getEffect(), ' ');
}

/**
 * Returns an entry of the effect of a command to be logged.
 * 
 * @return entry as a string.
 * */
string Command::stringToLog(){
    return "Command's Effect: " + getDescription();
}