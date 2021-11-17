#include <iostream>
#include "Cards.h"

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



string Card::toString() const
{
	string cardTypesText[] =
	{
		"bomb",
		"reinforcement",
		"blockade",
		"airlift",
		"diplomacy",
		"unassigned"
	};
	return cardTypesText[this->cardType];
}

Deck::Deck()
{
	//Deck has 4 reinforcment, 1 diplomacy, 19 blockade, 5 airlift and 6 bomb
	for (int i = 0; i < reinforcementCardAmount; i++) {
		this->deck.push_back(new Card(reinforcement));
	}
	for (int i = 0; i < diplomacyCardAmount; i++) {
		this->deck.push_back(new Card(diplomacy));
	}
	for (int i = 0; i < blockadeCardAmount; i++) {
		this->deck.push_back(new Card(blockade));
	}
	for (int i = 0; i < airliftCardAmount; i++) {
		this->deck.push_back(new Card(airlift));
	}
	for (int i = 0; i < bombCardAmount; i++) {
		this->deck.push_back(new Card(bomb));
	}
}

void Deck::reshuffleIntoDeck(CardType cardType)
{
	int randomCard;
	bool cardShuffledIn = false;
	int countAssigned = 0;

	//Check to see if all the cards in the deck already exist, if so it will skip the loop to reassign the card
	for (int i = 0; i < sizeDeck; i++) {
		if (this->deck[i]->getCardType() != unassigned) {
			countAssigned = countAssigned + 1;
		}
	}

	if (countAssigned == sizeDeck) {
		cardShuffledIn = true;
	}

	//This section randomly shuffles the card back into the deck
	while (cardShuffledIn == false) {
		randomCard = rand() % sizeDeck;
		//Check for a card that hasn't been removed from the deck
		if (this->deck[randomCard]->getCardType() == unassigned) {
			this->deck[randomCard]->setCardType(cardType);
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

    for (int i = 0; i < sizeDeck; i++) {
		if (this->deck.at(i)->getCardType() == unassigned) {
			countUnassigned = countUnassigned + 1;
		}
	}

	if (countUnassigned == sizeDeck) {
		cardDrawn = true;
	}

	while (cardDrawn == false) {
		randomCard = rand() % sizeDeck;
		//Check for a card that hasn't been removed from the deck
		if (this->deck[randomCard]->getCardType() != unassigned) {
			drawnCard = this->deck[randomCard]->getCardType();
			this->deck[randomCard]->setCardType(unassigned);
			cardDrawn = true;
		}
		
	}
	return drawnCard;
}

Deck::Deck(const Deck& deck)
{
	for (int i = 0; i < deck.deck.size(); i++) {
		this->deck.push_back(deck.deck[i]);
	}
	
}

int Deck::size() {
    return deck.size();
}

vector<Card*> Deck::getDeckOfCards() {return deck;}

Hand::Hand()
{
	//set hand to being unassigned
	for (int i = 0; i < 5; i++) {
		this->hand.push_back(new Card(unassigned));
	}
    deck = nullptr;
}

Hand::Hand(Deck* deck) : deck(deck){}

Deck *Hand::getDeck() {return deck;}

Card Hand::getHand(int index)
{
	return *this->hand[index];
}

void Hand::setHand(int index, CardType cardType)
{
	this->hand[index]->setCardType(cardType);
}

void Hand::addCardToHand(CardType card) {
    hand.push_back(new Card(card));
}


Hand::Hand(const Hand& hand)
{
	for (int i = 0; i < hand.hand.size(); i++) {
		this->hand.push_back(hand.hand[i]);
	}
    this->deck = hand.deck;
}

ostream& operator<<(ostream& out, const Card& c)
{
	out << c.toString();
	return out;
}

istream& operator>>(istream& in, const Card& c)
{
	std::cout << "Choose a card type";
	in >> c.cardType;
	return in;
}

int Hand::size() {
    return hand.size();
}


