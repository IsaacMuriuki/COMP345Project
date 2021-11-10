#include "Orders.h"

// Order class definition
Order::Order() : executed(false){}

Order::Order(Player* player) : player(player), executed(false) {}

// Player set to null, not deleted
Order::~Order() {
    player = nullptr;
}

// Shallow copy of player
Order& Order::operator=(Order&& order) {
    if (this != &order) {
        executed = order.executed;
        player = order.player;
    }
    return *this;
}

// Shallow copy of player
Order::Order(const Order& order) : executed(order.executed), player(order.player) {}

bool Order::isExecuted() const {
    return executed;
}

std::ostream& operator<<(std::ostream &out, const Order& order) {
    out << order.getDescription() << (order.isExecuted() ? " - " + order.getEffectApplied() : "");
    return out;
}

/**
 * CardOrder class definition
 */
CardOrder::CardOrder() { }

CardOrder::CardOrder(Player * player) : Order(player) {}

CardOrder::~CardOrder() {
    player = nullptr;
}

CardOrder& CardOrder::operator=(CardOrder&& order) {
    if (this != &order) {
        player = order.player;
    }
    return *this;
}

CardOrder::CardOrder(const CardOrder& order) : Order(order){}


/**
 * Deploy class definition
 */
Deploy::Deploy() {}

Deploy::Deploy(int units, Player* player, Territory* territory) : Order(player), units(units), territory(territory)  {}

Deploy::~Deploy() {
    player = nullptr;
    territory = nullptr;
}

Deploy& Deploy::operator=(Deploy&& order) {
    if (this != &order) {
        order.units = units;
    }
    order.player = player;
    order.territory = territory;
    return *this;
}

Deploy::Deploy(const Deploy& deploy) : Order(deploy.player), units(deploy.units), territory(deploy.territory)  {

}

Order* Deploy::clone() {
    return new Deploy(*this);
}

std::string Deploy::getDescription() const {
    return "Place units on your territories.";
}

std::string Deploy::getEffectApplied() const {
    return "Placed " + std::to_string(units) + " units on ";
}

void Deploy::execute() {
    // If the player owns the territory, add selected number of armies to the territory
    if(validate()){
        territory->setUnits(territory->getUnits() + units);
        player->removeFromReinforcementPool(units);

        std::cout << "Execute Deploy Order: " << units << " moved from " << player->getName() << "'s reinforcement pool to "
                  << territory->getName() << " (units: " << territory->getUnits() << ")." << std::endl;
    }
}

void Deploy::onExecute() {
    std::cout << "Deploy the army of " << units << " units!" << std::endl;
}

/**
 * Checks if player owns territory
 */
bool Deploy::validate() const {
    vector<Territory*> territories = player->toDefend();
    bool playerOwnsTerritory = false;
    for (int i = 0; i < territories.size(); ++i) {
        if(territories[i]->getId() == territory->getId()){
            playerOwnsTerritory = true;
            break;
        }
    }
    if (!playerOwnsTerritory) std::cout << "Invalid deploy order ! Player " << player->getName() << " does not own the territory " << territory->getName() << std::endl;

    return units > 0 && units < player->getReinforcementPool() && playerOwnsTerritory;
}

void Deploy::setUnitsToBeDeployed(int units) { this->units = units; }


/**
 * Advance class definition
 */
Advance::Advance() {}

Advance::Advance(Player* player, int units, Territory* fromTerritory, Territory* toTerritory) : Order(player), units(units),
                                                                                                sourceTerritory(fromTerritory), targetTerritory(toTerritory){ }

Advance::~Advance() {
    player = nullptr;
    sourceTerritory = nullptr;
    targetTerritory = nullptr;
}

Advance& Advance::operator=(Advance&& order) {
    if (this != &order) {
        order.units = units;
        order.player = player;
        order.sourceTerritory = sourceTerritory;
        order.targetTerritory = targetTerritory;
    }

    return *this;
}

Advance::Advance(const Advance& advance) : Order(advance.player), units(advance.units),
                                           sourceTerritory(advance.sourceTerritory), targetTerritory(advance.targetTerritory){ }

Order* Advance::clone() {
    return new Advance(*this);
}

std::string Advance::getDescription() const {
    return "Move some of your units to another, adjacent territory.";
}

