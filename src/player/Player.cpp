#include <Player.h>

Player::Player() {
    this->name = "";
    this->territories = vector<Territory*>();
    this->ordersList = new OrdersList();
    this->handOfCards = new Hand();
}

Player::Player(string name, vector<Territory*> territories, OrdersList* ordersList, Hand* handOfCards){
    this->name = name;

    /**
    * will change this once copy constructor for territories is created
    */
    for (int i = 0; i < territories.size(); ++i) {
        this->territories[i] = new Territory(territories[i]->getName(), territories[i]->getContinent(), territories[i]->getNumArmies());
    }

    this->ordersList = new OrdersList(*ordersList);
    this->handOfCards = new Hand(*handOfCards);
}

Player::~Player(){
    delete handOfCards; handOfCards = NULL;
    delete ordersList; ordersList = NULL;
    for (int i = 0; i < territories.size(); ++i) {
        delete territories[i];
        territories[i] = NULL;
    }
}

Player::Player(const Player& player){
    this->name = name;

    /**
     * will change this once copy constructor for territories is created
     */
    for (int i = 0; i < territories.size(); ++i) {
        this->territories[i] = new Territory(player.territories[i]->getName(), player.territories[i]->getContinent(), player.territories[i]->getNumArmies());
    }

    this->ordersList = new OrdersList(*ordersList);
    this->handOfCards = new Hand(*handOfCards);
}

vector<Territory*> Player::toDefend(){
    return territories;
}

vector<Territory*> Player::toAttack(){
    return territories;
}

void Player::issueOrder(){

}

std::ostream& Player::operator<<(std::ostream &out){

}

Player& Player::operator=(const Player player){

}

void Player::addOrder(Order *order) {
    ordersList->add(order);
}

void Player::addTerritory(Territory *territory) {
    territories.push_back(territory);
}

vector<Territory *> Player::getTerritories() {
    return vector<Territory *>();
}

OrdersList* Player::getOrdersList() {
    return ordersList;
}

Hand* Player::getHandOfCards() {
    return handOfCards;
}

void Player::setTerritories(vector<Territory *> territories) {

}

void Player::setOrders(vector<Order *> territories) {

}

void Player::setHandOfCards(Hand * handOfCards) {

}

