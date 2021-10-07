#ifndef CARDS_H
#define CARDS_H
#define GRANDPARENT_H

#include <iostream>
using namespace std;

//Declaring the CardType enum, values are stored as ints for now
enum CardType{ bomb, reinforcement, blockade, airlift, diplomacy, unassigned };

class Card {

	private:
	CardType cardType;
	public:
		//The default constructor is for the arrays of cards for the cards and hands
		Card();
		Card(CardType cardType);
		//Standard getter and setters
		void setCardType(CardType cardType);
		CardType getCardType();
};


class Deck {
	//Need to add getter and setters
	private:
	public:
		Card deck[35];
		Deck();
		
};

class Hand {

private:
	//Hand size is limited to 5 at the moment

public:
	Card hand[5];
	Hand();
	//The hand draws and plays cards
	//Need to add getter and setters and a maybe a display function
	CardType play(Deck deck, int handPosition);
	void Draw(Deck deck);

};

#endif