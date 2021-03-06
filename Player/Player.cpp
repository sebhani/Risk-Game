#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "Player.h"
#include <iostream>
#include <list>

//============================ Player Class ============================/

//-------------- Constructors --------------//
Player::Player() : playerId(0)
{
}

Player::Player(int playerId, int nbArmies, std::vector<Territory *> territoriesOwned, Hand *cards, OrdersList *orders) : playerId(playerId), nbArmies(nbArmies), territoriesOwned(territoriesOwned), cards(cards), orders(orders)
{
}

Player::Player(const Player &e) : playerId(e.playerId), nbArmies(e.nbArmies), cards(new Hand(*(e.cards))), orders(new OrdersList(*(e.orders)))
{
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    };
}

//-------------- Destructor --------------//
Player::~Player()
{
    for (Territory *t : territoriesOwned)
    {
        delete t;
        t = nullptr;
    };
    delete cards;
    cards = nullptr;
    delete orders;
    orders = nullptr;
}

//-------------- Assignment operator --------------//
Player &Player::operator=(const Player &e)
{
    this->playerId = e.playerId;
    for (int i = 0; i < e.territoriesOwned.size(); i++)
    {
        this->territoriesOwned.push_back(new Territory(*(e.territoriesOwned[i])));
    };
    this->cards = new Hand(*(e.cards));
    this->orders = new OrdersList(*(e.orders));
    return *this;
}

//-------------- Accessor methods --------------//
int Player::getPlayerId()
{
    return playerId;
}

int Player::getNbArmies() {
    return nbArmies;
}

std::vector<Territory *> Player::getTerritoriesOwned()
{
    return territoriesOwned;
}

Hand *Player::getCards()
{
    return cards;
}

OrdersList *Player::getOrders()
{
    return orders;
}

//-------------- Mutator methods --------------//
void Player::setPlayerId(int playerId)
{
    this->playerId = playerId;
}

void Player::setNbArmies(int nbArmies) {
    this->nbArmies = nbArmies;
}

void Player::setTerritoriesOwned(std::vector<Territory *> territoriesOwned)
{
    this->territoriesOwned = territoriesOwned;
}

void Player::setCards(Hand *cards)
{
    this->cards = cards;
}

void Player::setOrders(OrdersList *orders)
{
    this->orders = orders;
}

//-------------- toDefent method --------------//
/*
 Returns a collection of territories that the player can defend
*/
std::vector<Territory *> Player::toDefend()
{
    cout << "Player" << playerId << " has this collection of territories to defend: {";
    for (Territory *t : territoriesOwned)
    {
        cout << *(t);
    };
    cout << "}\n";
    return territoriesOwned;
}

//-------------- toAttack method --------------//
/*
 (for the time being)Returns an arbitrary collection of territories
*/
std::vector<Territory *> Player::toAttack(Map *map)
{
    vector<Territory*> territoriesToAttack;
    vector<Node*> ownedTerritoriesNodes;
    for (Node *n : map->getV()) {
        for(Territory *t : territoriesOwned) {
            if (n->getDataPtr() == t) {
                ownedTerritoriesNodes.push_back(n);
            }

        }

    }
    for (Node *n : map->getV()) {
        for (Node *pn : ownedTerritoriesNodes) {
            if (map->areConnected(n, pn)) {
                territoriesToAttack.push_back(n->getDataPtr());
            }
        }
    }

    cout << "Player" << playerId << " has this collection of territories to attack: {";
    for (Territory *t : territoriesToAttack) {
        cout << *t << endl;
    }
    cout << "}\n";
    return territoriesToAttack;
}

//-------------- issueOrder method --------------//
/*
 Creates an order based on the player input and adds it to the player's OrdersList
*/
void Player::issueOrder()
{
    cout << "Player" << playerId << ", What order would you like to issue? \n0. Deploy \n1. Advance \n2. Bomb \n3. Blocakde \n4. Airlift \n5. Negotiate \n6. None \n";
    int num;
    cin >> num;
    switch (num)
    {
    case 0:
    {
        Deploy *deployp = new Deploy;
        (*(orders)).addOrder(deployp);
        cout << "Adding order " << *(deployp) << " to the player's order list \n";
        break;
    }
    case 1:
    {
        Advance *advancep = new Advance;
        (*(orders)).addOrder(advancep);
        cout << "Adding order " << *(advancep) << " to the player's order list \n";
        break;
    }
    case 2:
    {
        Bomb *bombp = new Bomb;
        (*(orders)).addOrder(bombp);
        cout << "Adding order " << *(bombp) << " to the player's order list \n";
        break;
    }
    case 3:
    {
        Blockade *blockadep = new Blockade;
        (*(orders)).addOrder(blockadep);
        cout << "Adding order " << *(blockadep) << " to the player's order list \n";
        break;
    }
    case 4:
    {
        Airlift *airliftp = new Airlift;
        (*(orders)).addOrder(airliftp);
        cout << "Adding order " << *(airliftp) << " to the player's order list \n";
        break;
    }
    case 5:
    {
        Negotiate *negotiatep = new Negotiate;
        (*(orders)).addOrder(negotiatep);
        cout << "Adding order " << *(negotiatep) << " to the player's order list \n";
        break;
    }
    case 6:
        cout << "No order added.\n";
        break;
    default:
    {
        throw logic_error("Invalid input");
    }
    }
    cout << *(orders);
}

//-------------- Stream insertion operator --------------//
std::ostream &operator<<(std::ostream &out, const Player &e)
{
    out << "Player" << e.playerId << ":\n";
    out << "Player4 has this collection of territories: {";
    for (Territory *t : e.territoriesOwned)
    {
        out << *(t);
    }
    out << "}\n";
    out << "Player4 has this hand of cards: ";
    (*(e.cards)).print();
    out << "Player4 has this list of orders: " << *(e.orders);
    return out;
}