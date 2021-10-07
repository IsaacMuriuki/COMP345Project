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
    // TODO: maybe validate before execute?
    onExecute();
    _executed = true;
}

bool Order::isExecuted() {
    return _executed;
}

bool Order::validate() {
    return !_executed && !onValidate();
}

std::ostream& Order::operator<<(std::ostream &out) {
    out << getDescription() + (_executed ? " - " + getEffectApplied() : "");
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

std::string Deploy::getDescription() {
    return "Deploy units to a territory you own.";
}

std::string Deploy::getEffectApplied() {
    return "Placed " + std::to_string(_units) + " units on ";
}

void Deploy::onExecute() {
    std::cout << "Deploy the army of " << _units << " units!" << std::endl;
}

bool Deploy::onValidate() {
    // TODO: ensure territory is in player's team.
    return _units <= 0;
}


// Advance class definition
Advance::Advance(int units) {

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

std::string Advance::getDescription() {
    return "";
}

std::string Advance::getEffectApplied() {
    return "";
}

void Advance::onExecute() {
    std::cout << "Advance, army!" << std::endl;
}

bool Advance::onValidate() {
    // TODO: make sure there are more units on the territory than, or equal to, advancing.
    return true;
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

std::string Bomb::getDescription() {
    return "";
}

std::string Bomb::getEffectApplied() {
    return "";
}

void Bomb::onExecute() {
    std::cout << "Bomb ourselves!" << std::endl;
}

bool Bomb::onValidate() {
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

std::string Blockade::getDescription() {
    return "";
}

std::string Blockade::getEffectApplied() {
    return "";
}

void Blockade::onExecute() {
    std::cout << "Block every hit!" << std::endl;
}

bool Blockade::onValidate() {
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

std::string Airlift::getDescription() {
    return "";
}

std::string Airlift::getEffectApplied() {
    return "";
}

void Airlift::onExecute() {
    std::cout << "We have liftoff." << std::endl;
}

bool Airlift::onValidate() {
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

std::string Negotiate::getDescription() {
    return "";
}

std::string Negotiate::getEffectApplied() {
    return "";
}

void Negotiate::onExecute() {
    std::cout << "Negotiate with the enemy's army!" << std::endl;
}

bool Negotiate::onValidate() {
    return true;
}