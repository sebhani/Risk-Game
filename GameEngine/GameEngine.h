#pragma once

#include <iostream>
using namespace std;
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include "../Player/Player.h"
#include "../Map/Map.h"

class GameStarter{
    private:
        string selectedMap;
        int numberOfPlayers;
        bool isObserverTurnedOn[2];//isObserverTurnedOn[0] for Phase Observer. isObserverTurnedOn[1] for Game Statistics Observer
        vector<Player*> players;
        Map* myGraph;
   
    public:
    //-------------- constructors --------------//
        GameStarter();
        GameStarter(const GameStarter& original);

    //-------------- Destructor --------------//
        ~GameStarter();

    //-------------- getters --------------//
        string getSelectedMap();
        int getSelectedNumberOfPlayers();
        bool* getIsObserverTurnedOn();
        vector<Player*> getPlayers();
        Map* getMyGraph();
        
    //-------------- getting user input --------------//
        void selectMap();
        void selectNumOfPlayers();
        void turnObservers();

    //-------------- set up the game --------------//
        void setUpGame();

    //-------------- Overloads --------------//
    //overload assignment operator
    GameStarter& operator=(const GameStarter& rhs);
    friend ostream& operator<<(ostream& output, GameStarter& obj);//to access private attributes
};

//overload stream insertion operator
ostream& operator<<(ostream& output, GameStarter& obj);