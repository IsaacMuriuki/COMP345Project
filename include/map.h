#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "player.h"
using namespace std;

class Continent;
class Player;

class Territory {
private:
    int _id;
    string _name;
    Continent* _continent;
    int _units;
    Player* _owner;
    vector<Territory*> _adjacentTerritories;

public:
    Territory();
    Territory(int id, string name, Continent* continent, int units);
    ~Territory();
    Territory(const Territory& territory);
    Territory& operator=(const Territory &territory);
    bool operator==(const Territory& territory);
    friend std::ostream& operator<<(std::ostream &stream, const Territory& territory);

    /**
     * Adds a territory to the list of territories adjacent to this one.
     * 
     * @param territory the adjacent territory.
     **/
    void addAdjacentTerritory(Territory* territory);

    /**
     * Gets the id of this continent.
     * 
     * @return id of this continent.
     **/
    int getId();

    /**
     * Gets the name of this territory.
     * 
     * @return the name of this territory.
     **/
    string getName();

    /**
     * Gets the continent this territory is part of.
     * 
     * @return continent this territory is part of.
     **/
    Continent* getContinent();

    /**
     * Gets the number of units placed on this territory by the owner.
     * 
     * @return the number of units placed on this territory by the owner.
     **/
    int getUnits();

    /**
     * Gets the owner of the territory.
     * 
     * @return the player who owns this territory if any; NULL otherwise.
     **/
    Player* getOwner();

    /**
     * Gets a list of all adjacent territories.
     * 
     * @return all adjadcent territories.
     **/
    vector<Territory*> getAdjacentTerritories();

    /**
     * Sets the number of units placed on this territory by the owner.
     * 
     * @param units the number of units.
     **/
    void setUnits(int units);

   /**
     * Sets the player that owns this territory.
     * 
     * @param owner the owner of the territory.
     **/
    void setOwner(Player* owner);
};

class Continent {
private:
    int _id;
    string _name;
    int _armyValue;
    vector<Territory*> _territories;

public:
    Continent();
    Continent(int id, string name, int armyValue);
    ~Continent();
    Continent(const Continent& continent);
    Continent& operator=(const Continent &continent);
    bool operator==(const Continent& continent);
    friend std::ostream& operator<<(std::ostream &stream, const Continent& continent);

    /**
     * Adds a territory to the list of territories on this continent.
     * 
     * @param territory the territory.
     **/
    void addTerritory(Territory* territory);

    /**
     * Finds a territory within this continent by id.
     * 
     * @param id the id of the territory to find.
     * @return the territory if found; NULL otherwise.
     **/
    Territory* findTerritory(int id);

    /**
     * Gets the id of this continent.
     * 
     * @return id of this continent.
     **/
    int getId();

    /**
     * Gets the name of this continent.
     * 
     * @return the name of this continent.
     **/
    string getName();

    /**
     * Get the army value this continent.
     * 
     * @return the army value of this continent.
     **/
    int getArmyValue();
    
    /**
     * Gets all territories that are part of this continent.
     * 
     * @return all territories that are part of this continent.
     **/
    vector<Territory*> getTerritories();
};

class Map {
private:
    vector<Territory*> _territories;
    vector<Continent*> _continents;

public:
    Map();
    Map(vector<Territory*> territories, vector<Continent*> continents);
    ~Map();
    Map(const Map& map);
    Map& operator=(const Map &map);
    friend std::ostream &operator<<(std::ostream &stream, const Map& map);

    /**
     * Finds a continent within the by id.
     * 
     * @param id the id of the continent to find.
     * @return the continent if found; NULL otherwise.
     **/
    Continent* findContinent(int id);

    /**
     * Finds a territory in the map by id.
     * 
     * @param id the id of the territory to find.
     * @return the territory if found; NULL otherwise.
     **/
    Territory* findTerritory(int id);

    /**
     * Finds a territory on a specific continent in the map by id.
     * 
     * @param territoryId the id of the territory to find.
     * @param continentId the id of the continent to find in.
     * @return the territory if found; NULL otherwise.
     **/
    Territory* findTerritory(int territoryId, int continentId);

    /**
     * Checks if the order is valid.
     * 
     * @return true if not execute and valid; false otherwise.
     **/
    bool validate();

    /**
     * Performs DFS traversal on class member _territories.
     * 
     * @param indexOfTerritory index of starting territory.
     * @param visited keeps track if whether territories are visited or not.
     **/
    void dfs(int indexOfTerritory, vector<bool> &visited);

    /**
     * Performs DFS traversal on a specific subgraph.
     * 
     * @param subgraph the subgraph.
     * @param indexOfTerritory index of starting territory.
     * @param visited keeps track if whether territories are visited or not.
     **/
    void dfs(vector<Territory*> subgraph, int indexOfTerritory, vector<bool> &visited);
};

class MapLoader{
private:
    string _filePath;
    Map* _map;

public:
    MapLoader();
    ~MapLoader();
    MapLoader(const MapLoader& mapLoader);

    /**
     * Creates a Map object from loading a map file.
     * 
     * @param filePath the path to the map file.
     * @return the created map object if the file is valid, NULL otherwise.
     **/
    Map* loadMap(string filePath);
};

// For split() function https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template<typename Out>
void split(const std::string &s, char delim, Out result);
vector<string> split(const string &s, char delim);