#include "map.h"
#include "Drivers.h"
#include <stdio.h>
#include <boost/filesystem.hpp>

void MapDriver::demo(){
    const string MAPS_FOLDER = "../../maps/";
    /*struct dirent *entry;
    DIR *dir = opendir("../maps/");
    if (dir != NULL) {
        while ((entry = readdir (dir)) != NULL) {
            cout << entry << endl;
                cout << "Loading map: " << entry->d_name << endl;
                cout << "Validating..." << endl;
                
                string filePath = MAPS_FOLDER + entry->d_name;
                MapLoader loader;
                Map* m = loader.loadMap(filePath);
                //cout << *m << endl;
                cout << m->validate() << endl;
                filePath = MAPS_FOLDER + "solar.map";
                m = loader.loadMap(filePath);
                cout << m->validate() << endl;
                delete m;
                
            }
            closedir (dir);    
    } else {
        perror ("");
        return EXIT_FAILURE;
    }*/
}




