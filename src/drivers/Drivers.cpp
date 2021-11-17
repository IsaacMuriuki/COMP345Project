#include "Drivers.h"
#include "Cards.h"
#include "GameEngine.h"
#include "CommandProcessor.h"
#include "map.h"
#include "Orders.h"
#include "OrdersList.h"
#include "Player.h"
#include "LoggingObserver.h"
#include "Utilities.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <filesystem>

using std::cout, std::cin, std::endl;
namespace fs = std::filesystem;

void orderExecutionDriver() {
    const string BRASIL_MAP = "../maps/brasil.map";
    cout << endl << "\n************* DEPLOY ORDER *************\n";

    MapLoader loader;
    Map *brasilMap = loader.loadMap(BRASIL_MAP);

    Deck* deck = new Deck();
    Hand* hand = new Hand(deck);
    Hand* hand1 = new Hand(deck);
    Hand* hand2 = new Hand(deck);

    vector<Territory*> territories = brasilMap->getTerritories();
    vector<Territory*> player1Territories;
    vector<Territory*> player2Territories;
    vector<Territory*> neutralPlayerTerritories;

    Player* player1 = new Player("player 1", player1Territories, new OrdersList, hand);
    Player* player2 = new Player("player 2", player2Territories, new OrdersList, hand1);
    Player* neutral = new Player("neutral player", true, neutralPlayerTerritories, new OrdersList, hand2);

    for (int i = 0; i < territories.size(); ++i) {
        if(i % 2 == 0){
            territories[i]->setOwner(player1);
            player1->addTerritory(territories[i]);
            territories.at(i)->setUnits(10);
        } else{
            territories[i]->setOwner(player2);
            player2->addTerritory(territories[i]);
            territories.at(i)->setUnits(5);
        }
    }

    Deploy* deploy = new Deploy(5, player1, territories[0]);
    Deploy* deploy1 = new Deploy(2, player2, territories[2]);
    player1->addToReinforcementPool(5);
    player2->addToReinforcementPool(1);
    player1->addOrder(deploy);
    player2->addOrder(deploy1);

    deploy->execute();
    deploy1->execute();

    cout << endl << "\n************* ADVANCE ORDER *************\n";
    Advance* advance = new Advance(player1, 10, player1->getTerritories()[0], player2->getTerritories()[0]);
    player1->addOrder(advance);

    cout << "Player 1s number of cards before advance: "<< player1->getHandOfCards()->size()<< " ";
    for (int i =0; i < player1->getHandOfCards()->size(); ++i){
        cout << player1->getHandOfCards()->getHand(i).toString() << ", ";
    }

    cout << endl;
    cout << "Advance from " << player1->getTerritories()[0]->getName() << "(units: " << player1->getTerritories()[0]->getUnits() << ") to "
         << player2->getTerritories()[0]->getName() << "(units: " << player2->getTerritories()[0]->getUnits() << ")" << endl;

    Territory* amazonas = player2->getTerritories()[0];
    advance->execute();
    cout << "Owner of Amazonas after advance order : " << amazonas->getOwner()->getName() << endl;
    cout << "Player 1s number of cards after advance: "<< player1->getHandOfCards()->size() << " -> ";

    for (int i =0; i < player1->getHandOfCards()->size(); ++i){
        cout << player1->getHandOfCards()->getHand(i).toString() << "\n";
    }

    cout << endl << "\n************* NEGOTIATE ORDER *************\n";
    Negotiate* negotiate = new Negotiate(player1, player2);
    player1->addOrder(negotiate);
    negotiate->execute();

    Advance* advance1 = new Advance(player1, 10, player1->getTerritories()[1], player2->getTerritories()[7]);
    player1->addOrder(advance);
    cout << "Advance from " << player1->getTerritories()[1]->getName() << "(units: " << player1->getTerritories()[1]->getUnits() << ") to "
         << player2->getTerritories()[7]->getName() << "(units: " << player2->getTerritories()[7]->getUnits() << ")" << endl;

    advance->execute();

    cout << endl << "\n************* BLOCKADE ORDER *************\n";
    Blockade* blockade = new Blockade(player1, neutral, player1->getTerritories()[0]);
    player1->addOrder(blockade);
    Territory* t = player1->getTerritories()[0];
    cout << "Number of armies in " << t->getName() << " before blockade order : " << t->getUnits() << ". Owner : " << t->getOwner()->getName() << endl;
    blockade->execute();
    cout << "Number of armies in " << t->getName() << " after blockade order : " << t->getUnits() << ". Owner : " << t->getOwner()->getName() << endl;

//    cout << endl << "\n************* AIRLIFT ORDER *************\n";
//    cout << endl << "\n************* BOMB ORDER *************\n";
}

