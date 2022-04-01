#include "Deck.h";


void deck::shuffle(int shuffles) {
	for (int i = 0; i < shuffles; i++) {
		random_shuffle(this->DECK.begin(), this->DECK.end());
	}

}
void deck::shuffle() {
	for (int i = 0; i < DEFAULT_SHUFFLES_PER_DECK; i++) {
		random_shuffle(this->DECK.begin(), this->DECK.end());
	}

}
deck::deck() {
	card* c;
	deque<card*> d;
	// generate deck
	for (int i = CARD_START_VALUE; i < CARD_END_VALUE; i++) { // create card of each value
		for (int b = 0; b < SUITS; b++) { // create a card of each suit
			switch (b) {
			case 0:
				c = new card('d', i, 'r');
				this->DECK.push_back(c);
				break;
			case 1:
				c = new card('c', i, 'b');
				this->DECK.push_back(c);
				break;
			case 2:
				c = new card('h', i, 'r');
				this->DECK.push_back(c);
				break;
			case 3:
				c = new card('s', i, 'b');
				this->DECK.push_back(c);
				break;
			}// switch
		} // for suits
	} // for values
	this->shuffle(DEFAULT_SHUFFLES_PER_DECK);
}
deck::deck(int decks) {
	card* c;
	// generate x decks
	for (int x = 0; x < decks; x++) {
		for (int i = CARD_START_VALUE; i < CARD_END_VALUE; i++) { // create card of each value
			for (int b = 0; b < SUITS; b++) { // create a card of each suit
				switch (b) {
				case 0:
					c = new card('d', i, 'r');
					this->DECK.push_back(c);
					break;
				case 1:
					c = new card('c', i, 'b');
					this->DECK.push_back(c);
					break;
				case 2:
					c = new card('h', i, 'r');
					this->DECK.push_back(c);
					break;
				case 3:
					c = new card('s', i, 'b');
					this->DECK.push_back(c);
					break;
				}// switch
			} // for suits
		} // for values
	} // for x decks
	this->shuffle(DEFAULT_SHUFFLES_PER_DECK * decks);
}
card* deck::drawCard() {
	if (!this->DECK.empty()) {
		card* temp = this->DECK.front();
		this->used.push_back(this->DECK.front());
		this->DECK.pop_front();
		return temp;
	}
	else {
		card* empty = new card('n', 0, 'n');
		return empty;
	}
}

void deck::reset() {
	while (!this->used.empty()) {
		this->DECK.push_back(this->used.front());
		this->used.pop_front();
	}
}

void deck::returnCard(card* card) {
	for (int i = 0; i < this->used.size(); i++) {
		if (card == this->used[i]) {
			this->DECK.push_back(card);
			this->used.erase(this->used.begin() + (i - 1));
		}
	}
}

deck::~deck()
{
	while (!this->DECK.empty()) {
		delete(this->DECK.front());
		this->DECK.pop_front();
	}
	while (!this->used.empty()) {
		delete(this->used.front());
		this->used.pop_front();
	}
}
