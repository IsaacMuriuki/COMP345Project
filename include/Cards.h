#pragma once

#include <iostream>
#include <vector>

using namespace std;

//Declaring the CardType enum, values are stored as ints for now
enum CardType{ bomb, reinforcement, blockade, airlift, diplomacy, unassigned };
static int sizeDeck = 35;
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
		friend ostream& operator << (ostream& out, const Card& c);
		friend istream& operator >> (istream& in, const Card& c);
};


class Deck {
	//Need to add getter and setters
	private:
		vector<Card> deck;
	public:
		Deck();
		Deck(const Deck &deck);
		CardType draw();
		void reshuffleIntoDeck(CardType cardType);

		
};

class Hand {

private:
	//Hand size is limited to 5 at the moment
	vector<Card> hand;
public:
	Hand();
	Hand(const Hand& hand);
	Card getHand(int index);
	void setHand(int index, CardType cardType);
};

