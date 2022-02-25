#pragma once
#include <string>
using namespace std;
#include <stdio.h>
#include <iostream>

class card {
public:
	string getSuit();
	int getValue();
	string getColour();
	void print();
	card(char suit, int value, char colour);
private:
	char suit;
	int value;
	char colour;
};


