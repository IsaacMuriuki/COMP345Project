#include "map.h"
#include "Drivers.h"
#include <stdio.h>
#include <filesystem>
namespace fs = std::experimental::filesystem;

void MapDriver::demo(){
    const string MAPS_FOLDER = "../../maps/";
    MapLoader loader;
    for (const auto & entry : fs::directory_iterator(MAPS_FOLDER)){
        cout << "Loading map: " << entry.path().filename() << endl;
        cout << "Validating..." << endl;
        Map* m = loader.loadMap(entry.path().string());
        cout << m->validate() << endl;
        delete m;
    }
}




