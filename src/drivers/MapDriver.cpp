#include "map2.h"
#include "Drivers.h"
#include <iostream>
#include <stdio.h>

void MapDriver::demo()
{
    const string MAPS_FOLDER = "../../maps/";
    string filePath = MAPS_FOLDER + "artic.map";
    MapLoader loader;
    Map* m = loader.loadMap(filePath);
    //cout << *m << endl;
    cout << m->validate() << endl;
    filePath = MAPS_FOLDER + "solar.map";
    m = loader.loadMap(filePath);
    cout << m->validate() << endl;
    delete m;
}




