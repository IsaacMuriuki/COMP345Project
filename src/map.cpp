#include <iostream>
#include "../include/map.h"

// ***TERRITORY***

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

// default constructor
Territory::Territory() : name(""), numArmies(0) {}

// partial parameterized constructor used for loading map files
Territory::Territory(string name) : name(name) {}

// parameterized constructor
Territory::Territory(string name, string continent, int numArmies) : name(name), continent(continent), numArmies(numArmies) {}

// ACCESSOR METHODS
string Territory::getName() { return name; }

string Territory::getContinent() { return continent; }

int Territory::getNumArmies() { return numArmies; }

// MUTATOR METHODS
void Territory::setNumArmies(int numArmies) { this->numArmies = numArmies; }


// ***NODE***

// default constructor for Node
Node::Node() : territory(), adjList(vector<Node *>()), visited(false) {}

// partial parameterized constructor
Node::Node(Territory territory) : territory(territory), adjList(vector<Node *>()), visited(false) {}

// parametrized constructor
Node::Node(Territory territory, vector<Node *> adjList) : territory(territory), adjList(adjList), visited(false) {}

// ACCESSOR METHODS
Territory Node::getTerritory() { return territory; }

vector<Node *> Node::getAdjList() { return adjList; }

Territory* Node::getPointerToTerritory() const { return const_cast<Territory*>(&territory); }

bool Node::isVisited() { return visited; }

// MUTATOR METHODS
void Node::setAdjList(vector<Node *> newAdjList) {
    if (!adjList.empty())
        adjList.clear();
    for (size_t i = 0; i < newAdjList.size(); i++) {
        adjList.push_back(newAdjList[i]);
    }
}

void Node::setVisited(bool visisted) { this->visited = visited; }

// method used to add a pointer to a node to the adjacency list of this node
void Node::addNode(Node *node)
{
	for (size_t i = 0; i < adjList.size(); i++)
	{
		// avoid duplicates
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
	stream << "Info of the node:\n" << node.territory;
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


// ***CONTINENT***

// default constructor
Continent::Continent(): name(""), extraTroops(0), nodesInContinent(vector<Node*>()) {}

// parameterized constructor
Continent::Continent(string name, int extraTroops): name(name), extraTroops(extraTroops), nodesInContinent(vector<Node*>()) {}

void Continent::addNode(Node* node)
{
	nodesInContinent.push_back(node);
}

std::ostream& operator << (std::ostream& stream, Continent& continent)
{
	stream << continent.getName() << ":\n";
	stream << "Extra troops: " << continent.getExtraTroops() << endl;
	stream << "Number of countries: " << continent.getNodesInContinent()->size() << endl;
	stream << "List of territories:\n";
	for (size_t i = 0; i < continent.getNodesInContinent()->size(); i++) {
		stream << "\t" << (*continent.getNodesInContinent())[i]->getTerritory().getName() << endl;
	}
	stream << endl;
	return stream;
}

// ACCESSOR METHODS
string Continent::getName() { return name; }

int Continent::getExtraTroops() { return extraTroops; }

vector<Node*>* Continent::getNodesInContinent() { return &nodesInContinent; }


// ***MAP***

// default constructor
Map::Map() : numVertices(0) { }

// parameterized constructor
Map::Map(int numVertices, vector<Node>& nodes) : numVertices(numVertices)
{
	// if num vertices not equal to the number of nodes being added,
	// something went wrong and so the the vectorOfNodes object will not be set.
	try {
		if (numVertices != nodes.size())
			throw new std::exception;
		vectorOfNodes = nodes;
	}
	catch (const std::exception& e) {
		cout << "The number of nodes in the node vector is not as expected." << endl;
	}
}

void Map::addNode(Node& node)
{
	vectorOfNodes.push_back(node);
	numVertices = vectorOfNodes.size();
}

// add edge between two nodes in the map
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

// ACCESSOR METHODS
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

// returns false if visitAdjacentNodes() fails to visit all nodes, meanings it's not connected.
// used for validating a map
bool Map::isMapConnected()
{
	bool graphIsConnected = true;
    if(vectorOfNodes.empty())
        return false;
    vector<Node *> initialAdjListNode = vectorOfNodes[0].getAdjList();

    if (initialAdjListNode.empty())
        return false;

	visitAdjacentNodes(initialAdjListNode);

    for (size_t i = 0; i < vectorOfNodes.size(); i++) {
        if (!vectorOfNodes[i].isVisited()) {
            graphIsConnected = false;
            break;
        }
    }
    // reinitialize visisted
    for (size_t i = 0; i < vectorOfNodes.size(); i++) {
        vectorOfNodes[i].setVisited(false);
    }
    return graphIsConnected;
}

//helper method used for dfs
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

bool Map::areConnectedByEdge(Node* node1, Node* node2) {
    for (int i = 0; i < node1->getAdjList().size(); i++) {
        if (node1->getAdjList()[i] == node2)
            return true;
    }
    return false;
}

std::ostream& operator << (std::ostream& stream, Map& map)
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
