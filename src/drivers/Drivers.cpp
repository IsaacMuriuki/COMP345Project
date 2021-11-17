#include "Drivers.h"
#include "Cards.h"
#include "GameEngine.h"
#include "CommandProcessor.h"
#include "map.h"
#include "Orders.h"
#include "OrdersList.h"
#include "Player.h"
#include "LoggingObserver.h"

#include <stdio.h>
#include <iostream>
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

    vector<Territory*> territories = brasilMap->getTerritories();
    vector<Territory*> player1Territories;
    vector<Territory*> player2Territories;

    Player* player1 = new Player("player 1", player1Territories, new OrdersList, hand);
    Player* player2 = new Player("player 2", player2Territories, new OrdersList, hand1);

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
    Blockade* blockade = new Blockade(player1, player1->getTerritories()[0]);
    player1->addOrder(blockade);
    Territory* t = player1->getTerritories()[0];
    cout << "Number of armies in " << t->getName() << " before blockade order : " << t->getUnits() << ". Owner : " << t->getOwner()->getName() << endl;
    blockade->execute();
    cout << "Number of armies in " << t->getName() << " after blockade order : " << t->getUnits() << ". Owner : " << t->getOwner()->getName() << endl;


    cout << endl << "\n************* AIRLIFT ORDER *************\n";
    cout << endl << "\n************* BOMB ORDER *************\n";
}

void playerDriver(){
    Territory* t1 = new Territory(1, "Kenya", new Continent(1, "Africa", 2));
    Territory* t2 = new Territory(2, "Somalia", new Continent(2, "Africa", 2));
    Territory* t3 = new Territory(3, "South Africa", new Continent(3, "Africa", 3));
    Territory* t4 = new Territory(4, "Netherlands", new Continent(4, "Europe", 4));
    Territory* t5 = new Territory(5, "Belgium", new Continent(5, "Europe", 5));
    Territory* t6 = new Territory(6, "England", new Continent(6, "Europe", 5));

    vector<Territory*> territories;
    territories.push_back(t1); territories.push_back(t2); territories.push_back(t3); territories.push_back(t4); territories.push_back(t5); territories.push_back(t6);

    OrdersList* ordersList = new OrdersList();
    Hand* handOfCards = new Hand();

    // Creating new Player object
    Player *player = new Player("Isaac", territories, ordersList, handOfCards);

    // Player info output
    std::cout << *player << std::endl;

    // Player's toDefend() method which returns the first half of their territories
    vector<Territory *> toDefendResult = player->toDefend();

    std::cout << "\nResult of calling toDefend() on player: (first half of their territories)" << std::endl;
    for (auto *territory : toDefendResult)
    {
        std::cout << *territory << std::endl;
    }

    // Player's toAttack() method which returns the first half of their territories
    vector<Territory *> toAttackResult = player->toAttack();

    std::cout << "\nResult of calling toAttack() on player: (second half of their territories)" << std::endl;
    for (auto *territory : toAttackResult)
    {
        std::cout << *territory << std::endl;
    }

    // Player's issueOrder()
    player->issueOrder();

    std::cout << "Orders issued : " << std::endl;
    for (int i = 0; i < player->getOrdersList()->size(); ++i)
    {
        std::cout << *player->getOrdersList()->get(i) << endl;
    }

    // Player info output
    std::cout << "\nPlayer data after orders created: " << std::endl;
    std::cout << *player << std::endl;

    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete t6;
    delete player;
}

void mapDriver()
{
    const string MAPS_FOLDER = "../../maps/"; // for mac this works ->   const string MAPS_FOLDER = "../maps";
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

void cardsDriver()
{
    //String values of Card Types
    //bomb, reinforcement, blockade, airlift, diplomacy, unassigned
    string cardTypesText[] =
            {
                    "bomb",
                    "reinforcement",
                    "blockade",
                    "airlift",
                    "diplomacy",
                    "unassigned"
            };
    //Creating a deck and a hand
    Deck deck;
    Hand hand;
    CardType temp = unassigned;
    //Drawing the cards from the deck into the hand and playing the cards
    cout << "The hand is created and has no cards in yet" << endl;


    cout << "Cards are being drawn at random to the hand" << endl;
    for (int i = 0; i < 5; i++)
    {
        temp = deck.draw();
        hand.setHand(i, temp);
    }

    for (int i = 0; i < 5; i++)
    {
        //Using an array of strings to print out the text value of the cards
        temp = hand.getHand(i).play();
        deck.reshuffleIntoDeck(temp);
        cout << cardTypesText[temp];
        cout << endl;
    }
}

void gameEngineDriver()
{
    GameEngine gameEngine;
    gameEngine.Run();
}

void commandsDriver()
{

    cout << "Menu - COMP 345 Project - Part 1 - Team DN7" << endl;
    cout << "Here are the driver options for execution:" << endl;

    string option = ""; // Initial value must be an option.
    string options = "ABCDEF";

    if (options.find(option) != options.npos)
    {
        cout << "Choose commands source." << endl;
        cout << "\t-console" << endl;
        cout << "\t-file <filename>" << endl;
    }

    std::cout << "Enter your option: ";
    cout.flush();
    cin >> option;

    // read orders from the console using the CommandProcessor class
    if (option == "console")
    {
        CommandProcessor processor;
    }
    // read orders from a saved text file using the FileCommandProcessorAdapter
    else if(option == "filename"){

    } else{
        cout << "Invalid option." << endl;
    }

    cout << "End of the commands driver." << endl;

    // 3) commands that are invalid in the current game state are rejected, and valid commands result in the correct effect and state change
}

void logObserverDriver()
{
   /* cout << "\n\nHello" << endl;
    LogObserver *logObserver = new LogObserver();
    vector<Territory *> territories;
    Player *player = new Player("Henry", territories, new OrdersList(), new Hand());
    Airlift *airlift = new Airlift();
    Negotiate *negotiate = new Negotiate();
    Deploy *deploy = new Deploy(2);

    // attach player's orderlist and orders to observer
    player->getOrdersList()->Attach(logObserver);
    airlift->Attach(logObserver);
    negotiate->Attach(logObserver);
    deploy->Attach(logObserver);

    // add orders to player's orderlist
    player->getOrdersList()->add(airlift);
    player->getOrdersList()->add(negotiate);
    player->getOrdersList()->add(deploy);

    // execute all of player's valid orders
    OrdersList *orderList = player->getOrdersList();
    for (int i = 0; i < orderList->size(); i++)
    {
        orderList->get(i)->execute();
    }*/
}