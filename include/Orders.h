#pragma once

#include <iostream>

class Order {
    protected:
    bool _cancelled;
    // TODO: might need team reference here.
    public:
    bool cancel();
    virtual void execute()=0;
    virtual bool onCancel()=0;
    virtual bool validate()=0;
    friend std::ostream& operator<<(std::ostream &out, const Order &order);
};

/**
 * Order caused by using a card.
 **/
class CardOrder : public Order {
    protected:
    // TODO: add Player* and/or Card* as class reference.
    public:
    CardOrder();
    ~CardOrder();
    virtual void execute()=0;
    bool onCancel();
    virtual bool validate()=0;
};

class Deploy : public Order {
    private:
    int _units;
    // TODO: add territory as class field.
    public:
    Deploy(int units); // Add territory to constructor.
    ~Deploy();
    void execute();
    bool onCancel();
    bool validate();
};

class Advance : public Order {
    private:
    int _units;
    // TODO: add territory (from) as class field.
    // TODO: add territory (to) as class field.
    public:
    Advance(int units); // Add territories to constructor.
    ~Advance();
    void execute();
    bool onCancel();
    bool validate();
};

/**
 * Order caused by using a card.
 **/
class Bomb : public CardOrder {
    public:
    Bomb();
    ~Bomb();
    void execute();
    bool validate();
};

/**
 * Order caused by using a card.
 **/
class Blockade : public CardOrder {
    public:
    Blockade();
    ~Blockade();
    void execute();
    bool validate();
};

/**
 * Order caused by using a card.
 **/
class Airlift : public CardOrder {
    public:
    Airlift();
    ~Airlift();
    void execute();
    bool validate();
};

class Negotiate : public Order {
    public:
    Negotiate();
    ~Negotiate();
    void execute();
    bool onCancel();
    bool validate();
};