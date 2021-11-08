#include "map.h"
#include "Drivers.h"
#include <stdio.h>
#include <filesystem>
namespace fs = std::filesystem;

void MapDriver::demo(){
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
    }
}




