#include <Player.h>

// Default constructor
Player::Player() {
    this->name = "";
    this->territories = vector<Territory*>();
    this->ordersList = new OrdersList();
    this->handOfCards = new Hand();
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
}

// Destructor
Player::~Player(){
    delete handOfCards; handOfCards = NULL;
    delete ordersList; ordersList = NULL;

    // territories are not deleted because they are unique and therefore the vector of territories is a shallow copy
    for (int i = 0; i < territories.size(); ++i) {
        territories[i] = NULL;
    }
}

/**
 * Copy constructor
 *
 * @param player
 */
Player::Player(const Player& player){
    this->name = name;
    this->territories = territories;
    this->ordersList = new OrdersList(*ordersList);
    this->handOfCards = new Hand(*handOfCards);
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

    strm << "Player Data:\n";
    strm << "Name :" << player.name << "\n";
    strm << "Territories \n";
    for (int i = 0; i < player.territories.size(); ++i) {
        strm << *player.territories[i];
    }
    strm << "Orders \n";
    for (int i = 0; i < player.ordersList->size(); ++i) {
        strm << player.ordersList->get(i);
    }
    /**
     * will need to change this once hand is a vector
     */
    strm << "Cards \n";
    for (int i =0; i <sizeof(player.handOfCards->hand)/sizeof (player.handOfCards->hand[0]); ++i){
        strm << player.handOfCards->hand[i].getCardType() << "\n";
    }

    return strm;
}

// Asked to return an arbitrary list of territories for this, so I just return all the players territories
vector<Territory*> Player::toDefend(){ return territories;}

// Asked to return an arbitrary list of territories for this, so I just return all the players territories
vector<Territory*> Player::toAttack(){ return territories;}


// Asks the user for input on which order to create, and creates the corresponding order objects and adds it to the player's ordersList
void Player::issueOrder() {
    string orders = "List of possible orders to be made: \n 1. Deploy\n 2. Advance\n 3. Bomb\n 4. Blockade\n 5. Airlift\n ^6. Negotiate\n Enter the number of the order you want to execute: ";
    int orderNumber;

    // Asking player for which order and validates choice
    while (true)
    {
        std::cin >> orderNumber;
        if (!std::cin || orderNumber < 1 || orderNumber > 6)
        {
            std::cout << "Wrong Choice. Enter again " << endl;
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else break;
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

            Advance *advance = new Advance(numberOfAdvancements);
            ordersList->add(advance);
            break;
        }
        case 3: {
            Bomb *bomb = new Bomb();
            ordersList->add(bomb);
            break;
        }
        case 4: {
            Blockade* blockade = new Blockade();
            ordersList->add(blockade);
            break;
        }
        case 5: {
            Airlift* airlift = new Airlift();
            ordersList->add(airlift);
            break;
        }
        case 6: {
            Negotiate* negotiate = new Negotiate();
            ordersList->add(negotiate);
            break;
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

void Player::setHandOfCards(Hand* handOfCards) { this->handOfCards = new Hand(*handOfCards);}

string Player::getName()  { return this->name;}


