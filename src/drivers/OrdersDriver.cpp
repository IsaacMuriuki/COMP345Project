#include <iostream>
#include "Drivers.h"
#include "Orders.h"
#include "OrdersList.h"


std::ostream& operator<<(std::ostream &out, const Order& order) {
    out << order.getDescription() << (order.isExecuted() ? " - " + order.getEffectApplied() : "");
    return out;
}

void OrdersDriver::demo() {
    std::cout << "Creating all order instances." << std::endl;
    Order* deploy = new Deploy(8);
    Order* advance = new Advance(4);
    Order* bomb = new Bomb();
    Order* blockade = new Blockade();
    Order* airlift = new Airlift();
    Negotiate* negotiate = new Negotiate();
    Deploy* deploy2 = new Deploy(2);
    Order* invalid = new Advance(-1);

    std::cout << "Creating OrdersList." << std::endl;
    OrdersList* list = new OrdersList();

    std::cout << std::endl;
    std::cout << "Adding Deploy order (" << (deploy->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(deploy);
    std::cout << "Adding Advance order (" << (advance->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(advance);
    std::cout << "Adding Bomb order (" << (bomb->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(bomb);
    std::cout << "Adding Blockade order (" << (blockade->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(blockade);
    std::cout << "Adding Airlift order (" << (airlift->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(airlift);
    std::cout << "Adding Negotiate order (" << (negotiate->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(negotiate);
    std::cout << "Adding a second Deploy order (" << (deploy2->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(deploy2);
    std::cout << "Adding the first Deploy order again (" << (deploy->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(deploy);
    std::cout << "Adding an invalid order (" << (invalid->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(invalid);
    std::cout << "OrdersList has " << list->size() << " orders." << std::endl;

    std::cout << std::endl;
    std::cout << "Executing deploy order." << std::endl;
    deploy->execute();
    std::cout << "Executing advance order." << std::endl;
    advance->execute();
    std::cout << "Executing invalid order." << std::endl;
    invalid->execute();

    std::cout << std::endl;
    std::cout << "Print out the advance order." << std::endl;
    std::cout << *list->get(1) << std::endl;
    std::cout << "Print out the bomb order." << std::endl;
    std::cout << *list->get(2) << std::endl;
    std::cout << "Print out the second deploy order." << std::endl;
    std::cout << *list->get(6) << std::endl;
    std::cout << "Print out the third deploy order." << std::endl;
    std::cout << *list->get(7) << std::endl;

    std::cout << std::endl;
    std::cout << "Output " << std::endl;

    std::cout << std::endl;
    std::cout << "Remove advance order (index = 1)." << std::endl;
    list->remove(1);
    std::cout << "OrdersList is now size " << list->size() << std::endl;
    std::cout << "OrdersList at index 1 has '" << *list->get(1) << "'." << std::endl;
    std::cout << "Remove order at index = 100." << std::endl;
    list->remove(100);
    std::cout << "OrdersList is now size " << list->size() << std::endl;

    std::cout << std::endl;
    std::cout << "Moving indexes 1 (" << *list->get(1) << ") and 5 (" << *list->get(5) << ")." << std::endl;
    list->move(1, 5);
    std::cout << "Now, OrdersList have '" << *list->get(1) << "' at index 1 and and '" << *list->get(5) << "' at index 5." << std::endl;
}