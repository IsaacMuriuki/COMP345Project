#pragma once

#include "LoggingObserver.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Player.h"
#include "map.h"
using std::vector;

class Player;
class Territory;


class Order : public ILoggable, public Subject{
public:
    Order();
    Order(Player*);
    virtual ~Order();
    Order(const Order& order);
    virtual Order& operator=(Order&& order);
    friend std::ostream& operator<<(std::ostream &out, const Order& order);
    int getOrderID();
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
     * Get type of Order.
     * */
    virtual string getType() = 0;

    /**
     * Returns an entry of the effect of the order executed to be logged.
     * 
     * @return entry as a string.
     * */
    string stringToLog();

    /**
     * Outputs a description and the effects of the order after the order is executed.
     **/
    friend std::ostream& operator<<(std::ostream &out, const Order& order);

protected:
    bool executed;
    Player* player;
    string effectsApplied;
    static int ID;
    int orderID;

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

class Deploy : public Order {
private:
    int units;
    Territory* territory;
public:
    Deploy();
    Deploy(int units, Player*, Territory*);
    ~Deploy();
    Deploy& operator=(Deploy&& order);
    Deploy(const Deploy& order);
    void execute();
    string getType();

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
    int units;
    Territory* sourceTerritory;
    Territory* targetTerritory;
public:
    Advance();
    ~Advance();
    Advance(Player* player, int units, Territory* fromTerritory, Territory* toTerritory);
    Advance& operator=(Advance&& order);
    Advance(const Advance& order);
    void execute();
    string getType();

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
class Airlift : public Order {
public:
    Airlift();
    Airlift(Player* player, int units, Territory* sourceTerritory, Territory* targetTerritory);
    ~Airlift();
    Airlift& operator=(Airlift&& order);
    Airlift(const Airlift& order);
    void execute();
    string getType();

    /**
     * Gets a deep copy of the order itself.
     *
     * @return deep copy of the order.
     **/
    Order* clone();

private:
    int units;
    Territory* sourceTerritory;
    Territory* targetTerritory;

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
class Bomb : public Order {
public:
    Bomb();
    Bomb(Player* player, Territory* targetTerritory);
    ~Bomb();
    Bomb& operator=(Bomb&& order);
    Bomb(const Bomb& order);
    void execute();
    string getType();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

private:
    Territory* targetTerritory;
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
class Blockade : public Order {
public:
    Blockade();
    Blockade(Player* player, Territory* targetTerritory);
    ~Blockade();
    Blockade& operator=(Blockade&& order);
    Blockade(const Blockade& order);
    void execute();
    string getType();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

private:
    Territory* targetTerritory;

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



class Negotiate : public Order {
public:
    Negotiate();
    Negotiate(Player* player, Player* targetPlayer);
    ~Negotiate();
    Negotiate& operator=(Negotiate&& order);
    Negotiate(const Negotiate& order);
    void execute();
    string getType();

    /**
     * Gets a deep copy of the order itself.
     * 
     * @return deep copy of the order.
     **/
    Order* clone();

private:
    Player* targetPlayer;
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