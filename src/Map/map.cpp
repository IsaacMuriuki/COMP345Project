#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "map.h"

using namespace std;

// TERRITORY

Territory::Territory() : id(0), name(""), continent(""), numArmies(0) {}

Territory::Territory(int id, string name, string continent, int numArmies) : id(id), name(name), continent(continent), numArmies(numArmies) {}

int Territory::getId() { return id; }

string Territory::getName() { return name; }

string Territory::getContinent() { return continent; }

int Territory::getNumArmies() { return numArmies; }

Player Territory::getPlayer() { return player; }

void Territory::setNumArmies(int numArmies) { this->numArmies = numArmies; }

void Territory::setPlayer(Player player) { this->player = player; }

bool Territory::operator==(Territory territory)const
{
	return this->name == territory.name;
}

std::ostream& operator<< (std::ostream& stream, Territory territory)
{
    return stream << "Name: " << territory.getName() << endl <<
                  "Continent: " << territory.getContinent() << endl <<
                  "Number of armies: " << territory.getNumArmies() << endl;
}

// NODE

Node::Node() : territory(), adjList(vector<Node *>()), visited(false) {}

Node::Node(Territory territory) : territory(territory), adjList(vector<Node *>()), visited(false) {}

Node::Node(Territory territory, vector<Node *> adjList) : territory(territory), adjList(adjList), visited(false) {}

Territory Node::getTerritory() { return territory; }

vector<Node *> Node::getAdjList() { return adjList; }

Territory* Node::getPointerToTerritory() const { return const_cast<Territory*>(&territory); }

void Node::setAdjList(vector<Node *> newAdjList) {
    if (!adjList.empty())
        adjList.clear();
    for (size_t i = 0; i < newAdjList.size(); i++) {
        adjList.push_back(newAdjList[i]);
    }
}

void Node::setVisited(bool visisted) { this->visited = visited; }

bool Node::isVisited() { return visited; }

// Method used to add a pointer to a node to the adjacency list of this node
void Node::addNode(Node *node)
{
	for (size_t i = 0; i < adjList.size(); i++)
	{
		// Avoid duplicates
		if (adjList[i]->getTerritory() == node ->getTerritory())
			return;
	}
	this->adjList.push_back(node);
}

bool operator<(const Node &lhs, const Node &rhs){
	return lhs.getPointerToTerritory()->getNumArmies() < rhs.getPointerToTerritory()->getNumArmies();
}

std::ostream& operator << (std::ostream& stream, Node& node)
{
	stream << "Info of the node:\n" << node.getTerritory() << endl;
	stream << "Adjacent nodes: ";
    for (int i = 0; i < node.adjList.size(); i++) 
    {
        stream << node.adjList[i]->getTerritory().getName();
        if (i < node.adjList.size() - 1)
            stream << " -> ";
    }
    stream << "\n";
    return stream;
}


// CONTINENT

Continent::Continent(): id(0), name(""), armyValue(0), nodesInContinent(vector<Node*>()) {}

Continent::Continent(int id, string name, int armyValue): id(id), name(name), armyValue(armyValue), nodesInContinent(vector<Node*>()) {}

int Continent::getId() { return id; }

string Continent::getName() { return name; }

int Continent::getArmyValue() { return armyValue; }

vector<Node*>* Continent::getNodesInContinent() { return &nodesInContinent; }

void Continent::addNode(Node* node)
{
	nodesInContinent.push_back(node);
}

std::ostream& operator << (std::ostream& stream, Continent& continent)
{
	stream << "Continent name: " << continent.getName() << ":\n";
	stream << "Army value: " << continent.getArmyValue() << endl;
	stream << "Number of countries: " << continent.getNodesInContinent()->size() << endl;
	stream << "List of territories:\n";
	for (size_t i = 0; i < continent.getNodesInContinent()->size(); i++) {
		stream << "\t" << (*continent.getNodesInContinent())[i]->getTerritory().getName() << endl;
	}
	stream << endl;
	return stream;
}


// MAP

Map::Map() : numVertices(0) { }

Map::Map(int numVertices, vector<Node>& nodes) : numVertices(numVertices)
{
	// If num vertices not equal to the number of nodes being added,
	// something went wrong and so the the vectorOfNodes object will not be set.
	try {
		if (numVertices != nodes.size())
			throw new exception;
		vectorOfNodes = nodes;
	}
	catch (const exception& e) {
		cout << "The number of nodes in the node vector is not as expected." << endl;
	}
}

vector<Node*>* Map::getVectorOfNodes()
{
	vector<Node*>* nodes = new vector<Node*>();
	for(int i = 0; i < numVertices; i++)
	{
		nodes->push_back(&vectorOfNodes[i]);
	}
	return nodes;
}

int Map::getNumTerritories() { return numVertices; };

void Map::addNode(Node& node)
{
	vectorOfNodes.push_back(node);
	numVertices = vectorOfNodes.size();
}

// Add edge between two nodes in the map
void Map::addEdge(Node *node1, Node *node2)
{
	for (size_t i = 0; i < vectorOfNodes.size(); i++)
	{
		if (vectorOfNodes[i].getPointerToTerritory()->getName() == node1->getPointerToTerritory()->getName())
		{
			vectorOfNodes[i].addNode(node2);
		}
		if (vectorOfNodes[i].getPointerToTerritory()->getName() == node2->getPointerToTerritory()->getName())
		{
			vectorOfNodes[i].addNode(node1);
		}
	}
}


