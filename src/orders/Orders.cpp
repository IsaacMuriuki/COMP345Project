#include "Orders.h"


// Order class definition
void Order::execute() {
    std::cout << "Order::execute(): base class execution." << std::endl;
}

bool Order::validate() {
    return false;
}


// Deploy class definition
Deploy::Deploy() {
    
}

Deploy::~Deploy() {

}

void Deploy::execute() {
    Order::execute();
    std::cout << "Deploy the army!" << std::endl;
}

bool Deploy::validate() {
    return true;
}


// Advance class definition
Advance::Advance() {

}

Advance::~Advance() {

}

void Advance::execute() {
    std::cout << "Advance, army!" << std::endl;
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

bool Negotiate::validate() {
    return true;
}