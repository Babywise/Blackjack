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
class Account {};