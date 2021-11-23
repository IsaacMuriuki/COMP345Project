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

    gameEngine->SetCmdProcessor(nullptr);
    gameEngine = nullptr;
}

CommandProcessor& CommandProcessor::operator=(CommandProcessor&& cmdProcessor){
    
    if(this != &cmdProcessor){
        setGameEngine(cmdProcessor.gameEngine);
        savedCmds = cmdProcessor.savedCmds;
    }
    
    return *this;
}

CommandProcessor::CommandProcessor(const CommandProcessor &cmdProcessor) : CommandProcessor(cmdProcessor.gameEngine)
{
    for(Command* cmd : cmdProcessor.savedCmds)
        savedCmds.push_back(cmd->clone());
}

/**
 * Reads commands from the console as a string
 * @return command string read from the console
 **/
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

/** 
 * Stores the command internally in a collection of Command objects 
**/
void CommandProcessor::saveCommand(Command* cmd){
    savedCmds.push_back(cmd);

    // Notifies observer of the command.
    Notify(this);
}

/** 
 * Check if the command is valid in the current game state 
 * @return true if the command is valid
 * @param cmd Command object to validate
**/
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

/**
 * Read, process, validate and save commands
 * @return validated command
 **/
Command* CommandProcessor::getCommand(){

    string cmdstr = readCommand();
    Command* cmd = new Command(cmdstr);
    bool validCmd = validate(cmd); //Validates the command and execute the appropriate state transition
    saveCommand(cmd);
    
    if(validCmd) return cmd;
    else return nullptr;
}

/**
 * Assign a game engine to this command processor
 * @param _gameEngine game engine to assign
 **/
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

CommandProcessor *CommandProcessor::clone(){ return new CommandProcessor(*this);}

// FileLineReader class definition

FileLineReader::FileLineReader(){
    
}

FileLineReader::~FileLineReader(){
    
}

FileLineReader::FileLineReader(const FileLineReader& flr){
    cmdstrings = flr.cmdstrings;
}

FileLineReader& FileLineReader::operator=(FileLineReader&& flr){
    
    if(this != &flr){
        cmdstrings = flr.cmdstrings;
    }
    
    return *this;
}

/**
 * Reads the next line from the content of the file saved prior
 * @return string read from the content of the file
 **/
string FileLineReader::readLineFromFile(){
    if(cmdstrings.empty()) return "";

    string cmdstr = cmdstrings.front();
    cout << "Read Command: " << cmdstr << endl;
    cmdstrings.pop_front();
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
    
    cout << "\nReading from " << filename << " ..." << endl;

    string cmdstr;
	while (getline(input, cmdstr)) {
        cout << cmdstr << endl;
		cmdstrings.push_back(cmdstr);
	}

    cmdstrings.push_back(EXIT_CMD); //Add exit command at the end

    cout << "\nEnd of file..." << endl;

    return true;
}

FileLineReader *FileLineReader::clone(){ return new FileLineReader(*this);}

// FileCommandProcessorAdapter class definition

FileCommandProcessorAdapter::FileCommandProcessorAdapter(){
    
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader* _flr){
    flr = _flr;
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    delete flr;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& flrToCmdAdapter) : FileCommandProcessorAdapter(flrToCmdAdapter.flr->clone()) { }

FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator=(FileCommandProcessorAdapter&& flrToCmdAdapter){
    if(this != &flrToCmdAdapter){
        flr = flrToCmdAdapter.flr;
    }
    
    return *this;
}

/**
 * Reads commands from a saved file as a string
 * @return command string read from a saved file
 **/
string FileCommandProcessorAdapter::readCommand(){
    return flr->readLineFromFile();
}

FileCommandProcessorAdapter *FileCommandProcessorAdapter::clone(){ return new FileCommandProcessorAdapter(*this);}

// Command class definition

Command::Command(){
    effect = "null";
}

Command::Command(string _effect){
    saveEffect(effect = _effect);
}

Command::~Command(){

}

Command::Command(const Command& cmd) : Command(cmd.effect) {}

Command& Command::operator=(Command&& cmd)
{   
    if(this != &cmd){
        saveEffect(cmd.effect);
    }
    
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Command &cmd)
{
    os << cmd.effect;
    return os;
}

/**
 * Reads commands from a saved file as a string
 * @param newEffect new effect to save in the command
 **/
void Command::saveEffect(string newEffect){
    effect = newEffect;

     // Notifies observer of the command's effect.
    Notify(this);
}

/**
 * Effect accessor
 * @return effect
 **/
string Command::getEffect(){
    return effect;
}

/**
 * Geat command's effect description
 * @return effect description
 **/
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

/**
 * Method to split the command into parameters
 * @return a vector of string parameters
 **/
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

Command *Command::clone(){ return new Command(*this);}