std::string Advance::getEffectApplied() const {
    return "Moved " + std::to_string(units) + " units to ";
}

void Advance::execute() {
    if(validate()){
        // If the player owns both source and target territories
        if(targetTerritory->getOwner() == sourceTerritory->getOwner()){
            std::cout << "Advance order: The player " << player->getName() << " owns both territories, moving " << units << " from " << sourceTerritory->getName() << " to " << targetTerritory->getName() << std::endl;
            sourceTerritory->setUnits(sourceTerritory->getUnits() - units);
            targetTerritory->setUnits(targetTerritory->getUnits() + units);
        }
            // Simulation of an attack
        else if(targetTerritory->getOwner() != player){
            int attackingUnitsProbability = rand() % 100;
            int defendingUnitsProbability = rand() % 100;
            const int defendingUnitsCount = targetTerritory->getUnits();
            const int attackingUnitsCount = sourceTerritory->getUnits();
            int deadAttackingUnits = 0;
            int deadDefendingUnits = 0;

            // Attack simulation
            for (int i = 0; i < attackingUnitsCount; ++i) {
                if(attackingUnitsProbability < 60){
                    deadDefendingUnits++;
                    if(deadDefendingUnits == defendingUnitsCount) break;
                }
            }

            // Defence simulation
            for (int i = 0; i < defendingUnitsCount; ++i) {
                if(defendingUnitsProbability < 70){
                    deadAttackingUnits++;
                    if(deadAttackingUnits == attackingUnitsCount) break;
                }
            }

            bool hasSuccessfullyAttacked = false;
            // All of the defender's armies are eliminated - successful attack
            if(deadDefendingUnits == defendingUnitsCount){
                std::cout << "Advance order success: The target territory " << targetTerritory->getName() << " has been defeated and is now owned by Player " << player->getName() << ". Advancing "
                          << attackingUnitsCount-deadAttackingUnits << " surviving attacking units from " << sourceTerritory->getName() << " to " << targetTerritory->getName() << std::endl;

                hasSuccessfullyAttacked = true;
                targetTerritory->setOwner(player);
                targetTerritory->setUnits(attackingUnitsCount-deadAttackingUnits);
                sourceTerritory->setUnits(sourceTerritory->getUnits() - units);

                /**
                 * TODO: A player receives a card at the end of his turn if they successfully conquered at least one territory during their turn.
                 */
                if(hasSuccessfullyAttacked){
                    // give card to player
                }
            }
                // Unsuccessful attack
            else{
                std::cout << "Advance order unsuccessful: Player " << player->getName() << " lost all attacking armies from " << sourceTerritory->getName()
                          << ", while " << defendingUnitsCount - deadDefendingUnits << " remain alive on the target territory " << targetTerritory->getName() << std::endl;
                sourceTerritory->setUnits(attackingUnitsCount - deadAttackingUnits);
                targetTerritory->setUnits(defendingUnitsCount - deadDefendingUnits);
            }
        }
    }
}

bool Advance::validate() const {
    // Ensure source territory belongs to the player
    if(sourceTerritory->getOwner() != player){
        std::cout << "Invalid advance order ! Player " << player->getName() << " does not own the source territory " << sourceTerritory->getName() << std::endl;
        return false;
    }

    // Check if the target is adjacent to the source territory
    vector<Territory*> adjacentTerritoriesToSource = sourceTerritory->getAdjacentTerritories();
    bool isAdjacentToSource = false;
    for (int i = 0; i < adjacentTerritoriesToSource.size(); ++i) {
        if(adjacentTerritoriesToSource[i]->getId() == sourceTerritory->getId()){
            isAdjacentToSource = true;
            break;
        }
    }
    if(!isAdjacentToSource){
        std::cout << "Invalid advance order ! Player " << player->getName() << "'s target territory " << targetTerritory->getName() << " is not adjacent to their source territory " << sourceTerritory->getName() << std::endl;
        return isAdjacentToSource;
    }

    // Ensure player cant advance a negative amount of units
    if(units < 0){
        std::cout << "Invalid advance order ! Players cannot advance a negative number of units " << std::endl;
        return false;
    }

    // Ensure player cant advance more units than they have in the source territory
    if(units > sourceTerritory->getUnits()){
        std::cout << "Invalid advance order ! Player " << player->getName() << " cannot advance " << units << " from territory " << sourceTerritory->getName()
                  << " which has " << sourceTerritory->getUnits() << " units." << std::endl;
        return false;
    }

    return true;
}

