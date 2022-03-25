#pragma once
#include "deck.h"
#include "Account.h"
#include "PacketManager.h"
#include <thread>
#include <chrono>
#include <winsock.h>
using namespace std;
using namespace std::this_thread;
#define MIN_PLAYERS 4
#define MAX_PLAYERS 8
#define BROKEVALUE 21
#define MAX_PUBLIC_CARDS 10
#define CARDS_TO_DEAL 2
#define NUMBER_OF_DECKS 4
#define SAVETIME 20
#define NUMBEROFTABLES 10
#define MAX_OPTIONS 4
class dealer {
public:
	bool getCard(card* card);
	string turn(string options[], int length);
	int getCardTotal();
	string name;
	char status = 'i';
	void reset();
	double bets[MAX_PLAYERS];
	card* publicCard[MAX_PUBLIC_CARDS];
private:
	card* hiddenCard;
};


class player {
public:
	account* acc;
	void reset();
	bool getCard(card* card);
	string name;
	string turn(string options[], int length);
	int getCardTotal();
	char status = 'i';
	card* publicCard[MAX_PUBLIC_CARDS] = {};
	player(account* acc);
private:
	card* hiddenCard;
};


class AI {
public:
	bool getCard(card* card);
	float standValue = 0.26; // hard setting
	string name;
	int difficulty = 3; // hard
	void reset();
	string turn(string options[], int length);
	int getCardTotal();
	char status = 'i';
	int wins;
	int games;
	float funds = 500;
	card* publicCard[MAX_PUBLIC_CARDS];
private:
	card* hiddenCard;
};


class blackjack {
public:
	dealer* deal = new dealer();
	queue<player*> players;
	queue<player*> playerSave;
	queue<player*> incomingPlayers;
	queue<AI*> computers;
	thread saveThread;
	void save();
	deck* DECK = new deck(NUMBER_OF_DECKS);
	bool terminated = false;
	void startGame(); // wait for defined min players(socket connections) then play | wait for one player then fill with computers
	void dealCards();
	void takeBets();
	void dealBets();
	blackjack(player* players[], int computers, int people, int difficulty[]); // create game with x players and b computers
	blackjack(player* players[], int computers, int people); // create game with x players and b computers
	blackjack(float winloss);
	blackjack();
	int loss;
	int win;
	~blackjack();
};


void SAVE(blackjack* game);