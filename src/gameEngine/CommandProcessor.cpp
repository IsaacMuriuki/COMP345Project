#include "CommandProcessor.h"

#include <iostream>
#include <stdio.h>
#include<string>
#include <filesystem>

using std::string, std::cout, std::cin, std::endl;
namespace fs = std::filesystem;

// CommandProcessor class definition

CommandProcessor::CommandProcessor(){

}

CommandProcessor::~CommandProcessor(){
    
}

/* Gets commands from the console as a string */
void CommandProcessor::readCommand(string cmdName){
    //Take in the user input
    std::string cmd;
    cout << "\nEnter your command: " << std::endl;
    cin.clear(); 
    cin.sync();
    
    cin >> cmd; 
    cout << std::endl;
    
    //Validates the command and execute the appropriate state transition
    saveCommand(cmd);
}

/* Stores the command internally in a collection of Command objects */
void CommandProcessor::saveCommand(string cmdName){
    Command* cmd = new Command(cmdName);
    cmds.push_back(cmd);
}
/* Check if the command is valid in the current game state */
bool CommandProcessor::validate(Command cmd){
    return true;
}

Command* CommandProcessor::getCommand(){
    return new Command();
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

}

Command::Command(string cmdName){

}

Command::~Command(){

}

void Command::saveEffect(string newEffect){
    effect = newEffect;
}