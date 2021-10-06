#include "Orders.h"

bool Order::cancel() {
    if (!_cancelled && onCancel()) {
        _cancelled = true;
    }
    return _cancelled;
}

// Order class definition
void Order::execute() {
    std::cout << "Order::execute(): base class execution." << std::endl;
}

bool Order::validate() {
    return false;
}


CardOrder::CardOrder() {

}

CardOrder::~CardOrder() {

}

void CardOrder::execute() {

}

bool CardOrder::validate() {
    return false;
}

bool CardOrder::onCancel() {
    // TODO: return card to player.
    return true;
}


// Deploy class definition
Deploy::Deploy(int units) {
    _units = units;
}

Deploy::~Deploy() {
    // TODO: delete both territories.
}

void Deploy::execute() {
    Order::execute();
    std::cout << "Deploy the army!" << std::endl;
}

bool Deploy::onCancel() {
    return true;
}

bool Deploy::validate() {
    // TODO: ensure territory is in player's team.
    return true;
}


// Advance class definition
Advance::Advance(int units) {

}

Advance::~Advance() {
    // TODO: delete territory.
}

void Advance::execute() {
    std::cout << "Advance, army!" << std::endl;
}

bool Advance::onCancel() {
    return true;
}

bool Advance::validate() {
    return true;
}


// Bomb class definition
Bomb::Bomb() {

}

Bomb::~Bomb() {

}

void Bomb::execute() {
    std::cout << "Bomb ourselves!" << std::endl;
}

bool Bomb::validate() {
    return true;
}


// Blockade class definition
Blockade::Blockade() {

}

Blockade::~Blockade() {

}

void Blockade::execute() {
    std::cout << "Block every hit!" << std::endl;
}

bool Blockade::validate() {
    return true;
}


// Airlift class definition
Airlift::Airlift() {

}

Airlift::~Airlift() {

}

void Airlift::execute() {
    std::cout << "We have liftoff." << std::endl;
}

bool Airlift::validate() {
    return true;
}


// Negotiate class definition
Negotiate::Negotiate() {

}

Negotiate::~Negotiate() {

}

void Negotiate::execute() {
    std::cout << "Negotiate with the enemy's army!" << std::endl;
}

bool Negotiate::onCancel() {
    return true;
}

bool Negotiate::validate() {
    return true;
}