void mapDriver() {
    const string MAPS_FOLDER = "../../maps/"; // for mac this works -> const string MAPS_FOLDER = "../maps";
    MapLoader loader;

    // read all files in valid maps folder
    try
    {
        for (const auto &entry : fs::directory_iterator(MAPS_FOLDER))
        {
            cout << "\nLoading map: " << entry.path().filename() << endl;
            cout << "Validating..." << endl;
            Map *m = loader.loadMap(entry.path().string());
            // check if file is valid
            if (m != NULL)
            {
                // check if map is valid
                if (m->validate())
                {
                    cout << *m << endl;
                }
                else
                {
                    cout << "Invalid map" << endl;
                }
            }
            else
            {
                cout << "The file " << entry.path().filename() << " is not a valid .map file." << endl;
            }
        }
    }
    catch (const fs::filesystem_error)
    {
        cout << "\nInvalid folder..." << endl;
    }
}


void territoryValuesDriver() {
    Continent NA = Continent(0, "NA", 4);
    Territory CANADA = Territory(0, "CANADA", &NA);
    Territory US = Territory(1, "US", &NA);
    Territory MEXICO = Territory(2, "MEXICO", &NA);
    std::vector<Player> playerList;

    CANADA.addAdjacentTerritory(&US);
    US.addAdjacentTerritory(&CANADA);
    US.addAdjacentTerritory(&MEXICO);
    MEXICO.addAdjacentTerritory(&US);

    NA.addTerritory(&US);
    NA.addTerritory(&CANADA);
    NA.addTerritory(&MEXICO);

    Deck deck = Deck();
    Hand hand1 = Hand();
    Hand hand2 = Hand();
    CardType temp;
    for (int i = 0; i < 5; i++) {
        temp = deck.draw();
        hand1.setHand(i, temp);
        temp = deck.draw();
        hand2.setHand(i, temp);
    }

    playerList.push_back(Player());
    playerList.push_back(Player());
    playerList[0].setHandOfCards(&hand1);
    playerList[1].setHandOfCards(&hand2);
    playerList[1].addTerritory(&CANADA);
    playerList[0].setName("Ted");
    playerList[1].addTerritory(&US);
    playerList[1].addTerritory(&MEXICO);
    playerList[1].setName("Hillary");

    //the ammount of reinforcements a player will have
    int reinforcementCount = 0;
    //displays the countries and their units to the console
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries with these army counts: " << std::endl;
        for (Territory* territory : player.getTerritories()) {
            std::cout << territory->getName() << " with " << territory->getUnits() << std::endl;
        }
    }
    //Iterates through the players to let them add units to their country
    bool fullContinent = true;
    for (Player player : playerList) {
        if (player.getTerritories().size() == 0) { continue; }
        fullContinent = true;
        reinforcementCount = (player.getTerritories().size()) / 3;
        //checks to see for full continents (right now just NA)
        for (Territory* territory : NA.getTerritories()) {
            bool inContinent = false;
            for (Territory* territoryPlayer : player.getTerritories()) {
                if (territory->getId() == territoryPlayer->getId()) { inContinent = true; }
            }
            if (inContinent == false) { fullContinent = false; }
        }
        if (fullContinent == true) { reinforcementCount = reinforcementCount + NA.getArmyValue(); }
        if (reinforcementCount < 3) { reinforcementCount = 3; }
        std::cout << " Player " << player.getName() << " has " << reinforcementCount << " reinforcements." << std::endl;
    }

    Continent EU = Continent(1, "EU", 6);
    Territory FRANCE = Territory(5, "FRANCE", &EU);
    Territory POLAND = Territory(6, "POLAND", &EU);
    Territory SPAIN = Territory(7, "SPAIN", &EU);
    Territory GERMANY = Territory(8, "GERMANY", &EU);

    FRANCE.addAdjacentTerritory(&POLAND);
    POLAND.addAdjacentTerritory(&FRANCE);
    POLAND.addAdjacentTerritory(&GERMANY);
    GERMANY.addAdjacentTerritory(&POLAND);
    SPAIN.addAdjacentTerritory(&GERMANY);
    GERMANY.addAdjacentTerritory(&SPAIN);

    EU.addTerritory(&POLAND);
    EU.addTerritory(&FRANCE);
    EU.addTerritory(&GERMANY);
    EU.addTerritory(&SPAIN);


    playerList[0].addTerritory(&POLAND);
    playerList[0].addTerritory(&FRANCE);
    playerList[0].addTerritory(&SPAIN);
    playerList[0].addTerritory(&GERMANY);


    //the ammount of reinforcements a player will have
    reinforcementCount = 0;
    //displays the countries and their units to the console
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries with these army counts: " << std::endl;
        for (Territory* territory : player.getTerritories()) {
            std::cout << territory->getName() << " with " << territory->getUnits() << std::endl;
        }
    }
    //Iterates through the players to let them add units to their country
    bool fullContinentNA = true;
    bool fullContinentEU = true;
    for (Player player : playerList) {
        if (player.getTerritories().size() == 0) { continue; }
        fullContinentNA = true;
        fullContinentEU = true;
        reinforcementCount = (player.getTerritories().size()) / 3;
        //checks to see for full continents
        for (Territory* territory : NA.getTerritories()) {
            bool inContinent = false;
            for (Territory* territoryPlayer : player.getTerritories()) {
                if (territory->getId() == territoryPlayer->getId()) { inContinent = true; }
            }
            if (inContinent == false) { fullContinentNA = false; }
        }
        
        for (Territory* territory : EU.getTerritories()) {
            bool inContinent = false;
            for (Territory* territoryPlayer : player.getTerritories()) {
                if (territory->getId() == territoryPlayer->getId()) { inContinent = true; }
            }
            if (inContinent == false) { fullContinentEU = false; }

        }
        if (fullContinentEU == true) { reinforcementCount = reinforcementCount + EU.getArmyValue(); }
        if (fullContinentNA == true) { reinforcementCount = reinforcementCount + NA.getArmyValue(); }
        if (reinforcementCount < 3) { reinforcementCount = 3; }
        std::cout << " Player " << player.getName() << " has " << reinforcementCount << " reinforcements." << std::endl;

    }

    Territory PORTUGAL = Territory(9, "PORTUGAL", &EU);
    Territory UK = Territory(10, "UK", &EU);
    Territory TEMP = Territory(11, "TEMP", &EU);
    SPAIN.addAdjacentTerritory(&PORTUGAL);
    PORTUGAL.addAdjacentTerritory(&SPAIN);
    EU.addTerritory(&PORTUGAL);
    EU.addTerritory(&UK);
    EU.addTerritory(&TEMP);
    playerList[1].addTerritory(&PORTUGAL);
    playerList[0].addTerritory(&UK);
    playerList[0].addTerritory(&TEMP);
    //the ammount of reinforcements a player will have
    reinforcementCount = 0;
    //displays the countries and their units to the console
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries with these army counts: " << std::endl;
        for (Territory* territory : player.getTerritories()) {
            std::cout << territory->getName() << " with " << territory->getUnits() << std::endl;
        }
    }
    for (Player player : playerList) {
        if (player.getTerritories().size() == 0) { continue; }
        fullContinentNA = true;
        fullContinentEU = true;
        reinforcementCount = (player.getTerritories().size()) / 3;
        //checks to see for full continents
        for (Territory* territory : NA.getTerritories()) {
            bool inContinent = false;
            for (Territory* territoryPlayer : player.getTerritories()) {
                if (territory->getId() == territoryPlayer->getId()) { inContinent = true; }
            }
            if (inContinent == false) { fullContinentNA = false; }
        }

        for (Territory* territory : EU.getTerritories()) {
            bool inContinent = false;
            for (Territory* territoryPlayer : player.getTerritories()) {
                if (territory->getId() == territoryPlayer->getId()) { inContinent = true; }
            }
            if (inContinent == false) { fullContinentEU = false; }

        }
        if (fullContinentEU == true) { reinforcementCount = reinforcementCount + EU.getArmyValue(); }
        if (fullContinentNA == true) { reinforcementCount = reinforcementCount + NA.getArmyValue(); }
        if (reinforcementCount < 3) { reinforcementCount = 3; }
        std::cout << " Player " << player.getName() << " has " << reinforcementCount << " reinforcements." << std::endl;

    }
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries to attack: " << std::endl;
        for (Territory* territory : player.toAttack()) {
            std::cout << territory->getName() << std::endl;
        }
    }
    for (Player player : playerList) {
        std::cout << "Player " << player.getName() << " has the following countries to defend: " << std::endl;
        for (Territory* territory : player.toDefend()) {
            std::cout << territory->getName() << std::endl;
        }
    }

}

