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

/**
 * The order is executed if it is valid.
 **/
void Order::execute() {
    if (validate()) {
        onExecute();
        _executed = true;
    }
}

/**
 * Check if the order has been executed previously.
 * 
 * @return true if executed previously; false otherwise.
 **/
bool Order::isExecuted() const {
    return _executed;
}

/**
 * Checks if the order is valid.
 * 
 * @return true if not execute and valid; false otherwise.
 **/
bool Order::validate() const {
    return !_executed && onValidate();
}

string Order::stringToLog() {
    return "Observing Order::execute()";
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
Deploy::Deploy(int units) {
    _units = units;
}

Deploy::~Deploy() {
    // TODO: delete both territories.
}

Deploy& Deploy::operator=(Deploy&& order) {
    if (this != &order) {
        order._units = _units;
    }
    return *this;
}

Deploy::Deploy(const Deploy& deploy) {

}

/**
 * Gets a deep copy of the order itself.
 * 
 * @return deep copy of the order.
 **/
Order* Deploy::clone() {
    return new Deploy(*this);
}

/**
 * Gets the description of the order.
 * 
 * @return description of the order.
 **/
std::string Deploy::getDescription() const {
    return "Place units on your territories.";
}

/**
 * Gets the results of the order when it executed.
 * 
 * @return results of the order.
 **/
std::string Deploy::getEffectApplied() const {
    return "Placed " + std::to_string(_units) + " units on ";
}

/**
 * Additional actions taken for when the order gets executed.
 **/
void Deploy::onExecute() {
    std::cout << "Deploy the army of " << _units << " units!" << std::endl;
}

/**
 * Additional checks for validation of the order.
 * 
 * @return true if the additional validations pass; false otherwise.
 **/
bool Deploy::onValidate() const {
    // TODO: ensure territory is in player's team.
    return _units > 0;
}


// Advance class definition
Advance::Advance(int units) {
    _units = units;
}

Advance::~Advance() {
    // TODO: delete territory.
}

Advance& Advance::operator=(Advance&& order) {
    if (this != &order) {
        order._units = _units;
    }
    return *this;
}

Advance::Advance(const Advance& advance) {

}

/**
 * Gets a deep copy of the order itself.
 * 
 * @return deep copy of the order.
 **/
Order* Advance::clone() {
    return new Advance(*this);
}

/**
 * Gets the description of the order.
 * 
 * @return description of the order.
 **/
std::string Advance::getDescription() const {
    return "Move some of your units to another, adjacent territory.";
}

/**
 * Gets the results of the order when it executed.
 * 
 * @return results of the order.
 **/
std::string Advance::getEffectApplied() const {
    return "Moved " + std::to_string(_units) + " units to ";
}

/**
 * Additional actions taken for when the order gets executed.
 **/
void Advance::onExecute() {
    std::cout << "Advance, army!" << std::endl;
}

/**
 * Additional checks for validation of the order.
 * 
 * @return true if the additional validations pass; false otherwise.
 **/
bool Advance::onValidate() const {
    // TODO: make sure there are more units on the territory than, or equal to, advancing.
    return _units > 0;
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

/**
 * Gets a deep copy of the order itself.
 * 
 * @return deep copy of the order.
 **/
Order* Bomb::clone() {
    return new Bomb(*this);
}

/**
 * Gets the description of the order.
 * 
 * @return description of the order.
 **/
std::string Bomb::getDescription() const {
    return "Kill half of the army on an opponent's territory, adjacent to one of your territory.";
}

/**
 * Gets the results of the order when it executed.
 * 
 * @return results of the order.
 **/
std::string Bomb::getEffectApplied() const {
    return "Kill x units located on ";
}

/**
 * Additional actions taken for when the order gets executed.
 **/
void Bomb::onExecute() {
    std::cout << "Bomb yourselves!" << std::endl;
}

/**
 * Additional checks for validation of the order.
 * 
 * @return true if the additional validations pass; false otherwise.
 **/
bool Bomb::onValidate() const {
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

/**
 * Gets a deep copy of the order itself.
 * 
 * @return deep copy of the order.
 **/
Order* Blockade::clone() {
    return new Blockade(*this);
}

/**
 * Gets the description of the order.
 * 
 * @return description of the order.
 **/
std::string Blockade::getDescription() const {
    return "Triple the number of units on your territory and makes it neutral.";
}

/**
 * Gets the results of the order when it executed.
 * 
 * @return results of the order.
 **/
std::string Blockade::getEffectApplied() const {
    return "A blockade setup on ... of size ...";
}

/**
 * Additional actions taken for when the order gets executed.
 **/
void Blockade::onExecute() {
    std::cout << "Run for your life!" << std::endl;
}

/**
 * Additional checks for validation of the order.
 * 
 * @return true if the additional validations pass; false otherwise.
 **/
bool Blockade::onValidate() const {
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

/**
 * Gets a deep copy of the order itself.
 * 
 * @return deep copy of the order.
 **/
Order* Airlift::clone() {
    return new Airlift(*this);
}

/**
 * Gets the description of the order.
 * 
 * @return description of the order.
 **/
std::string Airlift::getDescription() const {
    return "Advance units from one territory to another, unoccupied territory or territory that you own.";
}

/**
 * Gets the results of the order when it executed.
 * 
 * @return results of the order.
 **/
std::string Airlift::getEffectApplied() const {
    return "Moving ... units from ... to ....";
}

/**
 * Additional actions taken for when the order gets executed.
 **/
void Airlift::onExecute() {
    std::cout << "We have liftoff." << std::endl;
}

/**
 * Additional checks for validation of the order.
 * 
 * @return true if the additional validations pass; false otherwise.
 **/
bool Airlift::onValidate() const {
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

/**
 * Gets a deep copy of the order itself.
 * 
 * @return deep copy of the order.
 **/
Order* Negotiate::clone() {
    return new Negotiate(*this);
}

/**
 * Gets the description of the order.
 * 
 * @return description of the order.
 **/
std::string Negotiate::getDescription() const {
    return "Peace for a single turn between you and another player.";
}

/**
 * Gets the results of the order when it executed.
 * 
 * @return results of the order.
 **/
std::string Negotiate::getEffectApplied() const {
    return "Attacks prevented with ...";
}

/**
 * Additional actions taken for when the order gets executed.
 **/
void Negotiate::onExecute() {
    std::cout << "Negotiate with the enemy's army!" << std::endl;
}

/**
 * Additional checks for validation of the order.
 * 
 * @return true if the additional validations pass; false otherwise.
 **/
bool Negotiate::onValidate() const {
    return true;
}