#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Utilities.h"
#include "map.h"

Territory::Territory() {
   this->_id = 0;
   this->_name = "";
   this->_continent = new Continent();
   this->_units = 0;
   this->_owner = new Player();
   this->_adjacentTerritories = vector<Territory*>();
}

Territory::Territory(int id, string name, Continent* continent) {
    this->_id = id;
    this->_name = name;
    this->_continent = new Continent(*continent);
    this->_units = 0;
    this->_owner = new Player();
    this->_adjacentTerritories = vector<Territory*>();
}

Territory::~Territory(){
    delete _continent; _continent = NULL;
    delete _owner; _owner = NULL;
    for ( int i = 0; i < _adjacentTerritories.size(); i++) {
        _adjacentTerritories[i] = NULL;
    }
}

Territory::Territory(const Territory& territory){
    this->_id = territory._id;
    this->_name = territory._name;
    this->_continent = territory._continent;
    this->_units = territory._units;
    this->_owner = territory._owner;
    this->_adjacentTerritories = territory._adjacentTerritories;
}

Territory& Territory::operator=(const Territory& territory){
	this->_id = territory._id;
    this->_name = territory._name;
    this->_continent = territory._continent;
    this->_units = territory._units;
    this->_owner = territory._owner;
    this->_adjacentTerritories = territory._adjacentTerritories;

    return *this;
}

bool Territory::operator==(const Territory& territory){
	return this->_id == territory._id;
}

std::ostream& operator<<(std::ostream& stream, const Territory& territory){
    stream << "Name: " << territory._name << endl <<
                  "Continent: " << territory._continent->getName() << endl <<
                  "Number of units: " << territory._units << endl <<
                  "Owned by: " << territory._owner->getName() << endl; 
    return stream;
}

/**
 * Adds a territory to the list of territories adjacent to this one.
 * 
 * @param territory the adjacent territory.
 **/
void Territory::addAdjacentTerritory(Territory* territory){
    for (size_t i = 0; i < _adjacentTerritories.size(); i++)
	{
		// Avoid duplicates
		if ( _adjacentTerritories[i] == territory)
			return;
	}
	this->_adjacentTerritories.push_back(territory);
}

int Territory::getId() { return this->_id; }

string Territory::getName() { return this->_name; }

Continent* Territory::getContinent() { return this->_continent; }

int Territory::getUnits() { return this->_units; }

Player* Territory::getOwner() { return this->_owner; }

vector<Territory*> Territory::getAdjacentTerritories() { return this->_adjacentTerritories; }

void Territory::setUnits(int units) { this->_units = units; }

void Territory::setOwner(Player* owner) { this->_owner = owner; }

// CONTINENT

Continent::Continent(){
    this->_id = 0;
    this->_name = "";
    this->_armyValue = 0;
    this->_territories = vector<Territory*>();
}

Continent::Continent(int id, string name, int armyValue){
    this->_id = id;
    this->_name = name;
    this->_armyValue = armyValue;
    this->_territories = vector<Territory*>();
}

Continent::~Continent(){
    for ( int i = 0; i < _territories.size(); i++ ) {
        _territories[i] = NULL;
    }
}

Continent::Continent(const Continent& continent){
    this->_id = continent._id;
    this->_name = continent._name;
    this->_armyValue = continent._armyValue;
    this->_territories = continent._territories;
}

Continent& Continent::operator=(const Continent& continent){
	this->_id = continent._id;
    this->_name = continent._name;
    this->_armyValue = continent._armyValue;
    this->_territories = continent._territories;

    return *this;
}

bool Continent::operator==(const Continent& continent){
	return this->_id == continent._id;
}

std::ostream& operator<<(std::ostream& stream, const Continent& continent){
    stream << "Continent name: " << continent._name << endl;
	stream << "Army value: " << continent._armyValue << endl;
	stream << "List of territories:\n";
	for (size_t i = 0; i < continent._territories.size(); i++) {
		stream << continent._territories[i]->getName() << endl;
	}
	return stream;
}

/**
 * Adds a territory to the list of territories on this continent.
 * 
 * @param territory the territory.
 **/
void Continent::addTerritory(Territory* territory){
    for (size_t i = 0; i < _territories.size(); i++)
	{
		// Avoid duplicates
		if ( _territories[i] == territory)
			return;
	}
	this->_territories.push_back(territory);
}

/**
 * Finds a territory within this continent by id.
 * 
 * @param id the id of the territory to find.
 * @return the territory if found; NULL otherwise.
 **/
Territory* Continent::findTerritory(int id){
	for (size_t i = 0; i < _territories.size(); i++)
	{
		if ( _territories[i]->getId() == id)
			return _territories[i];
	}
	return NULL;
}

int Continent::getId() { return this->_id; }