void commandsDriver(){

    string option = ""; // Initial value must be an option.
    
    cout << "Choose commands source." << endl;
    cout << "\tconsole" << endl;
    cout << "\tfile <filename>" << endl;

    cout << "\nEnter your option: " << flush;
    //cin.clear(); 
    //cin.sync();
    
    cin >> std::ws;
    std::getline(cin, option);
    cout << "Option: " << option << endl;

    vector<string> tokens = split(option, ' ');

    // read orders from the console using the CommandProcessor class 
    if(tokens[0] == "console"){
        CommandProcessor* cmdProcessor = new CommandProcessor();
        GameEngine* gameEngine = new GameEngine(cmdProcessor);
        gameEngine->Run();
    }
    // read orders from a saved text file using the FileCommandProcessorAdapter 
    else if(tokens[0] == "file" && tokens.size() > 1){
        FileLineReader* flr = new FileLineReader();
        if(flr->readFile(tokens[1])){
            FileCommandProcessorAdapter* fileCmdAdapter = new FileCommandProcessorAdapter(flr);
            GameEngine* gameEngine = new GameEngine(fileCmdAdapter);
            gameEngine->Run();
        }
    } else{
        cout << "Invalid option." << endl;
    }  
}

void logObserverDriver()
{
    cout << "\n\nLog Observer Driver" << endl;
    LogObserver* logObserver = new LogObserver();

    // Orders
    const string BRASIL_MAP = "../../maps/brasil.map";
    MapLoader loader;
    Map *brasilMap = loader.loadMap(BRASIL_MAP);

    Deck* deck = new Deck();
    Hand* hand1 = new Hand(deck);
    Hand* hand2 = new Hand(deck);

    vector<Territory*> territories = brasilMap->getTerritories();
    vector<Territory*> player1Territories;
    vector<Territory*> player2Territories;

    Player* player1 = new Player("player 1", player1Territories, new OrdersList, hand1);
    Player* player2 = new Player("player 2", player2Territories, new OrdersList, hand2);

    for (int i = 0; i < territories.size(); ++i) {
        if(i % 2 == 0){
            territories[i]->setOwner(player1);
            player1->addTerritory(territories[i]);
            territories.at(i)->setUnits(10);
        } else{
            territories[i]->setOwner(player2);
            player2->addTerritory(territories[i]);
            territories.at(i)->setUnits(5);
        }
    }
    player1->addToReinforcementPool(5);
    player2->addToReinforcementPool(1);

    cout << endl << "\n************* DEPLOY ORDER *************\n";
    Deploy* deploy1 = new Deploy(5, player1, territories[0]);
    Deploy* deploy2 = new Deploy(2, player2, territories[2]);

    // attach observer to player's orderlist and deploy orders
    player1->getOrdersList()->Attach(logObserver);
    player2->getOrdersList()->Attach(logObserver);
    deploy1->Attach(logObserver);
    deploy2->Attach(logObserver);
    // add and execute deply orders
    player1->addOrder(deploy1);
    player2->addOrder(deploy2);
    deploy1->execute();
    deploy2->execute();

    cout << endl << "\n************* ADVANCE ORDER *************\n";
    Advance* advance = new Advance(player1, 10, player1->getTerritories()[0], player2->getTerritories()[0]);
    
    // attach observer to advance order
    advance->Attach(logObserver);
    // add and execute advance order
    player1->addOrder(advance);
    advance->execute();

    // Commands & GameEngine
    Command* cmd1 = new Command();
    cmd1->Attach(logObserver);
    cmd1->saveEffect("loadmap test.map");
    Command* cmd2 = new Command();
    cmd2->Attach(logObserver);
    cmd2->saveEffect("validatemap");

    string option = "";
    cout << "Choose commands source." << endl;
    cout << "\tconsole" << endl;
    cout << "\tfile <filename>" << endl;
    cout << "\nEnter your option: " << flush;
    //cin.clear(); 
    //cin.sync();
    
    cin >> std::ws;
    std::getline(cin, option);
    cout << "Option: " << option << endl;

    vector<string> tokens = split(option, ' ');

    // read orders from the console using the CommandProcessor class 
    if(tokens[0] == "console"){
        // attach command processor and gameengine
        CommandProcessor* cmdProcessor = new CommandProcessor();
        cmdProcessor->Attach(logObserver);
        GameEngine* gameEngine = new GameEngine(cmdProcessor);
        gameEngine->Attach(logObserver);
        gameEngine->Run();
    }
    // read orders from a saved text file using the FileCommandProcessorAdapter 
    else if(tokens[0] == "file" && tokens.size() > 1){
        // attach command processor and gameengine
        FileLineReader* flr = new FileLineReader();
        if(flr->readFile(tokens[1])){
            FileCommandProcessorAdapter* fileCmdAdapter = new FileCommandProcessorAdapter(flr);
            fileCmdAdapter->Attach(logObserver);
            GameEngine* gameEngine = new GameEngine(fileCmdAdapter);
            gameEngine->Attach(logObserver);
            gameEngine->Run();
        }
    } else{
        cout << "Invalid option." << endl;
    }  
}