#include <Player.h>

// Default constructor
Player::Player() {
    //std::cout << "Player default constructor" << std::endl;

    this->name = "";
    this->territories = vector<Territory*>();
    this->ordersList = new OrdersList();
    this->handOfCards = new Hand();
    this-> reinforcementPool = 0;
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
}

/**
 * Overloading the assignment operator
 *
 * @param player
 * @return
 */
Player& Player::operator=(const Player& player){
    this->name = player.name;
    this->territories = player.territories;
    this->ordersList = new OrdersList(*player.ordersList);
    this->handOfCards = new Hand(*player.handOfCards);
    this->playersBeingNegotiatedWith = player.playersBeingNegotiatedWith;

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

// Asked to return an arbitrary list of territories for this, so I just return the first half of the players territories
vector<Territory*> Player::toDefend(){
    vector<Territory*> firstHalf;
    int half = territories.size()/2;

    for (int i = 0; i < half; ++i) {
        firstHalf.push_back(territories[i]);
    }
    return firstHalf;
}

// Asked to return an arbitrary list of territories for this, so I just return the second half of the players territories
vector<Territory*> Player::toAttack(){
    vector<Territory*> secondHalf;
    int half = territories.size()/2;

    for (int i = half; i < territories.size(); ++i) {
        secondHalf.push_back(territories[i]);
    }
    return secondHalf;
}


// Asks the user for input on which order to create, and creates the corresponding order objects and adds it to the player's ordersList
void Player::issueOrder() {
    string orders = "List of possible orders to be made: \n 1. Deploy\n 2. Advance\n 3. Bomb\n 4. Blockade\n 5. Airlift\n 6. Negotiate\n 7. Stop issuing orders\n ";
    int orderNumber = 0;

    while(orderNumber != 7) {
        std::cout << orders << std::endl;
        std::cout << "Enter the number of the next order you want to execute:" << std::endl;
        // Asking player for which order and validates choice
        while (true) {
            std::cin >> orderNumber;
            if (!std::cin || orderNumber < 1 || orderNumber > 7) {
                std::cout << "Wrong Choice. Enter again " << endl;
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else break;
        }

        switch (orderNumber) {
            case 1: {
                int numberOfDeployments;
                std::cout << "Enter how many troops(?) you want to deploy: ";
                while (true) {
                    std::cin >> numberOfDeployments;
                    if (!cin || numberOfDeployments < 0) {
                        cout << "Enter a non-negative number: " << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    } else break;
                }

                std::cout << "Creating a deployment order" << std::endl;
                Deploy *deploy = new Deploy(numberOfDeployments);
                ordersList->add(deploy);
                break;
            }
            case 2: {
                int numberOfAdvancements;
                std::cout << "Enter how many troops(?) you want to advance: ";
                while (true) {
                    std::cin >> numberOfAdvancements;
                    if (!cin || numberOfAdvancements < 0) {
                        cout << "Enter a non-negative number: " << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    } else break;
                }

                std::cout << "Creating an advance order" << std::endl;
                Advance *advance = new Advance(numberOfAdvancements);
                ordersList->add(advance);
                break;
            }
            case 3: {
                std::cout << "Creating a bomb order" << std::endl;
                Bomb *bomb = new Bomb();
                ordersList->add(bomb);
                break;
            }
            case 4: {
                std::cout << "Creating a blockade order" << std::endl;
                Blockade *blockade = new Blockade();
                ordersList->add(blockade);
                break;
            }
            case 5: {
                std::cout << "Creating an airlift order" << std::endl;
                Airlift *airlift = new Airlift();
                ordersList->add(airlift);
                break;
            }
            case 6: {
                std::cout << "Creating a negotiate order" << std::endl;
                Negotiate *negotiate = new Negotiate();
                ordersList->add(negotiate);
                break;
            }
            case 7: {
                std::cout << "Done Creating Orders\n" << std::endl;
                break;
            }
        }
    }
}

/**
 * Setters and Getters
 */
void Player::addOrder(Order *order) { ordersList->add(order);}

void Player::addTerritory(Territory *territory) { territories.push_back(territory);}

vector<Territory *> Player::getTerritories() { return this->territories;}

OrdersList* Player::getOrdersList() { return this->ordersList;}

Hand* Player::getHandOfCards() { return this->handOfCards;}

void Player::setTerritories(vector<Territory *> territories) { this->territories = territories;}

void Player::setOrders(OrdersList* ordersList) { this->ordersList = new OrdersList(*ordersList);}

void Player::addToReinforcementPool(int num) { this->reinforcementPool+=num;}

void Player::removeFromReinforcementPool(int num) {this->reinforcementPool-=num;}

int Player::getReinforcementPool() const {return reinforcementPool;}

void Player::setHandOfCards(Hand* handOfCards) { this->handOfCards = new Hand(*handOfCards);}

string Player::getName()  { return this->name;}

vector<Player *> Player::getPlayersBeingNegotiatedWith() const {return playersBeingNegotiatedWith; }

void Player::addToPlayersBeingNegotiatedWith(Player *player) {playersBeingNegotiatedWith.push_back(player);}

