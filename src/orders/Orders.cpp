#include "Orders.h"

// Order class definition
int Order::ID = 0;

Order::Order() : executed(false){
    ID++;
}

Order::Order(Player* player) : player(player), executed(false){
    ID++;
}

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

int Order::getOrderID() {return this->orderID;}

bool Order::isExecuted() const {
    return executed;
}

/**
 * Returns an entry of the effect of the order executed to be logged.
 * 
 * @return entry as a string.
 * */
string Order::stringToLog(){
    return "Order Executed: " + this->getEffectApplied();
}

std::ostream& operator<<(std::ostream &out, const Order& order) {
    out << order.getDescription() << (order.isExecuted() ? " - " + order.getEffectApplied() : "");
    return out;
}

/**
 * Deploy class definition
 */
Deploy::Deploy() {this->orderID = ID;}

Deploy::Deploy(int units, Player* player, Territory* territory) : Order(player), units(units), territory(territory)  {this->orderID = ID;}

Deploy::~Deploy() {
    player = nullptr;
    territory = nullptr;
}

Deploy& Deploy::operator=(Deploy&& order) {
    if (this != &order) {
        order.units = units;
        order.player = player;
        order.territory = territory;
    }
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
    return effectsApplied;
}

std::string Deploy::getType() {
    return "Deploy";
}

void Deploy::execute() {
    // If the player owns the territory, add selected number of armies to the territory
    if(validate()){
        stringstream ss;
        territory->setUnits(territory->getUnits() + units);
        player->removeFromReinforcementPool(units);

        ss << "Execute Deploy Order: " << units << " units moved from " << player->getName() << "'s reinforcement pool to "
                  << territory->getName() << " (units: " << to_string(territory->getUnits()) << ").";
        std::cout << ss.str() << std::endl;
        effectsApplied = ss.str();

        // Notifies observer of the effect of the order executed.
        Notify(this);
    }
    if(!player->getOrdersList()->remove(this)){
        std::cout << "Could not remove order from " << player->getName() << "'s order list." << std::endl;
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
    if (!playerOwnsTerritory) {
        std::cout << "Invalid deploy order ! Player " << player->getName() << " does not own the territory " << territory->getName() << std::endl;
        return false;
    }
    if(units > player->getReinforcementPool()) {
        std::cout << "Invalid deploy order ! Player " << player->getName()
                  << " does not have enough reinforcements to deploy " << std::endl;
        return false;
    }
    if(units < 0){
        std::cout << "Invalid deploy order ! Player " << player->getName()
                  << " cannot deploy negative units " << std::endl;
        return false;
    }
    return true;
}

void Deploy::setUnitsToBeDeployed(int units) { this->units = units; }


/**
 * Advance class definition
 */
Advance::Advance() {this->orderID = ID;}

Advance::Advance(Player* player, int units, Territory* fromTerritory, Territory* toTerritory) : Order(player), units(units),
                                                                                                sourceTerritory(fromTerritory), targetTerritory(toTerritory){
    this->orderID = ID;
}

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
    return effectsApplied;
}

std::string Advance::getType() {
    return "Advance";
}

