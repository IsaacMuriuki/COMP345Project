#include <iostream>
#include "Drivers.h"
#include "Cards.h"

void CardsDriver::demo() {
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
        cout << cardTypesText[hand.getHand(i).getCardType()] << endl;;
    }

    cout << "Cards are being drawn at random to the hand" << endl;
    for (int i = 0; i < 5; i++) {
        temp = deck.draw();
        hand.setHand(i, temp);
    }


    for (int i = 0; i < 5; i++) {
        //Using an array of strings to print out the text value of the cards
        cout << cardTypesText[hand.getHand(i).play()];
        cout << endl;
    }
}
