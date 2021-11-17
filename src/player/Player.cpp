#include "Player.h"

// Default constructor
Player::Player() {
    //std::cout << "Player default constructor" << std::endl;

    this->name = "";
    this->territories = vector<Territory*>();
    this->ordersList = new OrdersList();
    this->handOfCards = new Hand();
    this->reinforcementPool = 0;
}

/**
 * Parameterized constructor
 *
 * Creates a deep copy of ordersList and handOfCards
 * Creates a shallow copy of territories as per prof's answer - they are unique and therefore the vector of territories is a shallow copy
 *
 * @param name
 * @param territories
 * @param ordersList
 * @param handOfCards
 */
Player::Player(string name, vector<Territory*> territories, OrdersList* ordersList, Hand* handOfCards){
    this->name = name;
    this->territories = territories;
    this->ordersList = new OrdersList(*ordersList);
    this->handOfCards = new Hand(*handOfCards);
    this->reinforcementPool = 0;
}

// Destructor
Player::~Player(){
    delete handOfCards; handOfCards = NULL;
    delete ordersList; ordersList = NULL;

    // territories are not deleted because they are unique and therefore the vector of territories is a shallow copy
    for (int i = 0; i < territories.size(); ++i) {
        territories[i] = NULL;
    }

    for(Player* p : playersBeingNegotiatedWith){ p = nullptr; }
}

/**
 * Copy constructor
 *
 * @param player
 */
Player::Player(const Player& player){
    this->name = player.name;
    this->territories = player.territories;
    this->ordersList = new OrdersList(*player.ordersList);
    this->handOfCards = new Hand(*player.handOfCards);
    this->playersBeingNegotiatedWith = player.playersBeingNegotiatedWith;
    this->reinforcementPool = player.reinforcementPool;
}

/**
 * Overloading the assignment operator
 *
 * @param player
 * @return
 */
Player& Player::operator=(const Player& player){
    if(&player != this) {
        delete ordersList;
        delete handOfCards;
        this->name = player.name;
        this->territories = player.territories;
        this->ordersList = new OrdersList(*player.ordersList);
        this->handOfCards = new Hand(*player.handOfCards);
        this->playersBeingNegotiatedWith = player.playersBeingNegotiatedWith;
    }
    return *this;
}

/**
 * Overloading stream insertion operator
 *
 * @param strm
 * @param player
 * @return
 */
std::ostream& operator<<(std::ostream &strm, const Player& player){
    strm << "\nPlayer Data:\n";

    strm << "Name : " << player.name << "\n\n";

    strm << "Territories: \n";
    for (int i = 0; i < player.territories.size(); ++i) {
        strm << i+1 << ". " << *player.territories[i] << "\n";
    }

    strm << "Orders List:\n";
    if(player.ordersList->size() == 0){
        strm << "Player " << player.name << "'s order list is empty.\n";
    }
    else {
        for (int i = 0; i < player.ordersList->size(); ++i) {
            strm << *player.ordersList->get(i) << "\n";
        }
    }
    /**
     * will need to change this once hand is a vector
     */
    strm << "\nCards \n";
    for (int i =0; i <player.handOfCards->size(); ++i){
        strm << player.handOfCards->getHand(i).toString() << "\n";
    }

    return strm;
}

// Returns the territories that the player controls
vector<Territory*> Player::toDefend(){
    return territories;
}

// Asked to return an arbitrary list of territories for this, so I just return the second half of the players territories
vector<Territory*> Player::toAttack() {
    vector<Territory*> attackableTerritories;
    for (Territory* territory : territories) {
        for (Territory* adjacentTerritory : territory->getAdjacentTerritories()) {
            if (std::find(territories.begin(), territories.end(), adjacentTerritory) == territories.end()) {
                if (std::find(attackableTerritories.begin(), attackableTerritories.end(), adjacentTerritory) == attackableTerritories.end()) {
                    attackableTerritories.push_back(adjacentTerritory);
                }
            }
        }
    }
    return attackableTerritories;
}


