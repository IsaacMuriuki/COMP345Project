#include "CommandProcessor.h"

#include <iostream>
#include <stdio.h>
#include<string>
#include <filesystem>

using std::string, std::cout, std::cin, std::endl;
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
    cmds.push_back(cmd);
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

FileCommandProcessorAdapter::~FileCommandProcessorAdapter(){
    
}

void FileCommandProcessorAdapter::readFile(){
    /*
    const string MAPS_FOLDER = "../../maps/"; // for mac this works ->   const string MAPS_FOLDER = "../maps";
    MapLoader loader;
    // read all files in valid maps folder
    try{
        for (const auto & entry : fs::directory_iterator(MAPS_FOLDER)){
            cout << "\nLoading map: " << entry.path().filename() << endl;
            cout << "Validating..." << endl;
            Map* m = loader.loadMap(entry.path().string());
            // check if file is valid
            if(m != NULL){
                // check if map is valid
                if(m->validate()){
                    cout << *m << endl;
                } else {
                    cout << "Invalid map" << endl;
                }
            } else {
                cout << "The file " << entry.path().filename() << " is not a valid .map file." << endl;
            }
        }
    } catch(const fs::filesystem_error){
        cout << "\nInvalid folder..." << endl;
    }*/
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