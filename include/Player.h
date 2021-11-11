#ifndef COMP_345_PROJECT_PLAYER_H
#define COMP_345_PROJECT_PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <string>

#include "map.h"
#include "Cards.h"
#include "OrdersList.h"

class Territory;

class Player{
public:
    // Constructors, destructor and copy constructor
    Player();
    Player(string, vector<Territory*> , OrdersList*, Hand* );
    ~Player();
    Player(const Player& player);

    // Methods we were asked to create
    vector<Territory*> toDefend();
    vector<Territory*> toAttack();
    void issueOrder();

    // Helper methods
    void addOrder(Order* );
    void addTerritory(Territory* );
    vector<Territory*> getTerritories();
    OrdersList* getOrdersList();
    Hand* getHandOfCards();
    string getName();
    void setHandOfCards(Hand* );
    void setTerritories(vector<Territory*> );
    void setOrders(OrdersList* );
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
};

#endif //COMP_345_PROJECT_PLAYER_H
