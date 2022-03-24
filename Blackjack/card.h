#pragma once
#include <string>
using namespace std;
#include <stdio.h>
#include <iostream>
#define MAX_CARD 14
class card {
public:
	string getSuit();
	int getValue();
	string getColour();
	void print();
	card(char suit, int value, char colour);
	card() { suit = 'n', value = 0, colour = 'n'; };
private:
	char suit;
	int value;
	char colour;
};