Territory *Advance::getSourceTerritory() const {
    return sourceTerritory;
}

void Advance::setSourceTerritory(Territory *fromTerritory) {
    Advance::sourceTerritory = fromTerritory;
}

Territory *Advance::getTargetTerritory() const {
    return targetTerritory;
}

void Advance::setTargetTerritory(Territory *toTerritory) {
    Advance::targetTerritory = toTerritory;
}

/**
 * Airlift class definition
 */

Airlift::Airlift() {}

Airlift::Airlift(Player* player, int units, Territory* sourceTerritory, Territory* targetTerritory) : CardOrder(player), units(units),
                                                                                                      sourceTerritory(sourceTerritory), targetTerritory(targetTerritory){}

Airlift::~Airlift() {
    player = nullptr;
    sourceTerritory = nullptr;
    targetTerritory = nullptr;
}

Airlift& Airlift::operator=(Airlift&& order) {
    if (this != &order) {
        order.units = units;
        order.player = player;
        order.sourceTerritory = sourceTerritory;
        order.targetTerritory = targetTerritory;
    }
    return *this;
}

Airlift::Airlift(const Airlift& airlift) : CardOrder(airlift.player), units(airlift.units),
                                           sourceTerritory(airlift.sourceTerritory), targetTerritory(airlift.targetTerritory){}



void Airlift::execute() {
    if (validate()) {
        // Player owns both territories
        if (sourceTerritory->getOwner() == player && targetTerritory->getOwner() == player) {
            std::cout << "Airlift order: Moving player " << player->getName() << "'s units (" << units << "), from " <<
                      sourceTerritory->getName() << " to " << targetTerritory->getName() << std::endl;

            sourceTerritory->setUnits(sourceTerritory->getUnits() - units);
            targetTerritory->setUnits(targetTerritory->getUnits() + units);
        }
    }
}

/**
* TODO: validate -> airlift can only be executed by a player playing a card
*/
bool Airlift::validate() const {
    // Player owns neither territory
    if(sourceTerritory->getOwner() != player || targetTerritory->getOwner() != player){
        std::cout << "Invalid Airlift order ! The player " << player->getName() << " does not own either the source or target territory" << std::endl;
        return false;
    }

    // Check if the player has enough units in source territory
    if(units > sourceTerritory->getUnits()){
        std::cout << "Invalid Airlift order ! The player " << player->getName() << " does have enough units in the territory " << sourceTerritory->getName() << "(Currently " <<
                  sourceTerritory->getUnits() << " units)" << std::endl;
        return false;
    }

    return true;
}

Order* Airlift::clone() {
    return new Airlift(*this);
}

std::string Airlift::getDescription() const {
    return "Advance units from one territory to another, unoccupied territory or territory that you own.";
}

std::string Airlift::getEffectApplied() const {
    return "Moving ... units from ... to ....";
}

void Airlift::onExecute() {
    std::cout << "We have liftoff." << std::endl;
}


// Bomb class definition
Bomb::Bomb() {

}

Bomb::Bomb(Player* player, Territory* targetTerritory) : CardOrder(player), targetTerritory(targetTerritory) {}

Bomb::~Bomb() {
    player = nullptr;
    targetTerritory = targetTerritory;
}

Bomb& Bomb::operator=(Bomb&& order) {
    if (this != &order) {
        player = order.player;
        targetTerritory = order.targetTerritory;
    }
    return *this;
}

Bomb::Bomb(const Bomb& bomb) : CardOrder(bomb.player), targetTerritory(bomb.targetTerritory) {}

void Bomb::execute() {
    if(validate()){
        targetTerritory->setUnits(targetTerritory->getUnits() / 2);
        std::cout << "Bomb order: Removing half the armies in target territory " << targetTerritory->getName() << std::endl;
    }
}

