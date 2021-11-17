#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <string>

#include "map.h"
#include "OrdersList.h"
#include "Cards.h"

class Territory;
class Order;
class OrdersList;

class Player{
public:
    // Constructors, destructor and copy constructor
    Player();
    Player(string, vector<Territory*> , OrdersList*, Hand* );
    Player(string, bool, vector<Territory*> , OrdersList*, Hand* );
    ~Player();
    Player(const Player& player);

    // Methods we were asked to create
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder();

    // Helper methods
    void addOrder(Order* );
    void addTerritory(Territory* );
    void removeTerritory(Territory*);
    vector<Territory*> getTerritories();
    OrdersList* getOrdersList();
    Hand* getHandOfCards();
    string getName();
    int getReinforcementPool();
    void setName(string Name);
    void setHandOfCards(Hand* );
    void setTerritories(vector<Territory*> );
    void setOrders(OrdersList* );
    void setReinforcementPool(int amount);
    void addToReinforcementPool(int);
    void removeFromReinforcementPool(int);
    int getReinforcementPool() const;
    vector<Player *> getPlayersBeingNegotiatedWith() const;
    void addToPlayersBeingNegotiatedWith(Player* player);

    // Overloading << and = operators
    friend std::ostream& operator<<(std::ostream &, const Player& );
    Player& operator=(const Player& player);
private:
    string name;
    vector<Territory*> territories;
    Hand* handOfCards;
    OrdersList* ordersList; 
    int reinforcementPool;
    vector<Player*> playersBeingNegotiatedWith;
    bool isNeutral;
};

