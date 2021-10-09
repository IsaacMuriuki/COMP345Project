#include "../../include/map.h"
#include "Drivers.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void MapDriver::demo()
{
    const string MAPS_FOLDER = "../../maps/";

    string fileName = MAPS_FOLDER + "bigeurope.map";
    MapLoader loader(fileName);
    loader.loadMap(loader.readLines());
    Map* m = loader.getMap();
    cout << m->validate() << endl;
    cout << *m << endl;
}