void Advance::execute() {
    if(validate()){
        stringstream ss;

        // If the player owns both source and target territories
        if(targetTerritory->getOwner() == sourceTerritory->getOwner()){
            ss << "Advance order: The player " << player->getName() << " owns both territories, moving " << units << " from " << sourceTerritory->getName() << " to " << targetTerritory->getName();
            std::cout << ss.str() << std::endl;
            effectsApplied = ss.str();
            sourceTerritory->setUnits(sourceTerritory->getUnits() - units);
            targetTerritory->setUnits(targetTerritory->getUnits() + units);
        }
            // Simulation of an attack
        else if(targetTerritory->getOwner() != player){
            int attackingUnitsProbability;
            int defendingUnitsProbability;
            const int defendingUnitsCount = targetTerritory->getUnits();
            const int attackingUnitsCount = sourceTerritory->getUnits();
            int deadAttackingUnits = 0;
            int deadDefendingUnits = 0;

            // Attack simulation
            for (int i = 0; i < attackingUnitsCount; ++i) {
                attackingUnitsProbability = rand() % 100;
                if(attackingUnitsProbability < 60){
                    deadDefendingUnits++;
                    if(deadDefendingUnits == defendingUnitsCount) break;
                }
            }

            // Defence simulation
            for (int i = 0; i < defendingUnitsCount; ++i) {
                defendingUnitsProbability = rand() % 100;
                if(defendingUnitsProbability < 70){
                    deadAttackingUnits++;
                    if(deadAttackingUnits == attackingUnitsCount) break;
                }
            }

            bool hasSuccessfullyAttacked = false;
            // All of the defender's armies are eliminated - successful attack
            if(deadDefendingUnits == defendingUnitsCount){
                ss << "Advance order success: The target territory " << targetTerritory->getName() << " has been defeated and is now owned by Player " << player->getName() << ". Advancing "
                          << attackingUnitsCount-deadAttackingUnits << " surviving attacking units from " << sourceTerritory->getName() << " to " << targetTerritory->getName();
                std::cout << ss.str() << std::endl;
                effectsApplied = ss.str();

                hasSuccessfullyAttacked = true;
                player->addTerritory(targetTerritory);
                targetTerritory->getOwner()->removeTerritory(targetTerritory);
                targetTerritory->setOwner(player);
                targetTerritory->setUnits(attackingUnitsCount-deadAttackingUnits);
                sourceTerritory->setUnits(sourceTerritory->getUnits() - units);

                /**
                 * TODO: A player receives a card at the end of his turn if they successfully conquered at least one territory during their turn.
                 * - might need to add a reference to the Deck in the players Hand, in order to be able to draw() a card
                 */
                if(hasSuccessfullyAttacked){
                    // give card to player
                    CardType card = player->getHandOfCards()->getDeck()->draw();
                    player->getHandOfCards()->addCardToHand(card);
                }
            }
            // Unsuccessful attack
            else{
                ss << "Advance order unsuccessful: Player " << player->getName() << " lost all attacking armies from " << sourceTerritory->getName()
                          << ", while " << defendingUnitsCount - deadDefendingUnits << " remain alive on the target territory " << targetTerritory->getName();
                std::cout << ss.str() << std::endl;
                effectsApplied = ss.str();   
                sourceTerritory->setUnits(attackingUnitsCount - deadAttackingUnits);
                targetTerritory->setUnits(defendingUnitsCount - deadDefendingUnits);
            }
        }

        // Notifies observer of the effect of the order executed.
        Notify(this);
    }
    if(!player->getOrdersList()->remove(this)){
        std::cout << "Could not remove order from " << player->getName() << "'s order list." << std::endl;
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
        if(adjacentTerritoriesToSource[i]->getId() == targetTerritory->getId()){
            isAdjacentToSource = true;
            break;
        }
    }
    if(!isAdjacentToSource){
        std::cout << "Invalid advance order ! Player " << player->getName() << "'s target territory " << targetTerritory->getName() << " is not adjacent to their source territory " << sourceTerritory->getName() << std::endl;
        return isAdjacentToSource;
    }

    /**
     * Check if:
     * 1. the target territory is owned by another player
     * 2. the players are negotiating as a result of the negotiate order by playing the diplomacy card
     */
     if(targetTerritory->getOwner() != player) {
         if(!player->getPlayersBeingNegotiatedWith().empty()) {
             vector<Player *> playersNegotiatingWith = player->getPlayersBeingNegotiatedWith();
             bool isNegotiatingWithTarget = false;
             Player* targetPlayer = targetTerritory->getOwner();

             for(Player* p : playersNegotiatingWith){
                 if(p == targetPlayer){
                     isNegotiatingWithTarget = true;
                     break;
                 }
             }

             if(isNegotiatingWithTarget){
                 std::cout << "Invalid advance order ! Attack on " << targetTerritory->getName() << " prevented because the owning players are currently negotiating" << std::endl;
                 return false;
             }
         }
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

void Advance::onExecute() {}

/**
 * Airlift class definition
 */

Airlift::Airlift() {this->orderID = ID;}

Airlift::Airlift(Player* player, int units, Territory* sourceTerritory, Territory* targetTerritory) : Order(player), units(units),
                                                                                                      sourceTerritory(sourceTerritory), targetTerritory(targetTerritory){
    this->orderID = ID;
}

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

Airlift::Airlift(const Airlift& airlift) : Order(airlift.player), units(airlift.units),
                                           sourceTerritory(airlift.sourceTerritory), targetTerritory(airlift.targetTerritory){}



void Airlift::execute() {
    if (validate()) {
        stringstream ss;

        // Player owns both territories
        if (sourceTerritory->getOwner() == player && targetTerritory->getOwner() == player) {
            ss << "Airlift order: Moving player " << player->getName() << "'s units (" << units << "), from " <<
                      sourceTerritory->getName() << " to " << targetTerritory->getName();
            std::cout << ss.str() << std::endl;
            effectsApplied = ss.str();

            sourceTerritory->setUnits(sourceTerritory->getUnits() - units);
            targetTerritory->setUnits(targetTerritory->getUnits() + units);
        }

        // Notifies observer of the effect of the order executed.
        Notify(this);
    }
    if(!player->getOrdersList()->remove(this)){
        std::cout << "Could not remove order from " << player->getName() << "'s order list." << std::endl;
    }
}

/**
* TODO: validate -> airlift can only be executed by a player playing a card (prob to be done in issueOrder() )
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
    return effectsApplied;
}

std::string Airlift::getType() {
    return "Airlift";
}

void Airlift::onExecute() {
    std::cout << "We have liftoff." << std::endl;
}


// Bomb class definition
Bomb::Bomb() {
    this->orderID = ID;
}

Bomb::Bomb(Player* player, Territory* targetTerritory) : Order(player), targetTerritory(targetTerritory) {this->orderID = ID;}

Bomb::~Bomb() {
    player = nullptr;
    targetTerritory = nullptr;
}

Bomb& Bomb::operator=(Bomb&& order) {
    if (this != &order) {
        player = order.player;
        targetTerritory = order.targetTerritory;
    }
    return *this;
}

Bomb::Bomb(const Bomb& bomb) : Order(bomb.player), targetTerritory(bomb.targetTerritory) {}

void Bomb::execute() {
    if(validate()){
        stringstream ss;
        targetTerritory->setUnits(targetTerritory->getUnits() / 2);
        ss << "Bomb order: Removing half the armies in target territory " << targetTerritory->getName();
        std::cout << ss.str() << std::endl;
        effectsApplied = ss.str();

        // Notifies observer of the effect of the order executed.
        Notify(this);
    }
    if(!player->getOrdersList()->remove(this)){
        std::cout << "Could not remove order from " << player->getName() << "'s order list." << std::endl;
    }
}

/**
* TODO: validate -> bomb can only be executed by a player playing a card (prob to be done in issueOrder() )
*/
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

    if(isAdjacent){
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
    return effectsApplied;
}

std::string Bomb::getType() {
    return "Bomb";
}

void Bomb::onExecute() {
    std::cout << "Bomb yourselves!" << std::endl;
}

/**
 * Blockade class definition
 */
Blockade::Blockade() {
    this->orderID = ID;
}

Blockade::Blockade(Player *player, Player* neutralPlayer, Territory *targetTerritory) : Order(player), neutralPlayer(neutralPlayer), targetTerritory(targetTerritory){this->orderID = ID;}


Blockade::~Blockade(){
    player = nullptr;
    targetTerritory = nullptr;
    neutralPlayer = nullptr;
}

Blockade& Blockade::operator=(Blockade&& order) {
    if (this != &order) {
        player = order.player;
        targetTerritory = order.targetTerritory;
        neutralPlayer = order.neutralPlayer;
    }
    return *this;
}

Blockade::Blockade(const Blockade& blockade) : Order(blockade.player), targetTerritory(blockade.targetTerritory){}

Order* Blockade::clone() {
    return new Blockade(*this);
}

/**
 * TODO: Create neutral player and transfer target territory ownership to them
 * - maybe always add a neutral player in the start of a game (should not be given territories like the others),
 * so just need to transfer ownership here
 */
void Blockade::execute() {
    if(validate()){
        if(targetTerritory->getOwner() == player){
            stringstream ss;
            ss << "Blockade order: Doubling the number of armies in " << targetTerritory->getName() << ", and transferring its ownership to the Neutral player.";
            std::cout << ss.str() << std::endl;
            effectsApplied = ss.str();
            targetTerritory->setUnits(targetTerritory->getUnits() * 2);

            // Transferring ownership of the territory to neutral player
            targetTerritory->getOwner()->removeTerritory(targetTerritory);
            targetTerritory->setOwner(neutralPlayer);
            neutralPlayer->addTerritory(targetTerritory);
        }

        // Notifies observer of the effect of the order executed.
        Notify(this);
    }
    if(!player->getOrdersList()->remove(this)){
        std::cout << "Could not remove order from " << player->getName() << "'s order list." << std::endl;
    }
}


/**
* TODO: validate -> blockade can only be executed by a player playing a card (prob to be done in issueOrder() )
*/
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
    return effectsApplied;
}

std::string Blockade::getType() {
    return "Blockade";
}

void Blockade::onExecute() {
    std::cout << "Run for your life!" << std::endl;
}


// Negotiate class definition
Negotiate::Negotiate() {}

Negotiate::Negotiate(Player* player, Player* targetPlayer) : Order(player), targetPlayer(targetPlayer) {}

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

Negotiate::Negotiate(const Negotiate& negotiate) : Order(negotiate.player), targetPlayer(negotiate.targetPlayer) {}

/**
 * TODO: allow players to attack each other after the turn is over
 */
void Negotiate::execute() {
    if(validate()){
        stringstream ss;
        targetPlayer->addToPlayersBeingNegotiatedWith(player);
        player->addToPlayersBeingNegotiatedWith(targetPlayer);
        ss << "Negotiate order executed ! " << player->getName() << " is now negotiating with " << targetPlayer->getName();
        std::cout << ss.str() << std::endl;
        effectsApplied = ss.str();

        // Notifies observer of the effect of the order executed.
        Notify(this);
    }
    if(!player->getOrdersList()->remove(this)){
        std::cout << "Could not remove order from " << player->getName() << "'s order list." << std::endl;
    }
}

/**
* TODO: validate -> negotiate can only be executed by a player playing a card (prob to be done in issueOrder() )
*/
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
    return effectsApplied;
}

std::string Negotiate::getType() {
    return "Negotiate";
}

void Negotiate::onExecute() {
    std::cout << "Negotiate with the enemy's army!" << std::endl;
}