string Continent::getName() { return this->_name; }

int Continent::getArmyValue() { return this->_armyValue; }

vector<Territory *> Continent::getTerritories() { return this->_territories; }

// MAP

Map::Map(){
    this->_territories = vector<Territory*>();
	this->_continents = vector<Continent*>();
}

Map::Map(vector<Territory*> territories, vector<Continent*> continents){
    this->_territories = territories;
	this->_continents = continents;
}

Map::~Map(){
    for ( int i = 0; i < _territories.size(); i++ ) {
		delete _territories[i];
        _territories[i] = NULL;
    }
	for ( int i = 0; i < _continents.size(); i++ ) {
		delete _continents[i];
        _continents[i] = NULL;
    }
}

Map::Map(const Map& map){
    this->_territories = map._territories;
	this->_continents = map._continents;
}

Map& Map::operator=(const Map& map){
    this->_territories = map._territories;
	this->_continents = map._continents;

    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Map& map){
    stream << "Info of map:" << endl;
	stream << "Number of territories: " << map._territories.size() << endl;
	stream << "Number of continents: " << map._continents.size() << endl;
	return stream;
}

vector<Continent*> Map::getContinents() const {return _continents;}
vector<Territory*> Map::getTerritories() const {return _territories;}

/**
 * Finds a continent in the map by id.
 * 
 * @param id the id of the continent to find.
 * @return the continent if found; NULL otherwise.
 **/
Continent* Map::findContinent(int id){
	for (size_t i = 0; i < _continents.size(); i++)
	{
		if ( _continents[i]->getId() == id)
			return _continents[i];
	}
	return NULL;
}

/**
 * Finds a territory in the map by id.
 * 
 * @param id the id of the territory to find.
 * @return the territory if found; NULL otherwise.
 **/
Territory* Map::findTerritory(int id){
	for (size_t i = 0; i < _territories.size(); i++)
	{
		if ( _territories[i]->getId() == id)
			return _territories[i];
	}
	return NULL;
}

/**
 * Finds a territory on a specific continent in the map by id.
 * 
 * @param territoryId the id of the territory to find.
 * @param continentId the id of the continent to find in.
 * @return the territory if found; NULL otherwise.
 **/
Territory* Map::findTerritory(int territoryId, int continentId){
	Continent* continent = findContinent(continentId);
	if(continent == NULL)
		return NULL;
	vector<Territory*> territories = continent->getTerritories();
	for (size_t i = 0; i < territories.size(); i++)
	{
		if ( territories[i]->getId() == territoryId)
			return territories[i];
	}
	return NULL;
}

/**
 * Checks if the map is valid.
 * 
 * @return true if map is valid; false otherwise.
 **/
bool Map::validate(){
	if(_territories.empty() || _continents.empty()){
		return false;
	}

	// 1) Check if map is connected

	// do for all territories
	for (int i = 0; i < _territories.size(); i++) {
		// initialize visited
		vector<bool> visited(_territories.size());
		// start dfs from first territory
		dfs(i, visited);
		// if dfs doesn't visit all territories, then map is invalid
		if (find(visited.begin(), visited.end(), false) != visited.end()) {
            return false;
        }
	}

	// 2) Check if all continents are a connected subgraph

	// do for all continents
	for (int i = 0; i < _continents.size(); i++) {
		// get subgraph of continent
		vector<Territory*> subgraph = _continents.at(i)->getTerritories();
		// do for all territories in subgraph
		for(int j = 0; j < subgraph.size(); j++){
			// initialize visited
			vector<bool> visited(subgraph.size()); 
			// start dfs from first territory
			dfs(subgraph, j, visited);
			// if dfs doesn't visit all territories of continent, then map is invalid
			if (find(visited.begin(), visited.end(), false) != visited.end()) {
				return false;
			}
		}
	}

	// 3) each territory belongs to one continent

	for (size_t i = 0; i < _territories.size(); i++) {
		int id = _territories.at(i)->getId();
		Continent* continentOfTerritory = _territories.at(i)->getContinent();
		// check if any continent owns this territory other than the one assigned to it
		for (size_t j = 0; j < _continents.size(); j++){
			Continent* continent = _continents.at(j);
			if((*continentOfTerritory) == (*continent)) {
				continue;
			}
			if(findTerritory(id, continent->getId()) != NULL){
				return false;
			}
		}
	}

	return true;
}

/**
 * Performs DFS traversal on class member _territories.
 * 
 * @param indexOfTerritory index of starting territory.
 * @param visited keeps track if whether territories are visited or not.
 **/
