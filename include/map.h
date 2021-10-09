#pragma once

#include <string>
#include <vector>
#include "player.h"
#include <map>

using namespace std;

// Territory is a country in Risk game
class Territory
{
    private:
        int id;
        string name;
        string continent; 
        int numArmies;
        Player player;
    public:
        Territory();
        Territory(int id, string name, string continent, int numArmies);
        int getId();
        string getName();
        string getContinent();
        int getNumArmies();
        Player getPlayer();
        void setNumArmies(int numArmies);
        void setPlayer(Player player);
        bool operator==(Territory &rhs) const;
        bool operator==(Territory rhs) const;
        friend std::ostream &operator<<(std::ostream &stream, Territory territory);
        friend ostream &operator<<(std::ostream &stream, Territory &territory);
};

// Node contains a Territory and the list of nodes adjacent to it.
class Node
{
private:
    Territory territory;
    vector<Node*> adjList;
    bool visited;
public:
    Node();
    Node(Territory territory);
    Node(Territory territory, vector<Node *> adjList);
    Territory getTerritory();
    vector<Node*> getAdjList();
    Territory * getPointerToTerritory()const;
    void setAdjList(vector<Node*> adjList);
    void setVisited(bool visited);
    bool isVisited();
    void addNode(Node *node);
    friend ostream &operator<<(std::ostream &stream, Node &node);
    friend bool operator<(const Node &lhs, const Node &rhs);
};

class Continent
{
    private:
        int id;
        string name;
        int armyValue;
        vector<Node*> nodesInContinent;
    public:
        Continent();
        Continent(int id, string name, int armyValue);
        int getId();
        string getName();
        int getArmyValue();
        vector<Node*>* getNodesInContinent();
        void addNode(Node* node);
        friend ostream& operator <<(std::ostream& stream, Continent& continent);
};

// Map of Risk game
class Map
{
    private:
        int numVertices;
        vector<Node> vectorOfNodes;
        // Helper method
        void visitAdjacentNodes(vector<Node*> adjListNodes);
    public:
        Map();
        Map(int numVertices, vector<Node>& nodes);
        vector<Node*>* getVectorOfNodes();
        int getNumTerritories();
        void addNode(Node &node);
        void addEdge(Node *node1, Node *node2);
        bool areConnectedByEdge(Node* node1, Node* node2);
        bool validate();
        bool isMapConnected();
        friend ostream& operator <<(std::ostream& stream, Map& map);
};

class MapLoader
{
    private:
        string fileName;
        vector<Node>* nodes;
        Map* gameMap;
        vector<Continent*>* continents;
        // used to test continents are connected
        map<string, Map>* tempContinents;
        bool error;
    public:
        MapLoader();
        MapLoader(string fileName);
        vector<string> readLines();
        void loadMap(vector<string> lines);
        Map* getMap();
	    vector<Continent*>* getContinents();
};

// For split() function https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
template<typename Out>
void split(const std::string &s, char delim, Out result);
vector<string> split(const string &s, char delim);