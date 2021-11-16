#pragma once

#include "LoggingObserver.h"

#include <iostream>
#include <string>

class Order : public ILoggable, public Subject{
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
    void execute();

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
    bool validate() const;

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

    /**
     * Additional actions taken for when the order gets executed.
     **/
    virtual void onExecute() = 0;

    /**
     * Additional checks for validation of the order.
     **/
    virtual bool onValidate() const = 0;
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

    /**
     * Additional actions taken for when the order gets executed.
     **/
    virtual void onExecute() = 0;

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    virtual bool onValidate() const = 0;
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
     * Additional actions taken for when the order gets executed.
     **/
    void onExecute();

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool onValidate() const;
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
     * Additional actions taken for when the order gets executed.
     **/
    void onExecute();

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool onValidate() const;
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
     * Additional actions taken for when the order gets executed.
     **/
    void onExecute();

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool onValidate() const;
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
     * Additional actions taken for when the order gets executed.
     **/
    void onExecute();

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool onValidate() const;
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
     * Additional actions taken for when the order gets executed.
     **/
    void onExecute();

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool onValidate() const;
};

class Negotiate : public Order {
    public:
    Negotiate();
    ~Negotiate();
    Negotiate& operator=(Negotiate&& order);
    Negotiate(const Negotiate& order);

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
     * Additional actions taken for when the order gets executed.
     **/
    void onExecute();

    /**
     * Additional checks for validation of the order.
     * 
     * @return true if the additional validations pass; false otherwise.
     **/
    bool onValidate() const;
};