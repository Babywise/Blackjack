#pragma once
#include "card.h"
#include <queue>
#define CARD_START_VALUE 2
#define CARD_END_VALUE 15 // 2 - 10inclusive = 9 + jack queen king ace = 4   | 9 + 4 = 13
#define SUITS 4
#define DEFAULT_SHUFFLES_PER_DECK 6
#define CARDS_PER_DECK 52

class deck {
public:
	void shuffle(int shuffles); // shuffle deck x amount of times
	void shuffle(); // shuffle the deck once
	deck(); // create a single deck
	deck(int decks); // create a deck with x decks
	card* drawCard();
	void reset();
	void returnCard(card* card);
	~deck();
private:
	deque<card*> DECK;
	deque<card*> used;

};