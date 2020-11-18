#pragma once

#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include <vector>

//============================ Forward declarations  ============================//
class Card;
class Hand;
class GameStarter;

//============================ Player Class ============================//
class Player : public Subject
{

private:
    //-------------- Data members --------------//
    int playerId;
    int nbArmies;
    int reinforcementPool;
    // Vector of players that the player can't attack for a turn, related to negotiate order logic
    std::vector<Player*> unattackablePlayers;
    // vector of Territories owned by Player
    std::vector<Territory *> territoriesOwned;
    // ptr of type Hand that contains a vector of ptr of Cards that belong to Player
    Hand *cards;
    // ptr of type OrdersList that contains a vector of ptr of Orders that belong to Player
    OrdersList *orders;
    // The Phase observer needs to know the current phase
    Phase phase ;

public:
    //-------------- Constructors --------------//
    Player();
    Player(int playerId, int reinforcementPool, std::vector<Player*> unattackablePlayers, int nbArmies, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders);
    Player(const Player &e);

    //-------------- Destructor --------------//
    ~Player();

    //-------------- Assignment operator --------------//
    Player &operator=(const Player &e);

    //-------------- Accessor methods --------------//
    int getPlayerId();
    int getNbArmies();
    int getReinforcementPool();
    std::vector<Player *> getUnattackablePlayers();
    std::vector<Territory *> getTerritoriesOwned();
    Hand *getCards();
    OrdersList *getOrders();
    Phase getPhase();

    //-------------- Mutator methods --------------//
    void setPlayerId(int playerId);
    void setNbArmies(int nbArmies);
    void setReinforcementPool(int reinforcementPool);
    void setUnattackablePlayers(std::vector<Player*> unattackblePlayers);
    void setTerritoriesOwned(std::vector<Territory *> territoriesOwned);
    void setCards(Hand *cards);
    void setOrders(OrdersList *orders);

    //-------------- toDefend method --------------//
    std::vector<Territory *> toDefend();

    //--------------  toAttack method --------------//
    std::vector<Territory *> toAttack(Map *map);

    //-------------- AddArmiesToReinforcementPool method --------------//
    void addArmiesToReinforcementPool(int numberOfArmies);


    //-------------- issueOrder method --------------//
    void issueOrder(Map *map, GameStarter *gameStarter);

    //-------------- Stream insertion Operator --------------//
    friend std::ostream &operator<<(std::ostream &out, const Player &e);
};