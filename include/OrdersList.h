#pragma once

#include <vector>
#include "Orders.h"


class OrdersList {
    private:
    std::vector<Order*> _orders;

    public:
    OrdersList();
    ~OrdersList();
    OrdersList(const OrdersList& orders);
    OrdersList& operator=(OrdersList&& orders);

    /**
     * Inserts an order at the end of the list.
     * 
     * @param order order to add to the list.
     **/
    void add(Order* order);

    /**
     * Get the n-th order in the list.
     * 
     * @param index location in the list of the order to fetch.
     * @return order at the given index.
     **/
    Order* get(int index);

    /**
     * Swaps the location of two orders in the list. 
     * 
     * @param from index of one of the orders to swap.
     * @param to index of the other order to swap.
     * @return true if the swap occurred; false otherwise.
     **/
    bool move(int from, int to);

    /**
     * Pops the first element of the list.
     * 
     * @return first order in the list.
     * @exception std::out_of_range if the orders list is empty.
     **/
    Order* pop();

    /**
     * Removes an order at the end of the list.
     * 
     * @param index location in the list of the order to remove.
     * @return true if the order was removed; false otherwise.
     **/
    bool remove(int index);

    /**
     * Gets the size of the orders list.
     * 
     * @return number of orders in orders list.
     **/
    int size();
};