#include "pch.h"
#include "CppUnitTest.h"
#include "BlackJack.h"
#include "Deck.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackObjects
{
	TEST_CLASS(BlackJack_game) {
		TEST_METHOD(initWithThreePlayersAndDifficultyWithThreeBots)
		{
			//blackjack(player * players[], int computers, int people, int difficulty[]); // create game with x players and b computers
			//setup
			account* p1 = new account("Danny", 0, 0, "Danny");
			player* players[3];
			int difficulty[3];
			int computers = 3;
			player* play = new player(p1);
			players[0] = play;
			players[1] = play;
			players[2] = play;
			difficulty[0] = 1;
			difficulty[1] = 2;
			difficulty[2] = 3; 
			int people = 3;
			blackjack* game = new blackjack(players, computers, people, difficulty);
			int expected_players = 3;
			int expected_bots = 3;
			bool pass = false;

			//action
			if (game->computers.size() == expected_bots && game->players.size() == expected_players) {
				pass = true;
			}


			//assert
			Assert::AreEqual(true, pass);

		}
		TEST_METHOD(initWithTwoPlayersWithTwoBots)
		{
			//setup
			account* p1 = new account("Danny", 0, 0, "Danny");
			player* players[2];
			int computers = 2;
			player* play = new player(p1);
			players[0] = play;
			players[1] = play;
			int people = 2;
			blackjack* game = new blackjack(players, computers, people);
			int expected_players = 2;
			int expected_bots = 2;
			bool pass = false;
			//action
			if (game->computers.size() == expected_bots && game->players.size() == expected_players) {
				pass = true;
			}


			//assert
			Assert::AreEqual(true, pass);
		}
		TEST_METHOD(initWithWinLoss)
		{
			//setup
			float winloss = 0.34;
			blackjack* game = new blackjack(winloss);
			float expected = 0.34;
			float actual = 0;

			//action
			actual=game->computers.front()->standValue;

			//assert
			Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(dealerIsValid)
		{
			//setup
			blackjack* game = new blackjack();
			game->dealCards();
			bool pass = false;

			//action
			if (game->deal->publicCard[0]->getValue() > 1 && game->deal->publicCard[0]->getValue() < 15) {
				pass = true;
			}

			//assert
			Assert::AreEqual(true, pass);

		}
		TEST_METHOD(takeBetsFromBots)
		{
			//setup
			blackjack* game = new blackjack();
			game->dealCards();
			game->takeBets();
			double answer;
			bool passed[4];
			bool finalpass = false;


			//action				| checks all bets are in valid range
			for (int i = 0; i < 4; i++) {
				passed[i] = false;
				answer = game->deal->bets[i];
				if (answer == 5 || answer == 10 || answer == 20 || answer == 50) {
					passed[i] = true;
				}
			}
			if (passed[0] == true && passed[1] == true && passed[2] == true && passed[3] == true) {
				finalpass = true;
			}



			//assert
			Assert::AreEqual(true, finalpass);

		}
		TEST_METHOD(startGameWithBots)
		{
			//setup
			blackjack* game = new blackjack();
			game->dealCards();
			game->takeBets();
			int gamesPlayed = 0;
			int expected = game->computers.front()->games+1;

			// Action
			game->startGame();
			gamesPlayed = game->computers.front()->games;

			Assert::AreEqual(expected, gamesPlayed);
		}
		TEST_METHOD(dealCards)
		{
			//setup
			blackjack* game = new blackjack();
			card* empty = game->computers.front()->publicCard[0];
			game->dealCards();
			card* answer = game->computers.front()->publicCard[0];
			Assert::AreNotEqual(empty->getValue(), answer->getValue());
			
		}
		TEST_METHOD(dealBets)
		{

		}
	};
	TEST_CLASS(AI) {
	};

	TEST_CLASS(Player) {
	};

	TEST_CLASS(Dealer) {
		TEST_METHOD(getcard)
		{
			//setup
			dealer* deal = new dealer;
			deck* DECK = new deck(2);
			int non_expected = deal->getCardTotal();
			int result = 0;

			//action
			deal->getCard(DECK->drawCard());
			result =deal->getCardTotal();

			//assert
			Assert::AreNotEqual(non_expected, result);

		}
		TEST_METHOD(taketurn)
		{
			//setup
			dealer* deal = new dealer;
			bool pass = false;
			string options[4] = { "h","b","j","k" };
			string result = deal->turn(options,4);
			//action

			if (result == options[0] || result == options[1] || result == options[2] || result == options[3]) {
				pass = true;
			}

			//assert
			Assert::AreEqual(true, pass);
		}
		TEST_METHOD(getcardtotal)
		{
			//setup
			dealer* deal = new dealer;
			card* CARD = new card('s', 3, 'b');
			deal->getCard(CARD);
			int expected = 3;
			int actual = 0;

			//action
			actual = deal->getCardTotal();

			//assert
			Assert::AreEqual(expected, actual);

		}
		TEST_METHOD(reset)
		{
			//setup
			dealer* deal = new dealer;
			card* CARD = new card('s', 3, 'b');
			deal->getCard(CARD);
			int expected = 0;
			int actual = 4;

			//action
			actual = deal->getCardTotal();
			deal->reset();
			actual = deal->getCardTotal();

			//assert
			Assert::AreEqual(expected, actual);
		}
	};
}