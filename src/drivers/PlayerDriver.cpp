#include <iostream>

#include "Drivers.h"
#include "Player.h"

void PlayerDriver::demo(){
    Territory* t1 = new Territory(1, "Kenya", "Africa", 50);
    Territory* t2 = new Territory(2, "Somalia", "Africa", 10);
    Territory* t3 = new Territory(3, "South Africa", "Africa", 25);
    Territory* t4 = new Territory(4, "Netherlands", "Europe", 200);
    Territory* t5 = new Territory(5, "Belgium", "Europe", 125);
    Territory* t6 = new Territory(6, "England", "Europe", 75);

    vector<Territory*> territories;
    territories.push_back(t1); territories.push_back(t2); territories.push_back(t3); territories.push_back(t4); territories.push_back(t5); territories.push_back(t6);

    OrdersList* ordersList = new OrdersList();
    Hand* handOfCards = new Hand();

    // Creating new Player object
    Player* player = new Player("Isaac", territories, ordersList, handOfCards);

    // Player info output
    std::cout << *player << std::endl;

    // Player's toDefend() method which returns the first half of their territories
    vector<Territory*> toDefendResult = player->toDefend();

    std::cout << "\nResult of calling toDefend() on player: (first half of their territories)" << std::endl;
    for(auto* territory: toDefendResult)
    {
        std::cout<< *territory << std::endl;
    }

    // Player's toAttack() method which returns the first half of their territories
    vector<Territory*> toAttackResult = player->toAttack();

    std::cout << "\nResult of calling toAttack() on player: (second half of their territories)" << std::endl;
    for(auto* territory: toAttackResult)
    {
        std::cout<< *territory << std::endl;
    }

    // Player's issueOrder()
    player->issueOrder();

    std:cout << "Orders issued : " << std::endl;
    for(int i =0; i < player->getOrdersList()->size(); ++i){
        std::cout << *player->getOrdersList()->get(i) << endl;
    }

    // Player info output
    std::cout << "\nPlayer data after orders created: " << std::endl;
    std::cout << *player << std::endl;

    delete t1; delete t2; delete t3; delete t4; delete t5; delete t6;
}