bool Bomb::validate() const {
    // Check if player owns target territory
    if(targetTerritory->getOwner() == player){
        std::cout << "Bomb order invalid ! Player " << player->getName() << " owns the target territory" << std::endl;
        return false;
    }

    vector<Territory*> adjacentTerritories;
    bool isAdjacent = false;
    // Check if target territory is adjacent to a territory owned by the player
    for(Territory* t: player->toDefend()){
        adjacentTerritories = t->getAdjacentTerritories();
        for(Territory* adjacent: adjacentTerritories){
            if(adjacent->getId() == targetTerritory->getId()) {
                isAdjacent = true;
                break;
            }
        }
        adjacentTerritories.clear();
    }

    if(!isAdjacent){
        std::cout << "Bomb order invalid ! The target territory is not adjacent to any of the territories owned by " << player->getName() << std::endl;
        return false;
    }

    return true;
}

Order* Bomb::clone() {
    return new Bomb(*this);
}

std::string Bomb::getDescription() const {
    return "Kill half of the army on an opponent's territory, adjacent to one of your territory.";
}

std::string Bomb::getEffectApplied() const {
    return "Kill x units located on ";
}

void Bomb::onExecute() {
    std::cout << "Bomb yourselves!" << std::endl;
}

/**
 * Blockade class definition
 */
Blockade::Blockade() {

}

Blockade::Blockade(Player *player, Territory *targetTerritory) : CardOrder(player), targetTerritory(targetTerritory){}


Blockade::~Blockade(){
    player = nullptr;
    targetTerritory = nullptr;
}

Blockade& Blockade::operator=(Blockade&& order) {
    if (this != &order) {
        player = order.player;
        targetTerritory = order.targetTerritory;
    }
    return *this;
}

Blockade::Blockade(const Blockade& blockade) : CardOrder(blockade.player), targetTerritory(blockade.targetTerritory){}

Order* Blockade::clone() {
    return new Blockade(*this);
}

/**
 * TODO: Create neutral player and transfer target territory owndership to them
 */
void Blockade::execute() {
    if(validate()){
        if(targetTerritory->getOwner() == player){
            std::cout << "Blockade order: Doubling the number of armies in " << targetTerritory->getName() << ", and transferring its ownership to the Neutral player (** NOT IMPLEMENTED **)." << std::endl;

            targetTerritory->setUnits(targetTerritory->getUnits() * 2);

//            if(/* neutral player does not exist */){
//                /* Create neutral player */
//            }
//            targetTerritory->setOwner(/* Created Neutral Player */);
        }
    }
}

bool Blockade::validate() const {
    // Check if target territory belongs to player
    if(targetTerritory->getOwner() != player){
        std::cout << "Blockade order invalid ! The player " << player->getName() << " does not own the target territory" << std::endl;
        return false;
    }
    return true;
}

std::string Blockade::getDescription() const {
    return "Triple the number of units on your territory and makes it neutral.";
}

std::string Blockade::getEffectApplied() const {
    return "A blockade setup on ... of size ...";
}

void Blockade::onExecute() {
    std::cout << "Run for your life!" << std::endl;
}


// Negotiate class definition
Negotiate::Negotiate() {}

Negotiate::Negotiate(Player* targetPlayer) : CardOrder(player), targetPlayer(targetPlayer) {}

Negotiate::~Negotiate() {
    player = nullptr;
    targetPlayer = nullptr;
}

Negotiate& Negotiate::operator=(Negotiate&& order) {
    if (this != &order) {
        player = order.player;
        targetPlayer = order.targetPlayer;
    }
    return *this;
}

Negotiate::Negotiate(const Negotiate& negotiate) : CardOrder(negotiate.player), targetPlayer(negotiate.targetPlayer) {}

/**
 * TODO: allow players to attack each other after the turn is over
 */
void Negotiate::execute() {
    if(validate()){

    }
}

bool Negotiate::validate() const {
    if(targetPlayer == player){
        std::cout << "Negotiate order invalid ! The target player is the player issuing the order" << std::endl;
        return false;
    }
    return true;
}

Order* Negotiate::clone() {
    return new Negotiate(*this);
}

std::string Negotiate::getDescription() const {
    return "Peace for a single turn between you and another player.";
}

std::string Negotiate::getEffectApplied() const {
    return "Attacks prevented with ...";
}

void Negotiate::onExecute() {
    std::cout << "Negotiate with the enemy's army!" << std::endl;
}