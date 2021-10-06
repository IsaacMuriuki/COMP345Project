#pragma once

#include <iostream>

class Order {
    public:
    
    virtual void execute();
    virtual bool validate();
    friend std::ostream& operator<<(std::ostream &out, const Order &order);
};

class Deploy : public Order {
    public:
    Deploy();
    ~Deploy();
    virtual void execute();
    virtual bool validate();
};

class Advance : public Order {
    public:
    Advance();
    ~Advance();
    virtual void execute();
    virtual bool validate();
};

class Bomb : public Order {
    public:
    Bomb();
    ~Bomb();
    virtual void execute();
    virtual bool validate();
};

class Blockade : public Order {
    public:
    Blockade();
    ~Blockade();
    virtual void execute();
    virtual bool validate();
};

class Airlift : public Order {
    public:
    Airlift();
    ~Airlift();
    virtual void execute();
    virtual bool validate();
};

class Negotiate : public Order {
    public:
    Negotiate();
    ~Negotiate();
    virtual void execute();
    virtual bool validate();
};