bool Map::areConnectedByEdge(Node* node1, Node* node2) {
    for (int i = 0; i < node1->getAdjList().size(); i++) {
        if (node1->getAdjList()[i] == node2)
            return true;
    }
    return false;
}

// Valdiate map
bool Map::validate(){
	if(! isMapConnected()){
		return false;
	} 
	return true;
}

// Returns false if visitAdjacentNodes() fails to visit all nodes, meanings it's not connected.
// Used for validating a map.
bool Map::isMapConnected()
{
	bool mapIsConnected = true;
    if(vectorOfNodes.empty())
        return false;
    vector<Node *> initialAdjListNode = vectorOfNodes[0].getAdjList();

    if (initialAdjListNode.empty())
        return false;

	visitAdjacentNodes(initialAdjListNode);

    for (size_t i = 0; i < vectorOfNodes.size(); i++) {
        if (!vectorOfNodes[i].isVisited()) {
            mapIsConnected = false;
            break;
        }
    }
    // Reinitialize visisted
    for (size_t i = 0; i < vectorOfNodes.size(); i++) {
        vectorOfNodes[i].setVisited(false);
    }
    return mapIsConnected;
}

// Helper method used for DFS
void Map::visitAdjacentNodes(vector<Node*> adjListNode)
{
	if (!adjListNode.empty())
	{
		for (size_t i = 0; i < adjListNode.size(); i++)
		{
			if (!adjListNode[i]->isVisited())
			{
				for (size_t j = 0; j < vectorOfNodes.size(); j++)
				{
					if (adjListNode[i]->getTerritory() == vectorOfNodes[j].getTerritory())
					{
						if (!vectorOfNodes[j].isVisited())
						{
							vectorOfNodes[j].setVisited(true);
							visitAdjacentNodes(vectorOfNodes[j].getAdjList());
						}
					}
				}
			}
		}
	}
}

ostream& operator << (ostream& stream, Map& map)
{
	stream << "Info of this map:\n";
	stream << "Number of vertices: " << map.numVertices << endl;
	stream << "Array of nodes:\n";
	for (size_t i = 0; i < map.vectorOfNodes.size(); i++)
	{
		stream << map.vectorOfNodes[i] << "\n";
	}
	return stream;
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


// MAPLOADER

MapLoader::MapLoader() : fileName(""){}

MapLoader::MapLoader(string fileName) : fileName(fileName) {}

vector<string> MapLoader::readLines() {
	ifstream input;
	input.open(fileName.c_str());

	if (!input) {
		cout << "File " << fileName << " is invalid" << endl;
		return vector<string>();
	}

	vector<string> lines;
	string line;
	while (getline(input, line)) {
		lines.push_back(line);
	}

	return lines;
}

void MapLoader::loadMap(vector<string> lines) {
	nodes = new vector<Node>;
	continents = new vector<Continent*>;

	error = lines.empty();
	if (!error) {
		int continentId = 0;
		int continentStart = -1;
		int territoryStart = -1;
		int borderStart = -1;

		for (int i = 0; i < lines.size(); i++)
		{
			if (lines[i].find("[continents]") != std::string::npos)
			{
				continentStart = (i + 1);
				break;
			}
		}

		// if [continents] does not exist, then the file is invalid
		if (continentStart == -1)
		{
			cout << "The file " << fileName << " is not a valid .map file." << endl;
			return;
		}
		
		for (int i = continentStart; i < lines.size(); i++)
		{
			continentId++;
			if (lines[i].find("[countries]") != std::string::npos)
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
			continents->push_back(new Continent(id, name, armyValue));
		}
		// if [territories] does not exist, then the file is invalid
		if (territoryStart == -1)
		{
			cout << "The file " << fileName << " is not a valid .map file. We cannot create a Parser object." << endl;
			return;
		}

		for (int i = territoryStart; i < lines.size(); i++)
		{
			if (lines[i].find("[borders]") != std::string::npos)
			{
				borderStart = (i + 1);
				break;
			}
			else if(lines[i].empty())
			{
				continue;
			}

			vector<string> lineData = split(lines[i], ' ');
			string continentName;
			vector<Continent*>::iterator iter;
			for( iter = continents->begin(); iter != continents->end(); ++iter){
				if((*iter)->getId() == stoi(lineData[2])){
					continentName = (*iter)->getName();
					// create territory nodes
					Node n = Node(Territory(stoi(lineData[0]), lineData[1], continentName, 0));
					nodes->push_back(n);
					// add territory to their continent
					(*iter)->addNode(&n);
				}
			}
		}

		// if [borders] does not exist, then the file is invalid
		if (borderStart == -1)
		{
			cout << "The file " << fileName << " is not a valid .map file. We cannot create a Parser object." << endl;
			return;
		}

		for (int i = borderStart; i < lines.size(); i++)
		{
			if(lines[i].empty())
			{
				break;
			}
			// add adjacent nodes to created nodes
			vector<string> lineData = split(lines[i], ' ');
			vector<Node>::iterator iter;
			for( iter = nodes->begin(); iter != nodes->end(); ++iter){
				if((iter)->getTerritory().getId() == stoi(lineData[0])){
					for(int i = 1; i < lineData.size(); i++){
						int territoryId = stoi(lineData[i]);
						Node element = nodes->at(territoryId - 1);
						(iter)->addNode(&element);
					}
				}
			}
		}

		// create game Map
		gameMap = new Map(nodes->size(), *nodes);
	}
}

Map* MapLoader::getMap() { return gameMap; }

vector<Continent*>* MapLoader::getContinents() { return continents; }

