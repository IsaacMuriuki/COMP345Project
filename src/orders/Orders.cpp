#include "Orders.h"


// Order class definition
Order::Order() {
    _executed = false;
}

Order::~Order() {

}

Order& Order::operator=(Order&& order) {
    if (this != &order) {
        _executed = order._executed;
    }
    return *this;
}

Order::Order(const Order& order) : _executed(order._executed) {
}

void Order::execute() {
    if (validate()) {
        _executed = true;
    }
}

bool Order::isExecuted() const {
    return _executed;
}

std::ostream& operator<<(std::ostream &out, const Order& order) {
    out << order.getDescription() << (order.isExecuted() ? " - " + order.getEffectApplied() : "");
    return out;
}

// CardOrder class definition
CardOrder::CardOrder() {

}

CardOrder::~CardOrder() {

}

CardOrder& CardOrder::operator=(CardOrder&& order) {
    if (this != &order) {

    }
    return *this;
}

CardOrder::CardOrder(const CardOrder& order) {

}


// Deploy class definition
Deploy::Deploy(int units, Player* player, Territory* territory) {
    _units = units;
    this->player = player;
    this->territory = territory;
}

Deploy::~Deploy() {
    // TODO: delete both territories.
}

Deploy& Deploy::operator=(Deploy&& order) {
    if (this != &order) {
        order._units = _units;
    }
    order.player = player;
    order.territory = territory;
    return *this;
}

Deploy::Deploy(const Deploy& deploy) {

}

Order* Deploy::clone() {
    return new Deploy(*this);
}

std::string Deploy::getDescription() const {
    return "Place units on your territories.";
}

std::string Deploy::getEffectApplied() const {
    return "Placed " + std::to_string(_units) + " units on ";
}

void Deploy::execute() {
    // If the player owns the territory, add selected number of armies to the territory
    if(validate()){
        territory->setUnits(territory->getUnits() + _units);
        player->removeFromReinforcementPool(_units);

        std::cout << "Execute Deploy Order: " << _units << " moved from " << player->getName() << "'s reinforcement pool to "
                  << territory->getName() << " (units: " << territory->getUnits() << ")." << std::endl;
    }
}

void Deploy::onExecute() {
    std::cout << "Deploy the army of " << _units << " units!" << std::endl;
}

bool Deploy::validate() const {
    vector<Territory*> territories = player->toDefend();
    bool playerOwnsterritory = false;
    for (int i = 0; i < territories.size(); ++i) {
        if(territories[i]->getId() == territory->getId()){
            playerOwnsterritory = true;
            break;
        }
    }
    if (!playerOwnsterritory) std::cout << "Invalid deploy order ! Player " << player->getName() << " does not own the territory " << territory->getName() << std::endl;

    return _units > 0 && _units < player->getReinforcementPool() && playerOwnsterritory;
}

void Deploy::setUnitsToBeDeployed(int units) { this->_units = units; }


// Advance class definition
Advance::Advance(int units, Territory* fromTerritory, Territory* toTerritory) {
    _units = units;
    this->sourceTerritory = fromTerritory;
    this->targetTerritory = toTerritory;
}

Advance::~Advance() {
    // TODO: delete territory.
}

Advance& Advance::operator=(Advance&& order) {
    if (this != &order) {
        order._units = _units;
    }
    order.sourceTerritory = sourceTerritory;
    order.targetTerritory = targetTerritory;
    return *this;
}

Advance::Advance(const Advance& advance) {

}

Order* Advance::clone() {
    return new Advance(*this);
}

std::string Advance::getDescription() const {
    return "Move some of your units to another, adjacent territory.";
}

std::string Advance::getEffectApplied() const {
    return "Moved " + std::to_string(_units) + " units to ";
}

void Advance::onExecute() {
    if(validate()){
        // If the player owns both source and target territories
        if(targetTerritory->getOwner() == sourceTerritory->getOwner()){
            std::cout << "Advance order: The player " << player->getName() << " owns both territories, moving " << _units << " from " << sourceTerritory->getName() << " to " << targetTerritory->getName() << std::endl;
            sourceTerritory->setUnits(sourceTerritory->getUnits() - _units);
            targetTerritory->setUnits(targetTerritory->getUnits() + _units);
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

            // All of the defender's armies are eliminated - successful attack
            if(deadDefendingUnits == defendingUnitsCount){
                std::cout << "Advance order success: The target territory " << targetTerritory->getName() << " has been defeated and is now owned by Player " << player->getName() << ". Advancing "
                          << attackingUnitsCount-deadAttackingUnits << " from " << sourceTerritory->getName() << " to " << targetTerritory->getName() << std::endl;

                targetTerritory->setOwner(player);
                targetTerritory->setUnits(attackingUnitsCount-deadAttackingUnits);
                sourceTerritory->setUnits(sourceTerritory->getUnits() - _units);

                /**
                 * TODO: A player receives a card at the end of his turn if they successfully conquered at least one territory during their turn.
                 */
            }
                // Unsuccessful attack
            else{
                std::cout << "Advance order unsuccessful: Player " << player->getName() << " lost all attacking territories from " << sourceTerritory->getName()
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
    if(_units < 0){
        std::cout << "Invalid advance order ! Players cannot advance a negative number of units " << std::endl;
        return false;
    }

    // Ensure player cant advance more units than they have in the source territory
    if(_units > sourceTerritory->getUnits()){
        std::cout << "Invalid advance order ! Player " << player->getName() << " cannot advance " << _units << " from territory " << sourceTerritory->getName()
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

// Bomb class definition
Bomb::Bomb() {

}

Bomb::~Bomb() {

}

Bomb& Bomb::operator=(Bomb&& order) {
    if (this != &order) {

    }
    return *this;
}

Bomb::Bomb(const Bomb& bomb) {

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

bool Bomb::validate() const {
    return true;
}


// Blockade class definition
Blockade::Blockade() {

}

Blockade::~Blockade() {

}

Blockade& Blockade::operator=(Blockade&& order) {
    if (this != &order) {

    }
    return *this;
}

Blockade::Blockade(const Blockade& blockade) {

}

Order* Blockade::clone() {
    return new Blockade(*this);
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

bool Blockade::validate() const {
    return true;
}


// Airlift class definition
Airlift::Airlift() {

}

Airlift::~Airlift() {

}

Airlift& Airlift::operator=(Airlift&& order) {
    if (this != &order) {

    }
    return *this;
}

Airlift::Airlift(const Airlift& airlift) {

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

bool Airlift::validate() const {
    return true;
}


// Negotiate class definition
Negotiate::Negotiate() {

}

Negotiate::~Negotiate() {

}

Negotiate& Negotiate::operator=(Negotiate&& order) {
    if (this != &order) {

    }
    return *this;
}

Negotiate::Negotiate(const Negotiate& negotiate) {

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

bool Negotiate::validate() const {
    return true;
}