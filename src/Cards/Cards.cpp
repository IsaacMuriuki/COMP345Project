#include <iostream>
#include "Cards.h"
#include <stdlib.h>

using namespace std;


Card::Card()
{
	this->setCardType(unassigned);
}

Card::Card(CardType cardType)
{
	this->setCardType(cardType);
}


void Card::setCardType(CardType cardType)
{
	this->cardType = cardType;
}

CardType Card::getCardType()
{
	return this->cardType;
}

Card::Card(const Card &card)
{

	this->cardType = card.cardType;

}

CardType Card::play()
{
	CardType temporaryCardTypeHolder = this->getCardType();
	this->setCardType(unassigned);
	return temporaryCardTypeHolder;
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

void Deck::reshuffleIntoDeck(CardType cardType)
{
	int randomCard;
	bool cardShuffledIn = false;
	int countAssigned = 0;

	//Check to see if all the cards in the deck already exist, if so it will skip the loop to reassign the card
	for (int i = 0; i < 35; i++) {
		if (this->deck[i].getCardType() != unassigned) {
			countAssigned = countAssigned + 1;
		}
	}

	if (countAssigned == 35) {
		cardShuffledIn = true;
	}

	//This section randomly shuffles the card back into the deck
	while (cardShuffledIn == false) {
		randomCard = rand() % 35;
		//Check for a card that hasn't been removed from the deck
		if (this->deck[randomCard].getCardType() == unassigned) {			
			this->deck[randomCard].setCardType(cardType);
			cardShuffledIn = true;
		}
	}
}

CardType Deck::draw()
{
	//Generate random number and check if it's in the deck, if not new number
	//Add card to hand and remove from the deck
	int randomCard;
	bool cardDrawn = false;
	int countUnassigned = 0;
	CardType drawnCard = unassigned;
	//Check to see if all the cards in the deck already exist, if so it will skip the loop to reassign the card
	for (int i = 0; i < 35; i++) {
		if (this->deck[i].getCardType() == unassigned) {
			countUnassigned = countUnassigned + 1;
		}
	}

	if (countUnassigned == 35) {
		cardDrawn = true;
	}

	while (cardDrawn == false) {
		randomCard = rand() % 35;
		//Check for a card that hasn't been removed from the deck
		if (this->deck[randomCard].getCardType() != unassigned) {
			drawnCard = this->deck[randomCard].getCardType();
			this->deck[randomCard].setCardType(unassigned);
			cardDrawn = true;
		}
		
	}
	return drawnCard;
}

Deck::Deck(const Deck& deck)
{
	for (int i = 0; i < 35; i++) {
		this->deck[i] = deck.deck[i];
	}
	
}


Hand::Hand()
{
	//set hand to being unassigned
	for (int i = 0; i < 5; i++) {
		this->hand[i].setCardType(unassigned);
	}
}

Card Hand::getHand(int index)
{
	return this->hand[index];
}

void Hand::setHand(int index, CardType cardType)
{
	this->hand[index].setCardType(cardType);
}


Hand::Hand(const Hand& hand)
{
	for (int i = 0; i < 5; i++) {
		this->hand[i] = hand.hand[i];
	}
}







