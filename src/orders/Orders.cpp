#include "Orders.h"


// Order class definition
Order::Order() {
    _executed = false;
}

Order::~Order() {

}

Order& Order::operator=(Order&& order) {
    if (this != &order) {
        
    }
    return *this;
}

Order::Order(const Order& order) {
    _executed = order._executed;
}

void Order::execute() {
    if (validate()) {
        onExecute();
        _executed = true;
    }
}

bool Order::isExecuted() const {
    return _executed;
}

bool Order::validate() const {
    return !_executed && onValidate();
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

std::string Deploy::getDescription() const {
    return "Place units on your territories.";
}

std::string Deploy::getEffectApplied() const {
    return "Placed " + std::to_string(_units) + " units on ";
}

void Deploy::onExecute() {
    std::cout << "Deploy the army of " << _units << " units!" << std::endl;
}

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

std::string Advance::getDescription() const {
    return "Move some of your units to another, adjacent territory.";
}

std::string Advance::getEffectApplied() const {
    return "Moved " + std::to_string(_units) + " units to ";
}

void Advance::onExecute() {
    std::cout << "Advance, army!" << std::endl;
}

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

std::string Bomb::getDescription() const {
    return "Kill half of the army on an opponent's territory, adjacent to one of your territory.";
}

std::string Bomb::getEffectApplied() const {
    return "Kill x units located on ";
}

void Bomb::onExecute() {
    std::cout << "Bomb yourselves!" << std::endl;
}

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

std::string Blockade::getDescription() const {
    return "Triple the number of units on your territory and makes it neutral.";
}

std::string Blockade::getEffectApplied() const {
    return "A blockade setup on ... of size ...";
}

void Blockade::onExecute() {
    std::cout << "Run for your life!" << std::endl;
}

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

std::string Airlift::getDescription() const {
    return "Advance units from one territory to another, unoccupied territory or territory that you own.";
}

std::string Airlift::getEffectApplied() const {
    return "Moving ... units from ... to ....";
}

void Airlift::onExecute() {
    std::cout << "We have liftoff." << std::endl;
}

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

std::string Negotiate::getDescription() const {
    return "Peace for a single turn between you and another player.";
}

std::string Negotiate::getEffectApplied() const {
    return "Attacks prevented with ...";
}

void Negotiate::onExecute() {
    std::cout << "Negotiate with the enemy's army!" << std::endl;
}

bool Negotiate::onValidate() const {
    return true;
}