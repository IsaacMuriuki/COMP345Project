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
		Card(const Card &card);
		Card(CardType cardType);
		//Standard getter and setters
		void setCardType(CardType cardType);
		CardType getCardType();
		CardType play();
};


class Deck {
	//Need to add getter and setters
	private:
		Card deck[35];
	public:
		Deck();
		Deck(const Deck &deck);
		CardType draw();
		void reshuffleIntoDeck(CardType cardType);

		
};

class Hand {

private:
    /*moved this to public so i can access it from player easier - see card channel on discord
     *
	//Hand size is limited to 5 at the moment
	Card hand[5];
*/
public:
    //Hand size is limited to 5 at the moment
    Card hand[5];
	Hand();
	Hand(const Hand& hand);
	Card getHand(int index);
	void setHand(int index, CardType cardType);
};

#endif