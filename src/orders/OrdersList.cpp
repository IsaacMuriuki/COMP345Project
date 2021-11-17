#include "OrdersList.h"


OrdersList::OrdersList() {
    _orders = std::vector<Order*>();
}

OrdersList::~OrdersList() {
    for ( int i = 0; i < _orders.size(); i++ ) {
        delete _orders[i];
    }
    _orders.clear();
}

OrdersList& OrdersList::operator=(OrdersList&& orders) {
    if (this != &orders) {
        // we want the move constructor. copy the pointers over.
        _orders = std::vector<Order*>(orders._orders);
    }
    return *this;
}

OrdersList::OrdersList(const OrdersList& orders) : OrdersList() {
    _orders = std::vector<Order*>();
    for (auto order : orders._orders) {
        _orders.push_back(order->clone());
    }
}

/**
 * Inserts an order at the end of the list.
 * 
 * @param order order to add to the list.
 **/
void OrdersList::add(Order* order) {
    // std::vector adds the same reference to the same object.
    _orders.push_back(order);

    // Notifies observer of the order issued.
    Notify(this);
}

/**
 * Get the n-th order in the list.
 * 
 * @param index location in the list of the order to fetch.
 * @return order at the given index.
 * @exception std::out_of_range if index is out of bounds of the orders list.
 **/
Order* OrdersList::get(int index) {
    return _orders.at(index);
}

/**
 * Swaps the location of two orders in the list. 
 * 
 * @param from index of one of the orders to swap.
 * @param to index of the other order to swap.
 * @return true if the swap occurred; false otherwise.
 **/
bool OrdersList::move(int from, int to) {
    if (from < 0 || from >= _orders.size() || to < 0 || to >= _orders.size())
        return false;

    Order* temp = _orders[from];
    _orders[from] = _orders[to];
    _orders[to] = temp;

    return true;
}

/**
 * Pops the first element of the list.
 * 
 * @return first order in the list.
 * @exception std::out_of_range if the orders list is empty.
 **/
Order* OrdersList::pop() {
    Order* order = get(0);
    remove(0);
    return order;
}

/**
 * Removes an order at the end of the list.
 * 
 * @param index location in the list of the order to remove.
 * @return true if the order was removed; false otherwise.
 **/
bool OrdersList::remove(int index) {
    if (index < 0 || _orders.size() <= index) {
        return false;
    }
    
    delete _orders[index];
    _orders[index] = NULL;
    _orders.erase(_orders.begin() + index);
    return true;
}

bool OrdersList::remove(Order * order) {
    bool hasremovedOrder = false;
    for(int i =0; _orders.size(); i++ ){
        if (_orders.at(i)->getOrderID() == order->getOrderID()) {
            delete _orders.at(i);
            _orders.erase(_orders.begin() + i);
            _orders.shrink_to_fit();
            hasremovedOrder = true;
        }
    }
    return hasremovedOrder;
}

/**
 * Gets the size of the orders list.
 * 
 * @return number of orders in orders list.
 **/
int OrdersList::size() {
    return _orders.size();
}

/**
 * Returns an entry of the order issued to be logged.
 * 
 * @return entry as a string.
 * */
string OrdersList::stringToLog(){
    return "Order Issued: " + _orders[_orders.size() - 1]->getType();
}