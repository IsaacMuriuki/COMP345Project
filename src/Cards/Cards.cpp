#include <iostream>
#include "Cards.h"
#include <stdlib.h>

using namespace std;


Card::Card()
{
	this->cardType = unassigned;
}

Card::Card(CardType cardType)
{
	this->cardType = cardType;
}


void Card::setCardType(CardType cardType)
{
	this->cardType = cardType;
}

CardType Card::getCardType()
{
	return this->cardType;
}

Deck::Deck()
{
	//Deck has 4 reinforcment, 1 diplomacy, 19 blockade, 5 airlift and 6 bomb
	for (int i = 0; i < 4; i++) {
		this->deck[i].setCardType(reinforcement);
	}
	for (int i = 4; i < 5; i++) {
		this->deck[i].setCardType(diplomacy);
	}
	for (int i = 5; i < 24; i++) {
		this->deck[i].setCardType(blockade);
	}
	for (int i = 24; i < 29; i++) {
		this->deck[i].setCardType(airlift);
	}
	for (int i = 29; i < 35; i++) {
		this->deck[i].setCardType(bomb);
	}

}


Hand::Hand()
{
	//set hand to being unassigned
	for (int i = 0; i < 5; i++) {
		this->hand[i].setCardType(unassigned);
	}
}

CardType Hand::play(Deck deck, int handPosition)
{
	CardType temporaryCardTypeHolder = this->hand[handPosition].getCardType();
	this->hand[handPosition].setCardType(unassigned);
	for (int i = 0; i < 35; i++) {
		bool cardInsertedIntoDeck = false;
		if (deck.deck[i].getCardType() == unassigned && cardInsertedIntoDeck == false) {
			deck.deck[i].setCardType(temporaryCardTypeHolder);
			cardInsertedIntoDeck = true;
		}
	}
	return temporaryCardTypeHolder;
}

void Hand::Draw(Deck deck)
{
	//Generate random number and check if it's in the deck, if not new number
	//Add card to hand and remove from the deck
	int randomCard;
	bool cardDrawn = false;
	while (cardDrawn == false) {
		randomCard = rand() % 35;
		//Check for a card that hasn't been removed from the deck
		if (deck.deck[randomCard].getCardType() != unassigned) {
			bool cardAddedtoHand = false;
			for (int i = 0; i < 5; i++) {
				if (cardAddedtoHand == false && this->hand[i].getCardType() == unassigned) {
					this->hand[i].setCardType(deck.deck[randomCard].getCardType());
					cardAddedtoHand = true;
				}
			}
			cardDrawn = true;
			deck.deck[randomCard].setCardType(unassigned);
		}
	}
}




