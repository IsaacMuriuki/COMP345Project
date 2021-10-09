#include "../../include/map.h"
#include <iostream>
#include <stdio.h>
#include <string>

int main()
{
    const string MAPS_FOLDER = "../../maps/";

    string fileName = MAPS_FOLDER + "bigeurope.map";
    MapLoader loader(fileName);
    loader.loadMap(loader.readLines());
    Map* m = loader.getMap();
    cout << m->validate() << endl;
}

// TODO
// MapLoader  
// Add validate method to Map class 
// Destructors
// Copy constructors
// Driver