// Asks the user for input on which order to create, and creates the corresponding order objects and adds it to the player's ordersList
void Player::issueOrder() {
    int choiceDefend;
    int choiceAttack;
    int choiceCard;
    if (this->getTerritories().size() == 0) {
        std::cout << "This player no longer has countries and will be eliminated" << std::endl;
        return;
    }
    std::cout << this->getReinforcementPool() << "  " << this->getName() << std::endl;
    if (this->getReinforcementPool() > 0) {
        cout << "Player " << this->getName() << " still has has reinforcments and must deploy them" << std::endl;

        int numberOfDeployments;
        std::cout << "Enter how many troops(?) you want to deploy: ";
        while (true) {
            std::cin >> numberOfDeployments;
            if (!cin || numberOfDeployments < 0) {
                cout << "Enter a non-negative number: " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            else break;
        }

        std::cout << "Creating a deployment order" << std::endl;

        
        std::cout << "Player " << this->getName() << " has the following countries to reinforce: " << std::endl;
        for (Territory* territory : this->getTerritories()) {
            std::cout << territory->getName() << std::endl;
        }
        std::cout << "Choose by typing the index" << std::endl;
        std::cin >> choiceDefend;

        Deploy* deploy = new Deploy(numberOfDeployments, this, this->getTerritories()[choiceDefend]);
        ordersList->add(deploy);
        return;
    }

    int numberOfAdvancements;
    std::cout << "Enter how many troops(?) you want to advance: ";
    while (true) {
        std::cin >> numberOfAdvancements;
        if (!cin || numberOfAdvancements < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else break;
    }
    std::cout << "Player " << this->getName() << " has the following countries to attack: " << std::endl;
    for (Territory* territory : this->toAttack()) {
        std::cout << territory->getName() << std::endl;
    }
    std::cout << "Choose by typing the index" << std::endl;
    std::cin >> choiceAttack;

    std::cout << "Player " << this->getName() << " has the following countries to take an army from: " << std::endl;
    for (Territory* territory : this->getTerritories()) {
        std::cout << territory->getName() << std::endl;
    }
    std::cout << "Choose by typing the index" << std::endl;
    std::cin >> choiceDefend;

    std::cout << "Creating an advance order" << std::endl;
    Advance* advance = new Advance(this, numberOfAdvancements, this->getTerritories().at(choiceDefend), this->toAttack().at(choiceAttack));
    ordersList->add(advance);

    cout << "These are the cards in " << this->getName() << "'s hand:";
    for (int i = 0; i < 5; i++){
        cout << " " << this->handOfCards->getHand(i);
    }
    std::cout << std::endl;
    cout << "Choose a card based on its index or 9 for none ";
    cin >> choiceCard;
    if (choiceCard == 9) {
        std::cout << "No card played" << std::endl;
        return;
    }
    if (this->handOfCards->getHand(choiceCard).getCardType() == bomb) {
        std::cout << "Creating a bomb order" << std::endl;
        Bomb* bomb = new Bomb();
        ordersList->add(bomb);
    }
    if (this->handOfCards->getHand(choiceCard).getCardType() == blockade) {
        std::cout << "Creating a blockade order" << std::endl;
        Blockade* blockade = new Blockade();
        ordersList->add(blockade);
    }
    if (this->handOfCards->getHand(choiceCard).getCardType() == diplomacy) {
        std::cout << "Creating a diplomacy order" << std::endl;
        Negotiate* negotiate = new Negotiate();
        ordersList->add(negotiate);
    }
    if (this->handOfCards->getHand(choiceCard).getCardType() == airlift) {
        std::cout << "Creating a airlift order" << std::endl;
        Airlift* airlift = new Airlift();
        ordersList->add(airlift);
    }

}

/**
 * Setters and Getters
 */
void Player::addOrder(Order *order) { ordersList->add(order);}

void Player::addTerritory(Territory *territory) { territories.push_back(territory);}

void Player::removeTerritory(Territory* territory) {
    for(int i = 0; i < territories.size(); ++i){
        if(territory->getId() == territories[i]->getId()){
            territories.erase(territories.begin() + i);
        }
    }
}

vector<Territory *> Player::getTerritories() { return this->territories;}

OrdersList* Player::getOrdersList() { return this->ordersList;}

Hand* Player::getHandOfCards() { return this->handOfCards;}

void Player::setTerritories(vector<Territory *> territories) { this->territories = territories;}

void Player::setOrders(OrdersList* ordersList) { this->ordersList = new OrdersList(*ordersList);}

void Player::setReinforcementPool(int amount)
{
    this->reinforcementPool = amount;
}

void Player::addToReinforcementPool(int num) { this->reinforcementPool+=num;}

void Player::removeFromReinforcementPool(int num) {this->reinforcementPool-=num;}

int Player::getReinforcementPool() const {return reinforcementPool;}

void Player::setHandOfCards(Hand* handOfCards) { this->handOfCards = new Hand(*handOfCards);}

void Player::setName(string Name) { this->name = Name; }

string Player::getName()  { return this->name;}

int Player::getReinforcementPool() { return this->reinforcementPool; }
vector<Player *> Player::getPlayersBeingNegotiatedWith() const {return playersBeingNegotiatedWith; }

void Player::addToPlayersBeingNegotiatedWith(Player *player) {playersBeingNegotiatedWith.push_back(player);}

