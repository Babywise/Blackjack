#pragma once

const int externalMaxPublicCards = 10;
const int externalMaxPlayers = 10;
const int numberOfTables = 10;
const int maxOptions = 10;

class Card {
public:
	int num;

	Card() { num = 0; };
};
class account { 
	string n;
	int a;
	int b;
	string n2;
public: 
	account(string n, int a , int b , string n2) {
		this->n = n;
		this->a = a;
		this->b = b;
		this->n2 = n2;
	}
};