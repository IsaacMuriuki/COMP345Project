#pragma once

#include <iostream>
#include <string>
#include "Player.h"

class Order {
private:
    bool _executed;
    // TODO: might need Player* here.
public:
    Order();
    virtual ~Order();
    Order(const Order& order);
    virtual Order& operator=(Order&& order);
    friend std::ostream& operator<<(std::ostream &out, const Order& order);

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    virtual Order* clone() = 0;

    /**
     * The order is executed if it is valid.
     **/
    virtual void execute() = 0;

    /**
     * Check if the order has been executed previously.
     * 
     * @return true if executed previously; false otherwise.
     **/
    bool isExecuted() const;

    /**
     * Checks if the order is valid.
     * 
     * @return true if not execute and valid; false otherwise.
     **/
    virtual bool validate() const = 0;

    virtual void onExecute() = 0;

    /**
     * Outputs a description and the effects of the order after the order is executed.
     **/
    friend std::ostream& operator<<(std::ostream &out, const Order& order);

protected:
    /**
     * Gets the description of the order.
     * 
     * @return description of the order.
     **/
    virtual std::string getDescription() const = 0;

    /**
     * Gets the results of the order when it executed.
     * 
     * @return results of the order.
     **/
    virtual std::string getEffectApplied() const = 0;
};

/**
 * Order caused by using a card.
 **/
class CardOrder : public Order {
protected:
    // TODO: add Player* and/or Card* as class field.
public:
    CardOrder();
    ~CardOrder();
    virtual CardOrder& operator=(CardOrder&& order);
    CardOrder(const CardOrder& order);

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    virtual Order* clone() = 0;

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    virtual std::string getDescription() const = 0;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    virtual std::string getEffectApplied() const = 0;
};

class Deploy : public Order {
private:
    int _units;
    Territory* territory;
    Player* player;
public:
    Deploy(int units, Player*, Territory*); // Add territory to constructor.
    ~Deploy();
    Deploy& operator=(Deploy&& order);
    Deploy(const Deploy& order);
    void execute();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    std::string getDescription() const;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    std::string getEffectApplied() const;

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool validate() const;

    void setUnitsToBeDeployed(int);

    void onExecute();
};

class Advance : public Order {
private:
    int _units;
    Player* player;
    Territory* sourceTerritory;
    Territory* targetTerritory;
public:
    Advance(int units, Territory* fromTerritory, Territory* toTerritory);
    ~Advance();
    Advance& operator=(Advance&& order);
    Advance(const Advance& order);
    void execute();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    std::string getDescription() const;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    std::string getEffectApplied() const;

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool validate() const;

    Territory *getSourceTerritory() const;

    void setSourceTerritory(Territory *fromTerritory);

    Territory *getTargetTerritory() const;

    void setTargetTerritory(Territory *toTerritory);

    void onExecute();
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
    void execute();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    std::string getDescription() const;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    std::string getEffectApplied() const;
    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool validate() const;

    void onExecute();
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
    void execute();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    std::string getDescription() const;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    std::string getEffectApplied() const;

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool validate() const;

    void onExecute();
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
    void execute();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    std::string getDescription() const;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    std::string getEffectApplied() const;

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool validate() const;

    void onExecute();
};

class Negotiate : public CardOrder {
public:
    Negotiate();
    ~Negotiate();
    Negotiate& operator=(Negotiate&& order);
    Negotiate(const Negotiate& order);
    void execute();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

protected:
    /**
     * Gets the description of the order.
     * Used for stream operator.
     * 
     * @return description of the order.
     **/
    std::string getDescription() const;

    /**
     * Gets the results of the order when it executed.
     * Used for stream operator.
     * 
     * @return results of the order.
     **/
    std::string getEffectApplied() const;

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool validate() const;

    void onExecute();
};