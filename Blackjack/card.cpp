#include "card.h"

string card::getSuit()
{
	switch (this->suit) {
	case 'h':
		return "Heart";
		break;
	case 'd':
		return "Diamond";
		break;
	case 's':
		return "Spade";
		break;
	case 'c':
		return "Club";
		break;
	default:
		return "Error";
		break;
	}
}

void card::print() {
	if (this->value != NULL) {
		switch (this->value) {
		case 11:
			cout << "Card : " << this->getSuit() << " " << "Jack" << " " << this->getColour() << "\n";
			break;
		case 12:
			cout << "Card : " << this->getSuit() << " " << "Queen" << " " << this->getColour() << "\n";
			break;
		case 13:
			cout << "Card : " << this->getSuit() << " " << "King" << " " << this->getColour() << "\n";
			break;
		case 14:
			cout << "Card : " << this->getSuit() << " " << "Ace" << " " << this->getColour() << "\n";
			break;
		default:
			cout << "Card : " << this->getSuit() << " " << this->getValue() << " " << this->getColour() << "\n";
			break;

		}
	}
}
int card::getValue() {
	if (this == NULL) {
		return 0;
	}
	else {
		return this->value;
	}
}


string card::getColour() {
	if (this->colour == 'r') {
		return "Red";
	}
	else if (this->colour == 'b') {
		return "Black";
	}
	else {
		return "Error";
	}
}


card::card(char suit, int value, char colour) {
	this->suit = suit;
	this->value = value;
	this->colour = colour;
}