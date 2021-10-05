#include <string>
#include <vector>

using namespace std;

// Territory is a country in Risk game
class Territory
{
    private:
        string name;
        string continent; 
        int numArmies;
    public:
        Territory();
        Territory(string name);
        Territory(string name, string continent, int numArmies);
        bool operator==(Territory &rhs) const;
        bool operator==(Territory rhs) const;
        friend std::ostream &operator<<(std::ostream &stream, Territory territory);
        // friend std::ostream &operator<<(std::ostream &stream, Territory &territory);
        string getName();
        string getContinent();
        int getNumArmies();
        void setNumArmies(int numArmies);
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
    bool isVisited();
    void setAdjList(vector<Node*> adjList);
    void setVisited(bool visited);
    void addNode(Node *node);
    friend std::ostream &operator<<(std::ostream &stream, Node &node);
    friend bool operator<(const Node &lhs, const Node &rhs);
};

class Continent
{
    private:
        string name;
        int extraTroops;
        vector<Node*> nodesInContinent;
    public:
        Continent();
        Continent(string name, int extraTroops);
        string getName();
        int getExtraTroops();
        vector<Node*>* getNodesInContinent();
        void addNode(Node* node);
        friend std::ostream& operator <<(std::ostream& stream, Continent& continent);
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
        // Constructors
        Map();
        Map(int vertices, vector<Node>& arrayOfNodes);
        // Accessor methods (no mutator methods since the Map will not change after the initial creation
        vector<Node*>* getVectorOfNodes();
        int getNumTerritories();
        // Methods to add
        void addNode(Node &node);
        void addEdge(Node *node1, Node *node2);
        bool areConnectedByEdge(Node* node1, Node* node2);
        // bool areConnectedThroughOwned(int source, int destination);
        bool isMapConnected();
        friend std::ostream& operator <<(std::ostream& stream, Map& map);
};