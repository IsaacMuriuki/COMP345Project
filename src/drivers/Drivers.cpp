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
    Player* player = new Player("Isaac", territories, ordersList, handOfCards);

    // Player info output
    std::cout << *player << std::endl;

    // Player's toDefend() method which returns the first half of their territories
    vector<Territory*> toDefendResult = player->toDefend();

    std::cout << "\nResult of calling toDefend() on player: (first half of their territories)" << std::endl;
    for(auto* territory: toDefendResult)
    {
        std::cout<< *territory << std::endl;
    }

    // Player's toAttack() method which returns the first half of their territories
    vector<Territory*> toAttackResult = player->toAttack();

    std::cout << "\nResult of calling toAttack() on player: (second half of their territories)" << std::endl;
    for(auto* territory: toAttackResult)
    {
        std::cout<< *territory << std::endl;
    }

    // Player's issueOrder()
    player->issueOrder();

    std::cout << "Orders issued : " << std::endl;
    for(int i =0; i < player->getOrdersList()->size(); ++i){
        std::cout << *player->getOrdersList()->get(i) << endl;
    }

    // Player info output
    std::cout << "\nPlayer data after orders created: " << std::endl;
    std::cout << *player << std::endl;

    delete t1; delete t2; delete t3; delete t4; delete t5; delete t6;
    delete player;
}

void ordersDriver() {
    std::cout << "Creating all order instances." << std::endl;
    Order* deploy = new Deploy(8);
    Order* advance = new Advance(4);
    Order* bomb = new Bomb();
    Order* blockade = new Blockade();
    Order* airlift = new Airlift();
    Negotiate* negotiate = new Negotiate();
    Deploy* deploy2 = new Deploy(2);
    Order* invalid = new Advance(-1);

    std::cout << "Creating OrdersList." << std::endl;
    OrdersList* list = new OrdersList();

    std::cout << std::endl;
    std::cout << "Adding to OrdersList " << std::endl;
    std::cout << "Adding Deploy order (" << (deploy->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(deploy);
    std::cout << "Adding Advance order (" << (advance->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(advance);
    std::cout << "Adding Bomb order (" << (bomb->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(bomb);
    std::cout << "Adding Blockade order (" << (blockade->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(blockade);
    std::cout << "Adding Airlift order (" << (airlift->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(airlift);
    std::cout << "Adding Negotiate order (" << (negotiate->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(negotiate);
    std::cout << "Adding a second Deploy order (" << (deploy2->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(deploy2);
    std::cout << "Adding the first Deploy order again (" << (deploy->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(deploy);
    std::cout << "Adding an invalid order (" << (invalid->validate() ? "valid" : "invalid" ) << ")." << std::endl;
    list->add(invalid);
    std::cout << "OrdersList has " << list->size() << " orders." << std::endl;

    std::cout << std::endl;
    std::cout << "Execute " << std::endl;
    std::cout << "Executing deploy order." << std::endl;
    deploy->execute();
    std::cout << "Executing advance order." << std::endl;
    advance->execute();
    std::cout << "Executing invalid order." << std::endl;
    invalid->execute();

    std::cout << std::endl;
    std::cout << "Stream operator " << std::endl;
    std::cout << "Print out the advance order." << std::endl;
    std::cout << *list->get(1) << std::endl;
    std::cout << "Print out the bomb order." << std::endl;
    std::cout << *list->get(2) << std::endl;
    std::cout << "Print out the second deploy order." << std::endl;
    std::cout << *list->get(6) << std::endl;
    std::cout << "Print out the third deploy order." << std::endl;
    std::cout << *list->get(7) << std::endl;

    std::cout << std::endl;
    std::cout << "Output " << std::endl;
    std::cout << "Remove advance order (index = 1)." << std::endl;
    list->remove(1);
    std::cout << "OrdersList is now size " << list->size() << std::endl;
    std::cout << "OrdersList at index 1 has '" << *list->get(1) << "'." << std::endl;
    std::cout << "Remove order at index = 100." << std::endl;
    list->remove(100);
    std::cout << "OrdersList is now size " << list->size() << std::endl;

    std::cout << std::endl;
    std::cout << "Moving indexes 1 (" << *list->get(1) << ") and 5 (" << *list->get(5) << ")." << std::endl;
    list->move(1, 5);
    std::cout << "Now, OrdersList have '" << *list->get(1) << "' at index 1 and and '" << *list->get(5) << "' at index 5." << std::endl;
}

void mapDriver() {
    const string MAPS_FOLDER = "../../maps/"; // for mac this works ->   const string MAPS_FOLDER = "../maps";
    MapLoader loader;

    // read all files in valid maps folder
    try{
        for (const auto & entry : fs::directory_iterator(MAPS_FOLDER)){
            cout << "\nLoading map: " << entry.path().filename() << endl;
            cout << "Validating..." << endl;
            Map* m = loader.loadMap(entry.path().string());
            // check if file is valid
            if(m != NULL){
                // check if map is valid
                if(m->validate()){
                    cout << *m << endl;
                } else {
                    cout << "Invalid map" << endl;
                }
            } else {
                cout << "The file " << entry.path().filename() << " is not a valid .map file." << endl;
            }
        }
    } catch(const fs::filesystem_error){
        cout << "\nInvalid folder..." << endl;
    }
}

void cardsDriver() {
    //String values of Card Types
    //bomb, reinforcement, blockade, airlift, diplomacy, unassigned
    char* cardTypesText[] =
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
    for (int i = 0; i < 5; i++) {
        cout << hand.getHand(i).toString() << endl;;
    }

    cout << "Cards are being drawn at random to the hand" << endl;
    for (int i = 0; i < 5; i++) {
        temp = deck.draw();
        hand.setHand(i, temp);
    }


    for (int i = 0; i < 5; i++) {
        //Using an array of strings to print out the text value of the cards
        temp = hand.getHand(i).play();
        deck.reshuffleIntoDeck(temp);
        cout << cardTypesText[temp];
        cout << endl;
    }
}

void gameEngineDriver(){
    GameEngine gameEngine;
    gameEngine.Run();
}

void commandsDriver(){

    cout << "Menu - COMP 345 Project - Part 1 - Team DN7" << endl;
    cout << "Here are the driver options for execution:" << endl;

    string option = ""; // Initial value must be an option.
    string options = "ABCDEF";

    if (options.find(option) != options.npos) {
        cout << "Choose commands source." << endl;
        cout << "\t-console" << endl;
        cout << "\t-file <filename>" << endl;
    }

    std::cout << "Enter your option: ";
    cout.flush();
    cin >> option;

    // read orders from the console using the CommandProcessor class 
    if(option == "console"){
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

void logObserverDriver(){
    cout << "\n\nHello" << endl;
    
}