#ifndef COMP_345_PROJECT_PLAYER_H
#define COMP_345_PROJECT_PLAYER_H

#include <iostream>
#include <string>
#include <vector>

#include "map.h"
#include "Cards.h"
#include "Orders.h"

class Player{
public:
    Player();
    Player(vector<Territory> territories);
    ~Player();
    Player(const Player& player);
    Vector<Territory> toDefend();
    Vector<Territory> toAttack();
    void issueOrder();
    friend std::ostream& operator<<(std::ostream &out);
    Player& operator=(const Player player);

private:
    vector<Territory*> territories;
    Hand* handOfCards;
    vector<Order*> orders;
};

#endif //COMP_345_PROJECT_PLAYER_H
