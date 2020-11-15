#include <iostream>
#include "./GameEngine.h"
#include <list>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Map/Map.h"

using namespace std;

GameStarter::GameStarter(){
    selectedMap = "";
    numberOfPlayers = 0;
    isObserverTurnedOn[0] = false;//Phase Observer
    isObserverTurnedOn[1] = false;//Game Statistics Observer
}

string GameStarter::getSelectedMap(){
    return selectedMap;
}

int GameStarter::getSelectedNumberOfPlayers(){
    return numberOfPlayers;
}

bool* GameStarter::getIsObserverTurnedOn(){
    return isObserverTurnedOn;
}

vector<Player*> GameStarter::getPlayers(){
    return players;
}

Map* GameStarter::getMyGraph(){
    return myGraph;
}

void GameStarter::selectMap(){
    int mapNum;
    cout<<"Available maps:"<<endl;

    //!!!!!!!!!!!!!! dummy should by replace with list_dir from MapLoaderDriver
    list<string> listOfMaps = list_dir("./MapLoader/Maps/");

    int count = 1;
    for(std::list<std::string>::const_iterator i = listOfMaps.begin(); i != listOfMaps.end(); ++i)
    {
        cout<<count<<"-"<<*i<<"\t";
        
        
        //every 4 maps will be printed in a single line
        if(count%4 == 0 || count == listOfMaps.size())
            cout<<endl;

        count++;
    }

    cout<<"Which map would you like to load (enter its number): ";
    
    bool isInputCorrect = false;
    while(!isInputCorrect){
        cin>>mapNum;

        if(mapNum>=1 && mapNum<=listOfMaps.size()){
            isInputCorrect = true;
        }else{//hanldes invalid inputs (i.e. 0, x>listOfMaps.size() and non-int input)
            if(cin.fail()){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout<<"Invalid input! Re-choose a map: ";
        }
    }

    //find element from the list
    list<string>::iterator it = std::next(listOfMaps.begin(), mapNum-1);
    selectedMap = *it;
}

void GameStarter::selectNumOfPlayers(){
    int tempNumOfPlayers;
    cout<<"How many palyers (2-5)? ";
    
    bool isInputCorrect = false;
    while(!isInputCorrect){
        cin>>tempNumOfPlayers;

        if(tempNumOfPlayers>=2 && tempNumOfPlayers<=5){
            isInputCorrect = true;
        }else{//hanldes invalid inputs (i.e. 0, tempNumOfPlayers<2 or tempNumOfPlayers>5 or non-int input)
            if(cin.fail()){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout<<"Invalid input! Re-enter number of players: ";
        }
    }
    numberOfPlayers = tempNumOfPlayers;
}

void GameStarter::turnObservers(){
    char responseGameStatistics;
    char phaseObserver;

    cout<<"Would you like to turn on Phase Observer (y for yes/anything else for no)? ";
    cin>>phaseObserver;

    cout<<"Would you like to turn on Game Statistics Observer (y for yes/anything else for no)? ";
    cin>>responseGameStatistics;

    if(phaseObserver == 'y')
        isObserverTurnedOn[0] = true;
    if(responseGameStatistics == 'y')
        isObserverTurnedOn[1] = true;
}

void GameStarter::setUpGame(){
    selectMap();//load the map
    myGraph = new Map(parseMap(selectedMap));

    selectNumOfPlayers();

    // Creating order pointers and a vector of order pointers for the player
    Deploy *d1 = new Deploy;
    Advance *a1 = new Advance;
    Bomb *b1 = new Bomb;
    vector<Order *> vo;
    vo.push_back(d1);
    vo.push_back(a1);
    vo.push_back(b1);
    OrdersList *olp = new OrdersList(vo);

    //create players
    for(int i=0; i<numberOfPlayers;i++){
        players.push_back(new Player);
        players.front()->setPlayerId(i);

        players.front()->setCards(new Hand); //assign an empty hand of cards
        players.front()->setOrders(olp); //assign orders
    }

    // Create a deck of cards
    Card *card4 = new Card(0);
    Card *card5 = new Card(1);
    Card *card6 = new Card(3);
    vector<Card *> vdeck1;
    vdeck1.push_back(card4);
    vdeck1.push_back(card5);
    vdeck1.push_back(card6);
    Deck *deckp = new Deck(vdeck1);
}

vector<string> getCountriesInContinent(Map* map, Continent* continent){
    vector<string> teritories;
    for(Node* territory : map->getV()){
        if( territory->getData().getContinent()->getContinentName() == continent->getContinentName()){
            teritories.push_back(territory->getData().getTerritoryName());
        }
    }
    return teritories;
}
vector<string> playerTerritories(vector<Territory*> terriroies){
    vector<string> names;
    for(Territory* territory : terriroies){
        names.push_back(territory->getTerritoryName());
    }
    return names;
}
bool hasAllTerritories(Player* player, Map* map, Continent* continent) {
    vector<string> cTerritories=getCountriesInContinent(map, continent);
    vector<string> pTerritories=playerTerritories(player->getTerritoriesOwned());
    bool contain= false;
    for(std::vector<string>::iterator it = cTerritories.begin(); it != cTerritories.end(); ++it) {
        bool booll = find(pTerritories.begin(), pTerritories.end(), *it) != pTerritories.end();
        if (!booll)
        {
            contain = false;
        }
        else{ contain = true; }
    }
    return contain;
}

void reinforcementPhase(GameStarter x) {

    vector<Player*> players= x.getPlayers();
    Map* map=x.getMyGraph();
    for (Player* player : players) {
        int reinforcement = 0;
        reinforcement += player->getTerritoriesOwned().size() / 3;
        cout << "reinforcement is: " << player->getTerritoriesOwned().size() << endl;
        int playerTerritories = player->getTerritoriesOwned().size();
        for(Continent* continent : map->getListOfContinents()){
            if(hasAllTerritories(player, map, continent)){
                reinforcement+= continent->getBonus();
            }
        }
        if(reinforcement<3){
            cout << "player doesn't have enough territories" <<endl;
            reinforcement=3;}
        int prev = player->getNbArmies();
        player->setNbArmies(prev+reinforcement);
        cout << "player has " << player->getNbArmies() << "armies" <<endl;
    }
}
void issueOrdersPhase(GameStarter x) {
    vector<Player*> players= x.getPlayers();
    // Contains whether a player is done with their turn or not. True if not done.
    std::map<int, bool> playerTurns = std::map<int, bool>();
    // Initializing the map
    int i=0;
    for (Player* player : players) {
        playerTurns[i] = true;
        i++;
    }

    // Going round robin until all turns are done.
    int amountOfPlayersDone = 0;

    while (amountOfPlayersDone != players.size()) {
        int i=0;
        for (Player* player : players) {
            // If a player did not end his turn yet...
            if (playerTurns[i]) {
                // ... it is prompted to play.
                player->issueOrder();

                // If it decided to end it's turn just now...
                if (!playerTurns[i]) {
                    // ... we add it to the number of players that are done.
                    amountOfPlayersDone++;
                }
            }
            i++;
        }
    }
    // Everyone has played.
}

//-------------- Main Game Loop --------------//
void mainGameLoop(GameStarter x) {
    vector<Player*> players= x.getPlayers();
    cout << "Let the game begin!" << endl;
    reinforcementPhase(x);
    issueOrdersPhase(x);

}

int main(){
    GameStarter x = GameStarter();
    x.setUpGame();
    cout<<"am heeere"<<endl;
    mainGameLoop(x);
    cout<<"Size: "<<x.getPlayers().front()->getPlayerId()<<endl;
    cout<<"Size: "<<x.getPlayers().back()->getPlayerId()<<endl;

    return 0;
}