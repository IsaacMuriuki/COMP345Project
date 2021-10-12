#include "map.h"

// TERRITORY

Territory::Territory() {
   this->_id = 0;
   this->_name = "";
   this->_continent = new Continent();
   this->_units = 0;
   this->_owner = new Player();
   this->_adjacentTerritories = vector<Territory*>();
}

Territory::Territory(int id, string name, Continent* continent, int units) {
    this->_id = id;
    this->_name = name;
    this->_continent = new Continent(*continent);
    this->_units = units;
    this->_owner = new Player();
    this->_adjacentTerritories = vector<Territory*>();
}

Territory::~Territory(){
    delete _continent; _continent = NULL;
    delete _owner; _owner = NULL;
    for ( int i = 0; i < _adjacentTerritories.size(); i++ ) {
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

std::ostream& operator<< (std::ostream& stream, const Continent& continent){
    stream << "Continent name: " << continent._name << ":\n";
	stream << "Army value: " << continent._armyValue << endl;
	stream << "Number of countries: " << continent._territories.size() << endl;
	stream << "List of territories:\n";
	for (size_t i = 0; i < continent._territories.size(); i++) {
		stream << "\t" << continent._territories[i] << endl;
	}
	stream << endl;
	return stream;
}

void Continent::addTerritory(Territory* territory){
    for (size_t i = 0; i < _territories.size(); i++)
	{
		// Avoid duplicates
		if ( _territories[i] == territory)
			return;
	}
	this->_territories.push_back(territory);
}

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
    stream << "\nInfo of map:" << endl;
	stream << "List of territories:" << endl;
	for (size_t i = 0; i < map._territories.size(); i++)
	{
        Territory* t = map._territories[i];
		stream << *t << "\n";
	}
	stream << endl;
	return stream;
}

Continent* Map::findContinent(int id){
	for (size_t i = 0; i < _continents.size(); i++)
	{
		if ( _continents[i]->getId() == id)
			return _continents[i];
	}
	return NULL;
}

Territory* Map::findTerritory(int id){
	for (size_t i = 0; i < _territories.size(); i++)
	{
		if ( _territories[i]->getId() == id)
			return _territories[i];
	}
	return NULL;
}

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

Map* MapLoader::loadMap(string filePath){

    vector<Continent*> continents;
    vector<Territory*> territories;
    ifstream input;
    bool error;

    // Read lines
	input.open(filePath.c_str());

	if (!input) {
		cout << "File " << filePath << " is invalid" << endl;
		return new Map();
	}

	vector<string> lines;
	string line;
	while (getline(input, line)) {
		lines.push_back(line);
	}

    // Create Map
    error = lines.empty();
	if (!error) {
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
			cout << "The file " << filePath << " is not a valid .map file." << endl;
			return new Map();
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
			cout << "The file " << filePath << " is not a valid .map file. We cannot create a Parser object." << endl;
			return new Map();
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
            Territory* territory = new Territory(id, name, continent, 0);
            territories.push_back(new Territory(id, name, continent, 0));
		}

		// if [borders] does not exist, then the file is invalid
		if (borderStart == -1)
		{
			cout << "The file " << filePath << " is not a valid .map file. We cannot create a Parser object." << endl;
			return new Map();
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

    return new Map();
}

// SPLIT() FUNCTION from https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template<typename Out>
void split(const std::string &s, char delim, Out result) {
	stringstream ss;
	ss.str(s);
	string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, back_inserter(elems));
	return elems;
}