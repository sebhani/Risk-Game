#pragma once
#include <vector>
#include <string>
using namespace std;


//----------------------------Order Class----------------------------//
class Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Order();
    Order(string orderType);
    Order(const Order &order);

    //-------------- Getters --------------//
    //Make this getter 'virtual' to allow for polymorphism
    virtual string getOrderType();

    //-------------- Other Methods --------------//
    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Order &order);

    //Assignment operator
    virtual Order& operator =(const Order &order);
};


//----------------------------OrdersList Class----------------------------//
class OrdersList {

private:
    //A list of pointers to Order objects
    vector<Order*> oList;

public:
    //-------------- Constructors --------------//
    OrdersList();
    OrdersList(vector<Order*> ordList);
    OrdersList(const OrdersList &ordList);

    //-------------- Destructors --------------//
    ~OrdersList();

    //-------------- Getters --------------//
    vector<Order*> getOrdersList();

    //-------------- Setters --------------//
    void setOrdersList(vector<Order*> oList);

    //-------------- Other Methods --------------//
    //Method to add an Order to the players list of orders
    void addOrder(Order* order);

    //Method to delete an order from the players list of orders
    void deleteOrder(int index);

    //Method to move an order from one index to another
    void move(int currentOrderPos, int newOrderPos);

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, OrdersList &ordList);

    //Assignment operator
    OrdersList& operator =(const OrdersList &ordList);

};


//----------------------------Deploy Class----------------------------//
class Deploy : public Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Deploy();
    Deploy(string orderType);
    Deploy(const Deploy &dep);

    //-------------- Getters --------------//
    string getOrderType();

    //-------------- Other Methods --------------//
    //Method to validate if an order is valid
    bool validate();

    //Method to execute the order
    void execute();

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Deploy &dep);

    //Assignment operator
    Deploy& operator =(const Deploy &dep);

};


//----------------------------Advance Class----------------------------//
class Advance : public Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Advance();
    Advance(string orderType);
    Advance(const Advance &adv);

    //-------------- Getters --------------//
    string getOrderType();

    //-------------- Other Methods --------------//
    //Method to validate if an order is valid
    bool validate();

    //Method to execute the order
    void execute();

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Advance &adv);

    //Assignment operator
    Advance& operator =(const Advance &adv);
};


//----------------------------Bomb Class----------------------------//
class Bomb : public Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Bomb();
    Bomb(string orderType);
    Bomb(const Bomb &bomb);

    //-------------- Getters --------------//
    string getOrderType();

    //-------------- Other methods --------------//
    //Method to validate if an order is valid
    bool validate();

    //Method to execute the order
    void execute();

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Bomb &bomb);

    //Assignment operator
    Bomb& operator =(const Bomb &bomb);

};


//----------------------------Blockade Class----------------------------//
class Blockade : public Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Blockade();
    Blockade(string orderType);
    Blockade(const Blockade &block);

    //-------------- Getters --------------//
    string getOrderType();

    //-------------- Other Methods --------------//
    //Method to validate if an order is valid
    bool validate();

    //Method to execute the order
    void execute();

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Blockade &block);

    //Assignment operator
    Blockade& operator =(const Blockade &block);

};


//----------------------------Airlift Class----------------------------//
class Airlift : public Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Airlift();
    Airlift(string orderType);
    Airlift(const Airlift &air);

    //-------------- Getters --------------//
    string getOrderType();

    //-------------- Other Methods --------------//
    //Method to validate if an order is valid
    bool validate();

    //Method to execute the order
    void execute();

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Airlift &air);

    //Assignment operator
    Airlift& operator =(const Airlift &air);

};


//----------------------------Negotiate Class----------------------------//
class Negotiate : public Order {

private:
    //String describing the order type
    string orderType;

public:
    //-------------- Constructors --------------//
    Negotiate();
    Negotiate(string orderType);
    Negotiate(const Negotiate &neg);

    //-------------- Getters --------------//
    string getOrderType();

    //-------------- Other Methods --------------//
    //Method to validate if an order is valid
    bool validate();

    //Method to execute the order
    void execute();

    //Stream insertion operator
    friend ostream& operator <<(ostream &strm, Negotiate &neg);

    //Assignment operator
    Negotiate& operator =(const Negotiate &neg);

};







