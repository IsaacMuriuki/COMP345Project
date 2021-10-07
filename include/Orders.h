#pragma once

#include <iostream>
#include <string>

class Order {
    private:
    bool _executed;
    // TODO: might need team reference here.
    public:
    Order();
    ~Order();
    Order(const Order& order);
    virtual Order& operator=(Order&& order);
    void execute();
    bool isExecuted();
    bool validate();
    std::ostream& operator<<(std::ostream &out);
    protected:
    virtual std::string getDescription()=0;
    virtual std::string getEffectApplied()=0;
    virtual void onExecute()=0;
    virtual bool onValidate()=0;
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
    virtual CardOrder& operator=(CardOrder&& order);
    CardOrder(const CardOrder& order);
    protected:
    virtual std::string getDescription()=0;
    virtual std::string getEffectApplied()=0;
    virtual void onExecute()=0;
    virtual bool onValidate()=0;
};

class Deploy : public Order {
    private:
    int _units;
    // TODO: add territory as class field.
    public:
    Deploy(int units); // Add territory to constructor.
    ~Deploy();
    Deploy& operator=(Deploy&& order);
    Deploy(const Deploy& order);
    protected:
    std::string getDescription();
    std::string getEffectApplied();
    void onExecute();
    bool onValidate();
};

class Advance : public Order {
    private:
    int _units;
    // TODO: add territory (from) as class field.
    // TODO: add territory (to) as class field.
    public:
    Advance(int units); // Add territories to constructor.
    ~Advance();
    Advance& operator=(Advance&& order);
    Advance(const Advance& order);
    protected:
    std::string getDescription();
    std::string getEffectApplied();
    void onExecute();
    bool onValidate();
};

/**
 * Order caused by using a card.
 **/
class Bomb : public CardOrder {
    public:
    Bomb();
    ~Bomb();
    Bomb& operator=(Bomb&& order);
    Bomb(const Bomb& order);
    protected:
    std::string getDescription();
    std::string getEffectApplied();
    void onExecute();
    bool onValidate();
};

/**
 * Order caused by using a card.
 **/
class Blockade : public CardOrder {
    public:
    Blockade();
    ~Blockade();
    Blockade& operator=(Blockade&& order);
    Blockade(const Blockade& order);
    protected:
    std::string getDescription();
    std::string getEffectApplied();
    void onExecute();
    bool onValidate();
};

/**
 * Order caused by using a card.
 **/
class Airlift : public CardOrder {
    public:
    Airlift();
    ~Airlift();
    Airlift& operator=(Airlift&& order);
    Airlift(const Airlift& order);
    protected:
    std::string getDescription();
    std::string getEffectApplied();
    void onExecute();
    bool onValidate();
};

class Negotiate : public Order {
    public:
    Negotiate();
    ~Negotiate();
    Negotiate& operator=(Negotiate&& order);
    Negotiate(const Negotiate& order);
    protected:
    std::string getDescription();
    std::string getEffectApplied();
    void onExecute();
    bool onValidate();
};