void Map::dfs(int indexOfTerritory, vector<bool> &visited){
	visited[indexOfTerritory] = true;
	vector<Territory*> adjTerritories = _territories.at(indexOfTerritory)->getAdjacentTerritories();
	vector<Territory*>::iterator i;
	// process all adjacent territories that are not visited yet
	for(i = adjTerritories.begin(); i != adjTerritories.end(); ++i){
		if(!visited[(*i)->getId() - 1]) {
			dfs((*i)->getId() - 1, visited);
		}
	} 
}

/**
 * Performs DFS traversal on a specific subgraph.
 * 
 * @param subgraph the subgraph.
 * @param indexOfTerritory index of starting territory.
 * @param visited keeps track if whether territories are visited or not.
 **/
void Map::dfs(vector<Territory*> subgraph, int indexOfTerritory, vector<bool> &visited){
	visited[indexOfTerritory] = true;
	vector<Territory*> adjTerritories = subgraph.at(indexOfTerritory)->getAdjacentTerritories();
	vector<Territory*>::iterator i;
	// process all adjacent territories that are not visited yet
	for(i = adjTerritories.begin(); i != adjTerritories.end(); ++i){
		// skip territories not in continent
		auto it = find(subgraph.begin(), subgraph.end(), (*i));
		if(it != subgraph.end()){
			int indexOfAdjTerritory = it - subgraph.begin();
			if(!visited[indexOfAdjTerritory]) {
				dfs(subgraph, indexOfAdjTerritory, visited);
			}
		}
	} 
}

// MAPLOADER

MapLoader::MapLoader(){
    this->_filePath = "";
    this->_map = new Map();
}

MapLoader::~MapLoader(){
    _map = NULL;
}

MapLoader::MapLoader(const MapLoader& mapLoader){
    this->_filePath = mapLoader._filePath;
    this->_map = mapLoader._map;
}

/**
 * Creates a Map object from loading a map file.
 * 
 * @param filePath the path to the map file.
 * @return the created map object if the file is valid, NULL otherwise.
 **/
Map* MapLoader::loadMap(string filePath){

    vector<Continent*> continents;
    vector<Territory*> territories;
    ifstream input;
    bool error;

    // Read lines
	input.open(filePath.c_str());

	if (!input) {
		return NULL;
	}

	vector<string> lines;
	string line;
	while (getline(input, line)) {
		lines.push_back(line);
	}

    // Create Map
    error = lines.empty();
	if (!error) {
		try {
			int continentId = 0;
			int continentStart = -1;
			int territoryStart = -1;
			int borderStart = -1;

			for (int i = 0; i < lines.size(); i++)
			{
				if (lines[i].find("[continents]") != string::npos)
				{
					continentStart = (i + 1);
					break;
				}
			}

			// if [continents] does not exist, then the file is invalid
			if (continentStart == -1)
			{
				return NULL;
			}
			
			for (int i = continentStart; i < lines.size(); i++)
			{
				continentId++;
				if (lines[i].find("[countries]") != string::npos)
				{
					territoryStart = (i + 1);
					break;
				} 
				else if(lines[i].empty())
				{
					continue;
				}
				// create continents
				vector<string> lineData = split(lines[i], ' ');
				int id = continentId;
				string name = lineData[0];
				int armyValue = stoi(lineData[1]);
				continents.push_back(new Continent(id, name, armyValue));
			}

			// if [territories] does not exist, then the file is invalid
			if (territoryStart == -1)
			{
				return NULL;
			}

			for (int i = territoryStart; i < lines.size(); i++)
			{
				if (lines[i].find("[borders]") != string::npos)
				{
					borderStart = (i + 1);
					break;
				}
				else if(lines[i].empty())
				{
					continue;
				}
				// create territories
				vector<string> lineData = split(lines[i], ' ');
				int id = stoi(lineData[0]);
				string name = lineData[1];
				Continent* continent = continents.at(stoi(lineData[2]) - 1);
				territories.push_back(new Territory(id, name, continent));
			}

			// if [borders] does not exist, then the file is invalid
			if (borderStart == -1)
			{
				return NULL;
			}

			for (int i = borderStart; i < lines.size(); i++)
			{
				if(lines[i].empty())
				{
					break;
				}
				// add adjacent territories to territories
				vector<string> lineData = split(lines[i], ' ');
				Territory* territory = territories.at(stoi(lineData[0]) - 1);
				for(int i = 1; i < lineData.size(); i++){
					int territoryId = stoi(lineData[i]);
					Territory* adjacentTerritory = territories.at(territoryId - 1);
					territory->addAdjacentTerritory(adjacentTerritory);
				}
				// add territores to continents
				continents.at(territory->getContinent()->getId() - 1)->addTerritory(territory);
			}

			_map = new Map(territories, continents);
			return _map;
		}
		catch( const std::invalid_argument&) {
			return NULL;
		}
	}

    return NULL;
}
