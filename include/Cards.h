#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Declaring the CardType enum, values are stored as ints for now
enum CardType{ bomb, reinforcement, blockade, airlift, diplomacy, unassigned };
//Deck has 4 reinforcment, 1 diplomacy, 19 blockade, 5 airlift and 6 bomb
static int reinforcementCardAmount = 4;
static int diplomacyCardAmount = 1;
static int blockadeCardAmount = 19;
static int airliftCardAmount = 5;
static int bombCardAmount = 6;
static int sizeDeck = reinforcementCardAmount + diplomacyCardAmount + blockadeCardAmount + airliftCardAmount + bombCardAmount;

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
		string toString() const;
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
		int size();

		
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
	int size();
};
