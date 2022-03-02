#include "pch.h"
#include "CppUnitTest.h"
#include "Deck.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackObjects
{
	TEST_CLASS(Misc) {
		TEST_METHOD(printCard)
		{
			deck* d = new deck();
			card* c = d->drawCard();
			while (c->getValue() != 0) {
				c->print();
				c = d->drawCard();
			}
		}
		TEST_METHOD(deleteDeck)
		{
			deck* d = new deck();
			card* c = d->drawCard();
			delete(d);
		}
		TEST_METHOD(deleteCard)
		{
			deck* d = new deck();
			card* c = d->drawCard();
			delete(c);
		}

	};
	TEST_CLASS(Cards)
	{
	public:
		
		TEST_METHOD(getSuitDiamond)
		{
			//setup
			card* diamond = new card('d',3,'r');
			string expected = "Diamond";

			//act
			string actual = diamond->getSuit();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getSuitClub)
		{
			//setup
			card* club = new card('c', 3, 'b');
			string expected = "Club";

			//act
			string actual = club->getSuit();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getSuitSpade)
		{
			//setup
			card* spade = new card('s', 3, 'b');
			string expected = "Spade";

			//act
			string actual = spade->getSuit();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getSuitHeart)
		{
			//setup
			card* heart = new card('h', 3, 'r');
			string expected = "Heart";

			//act
			string actual = heart->getSuit();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getValueNegitive)
		{
			//setup
			card* heart = new card('h', -2, 'r');
			int expected = 0;

			//act
			int actual = heart->getValue();

			//assert
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(getValueFour)
		{
			//setup
			card* heart = new card('h', 4, 'r');
			int expected = 4;

			//act
			int actual = heart->getValue();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getValueOverMax)
		{
			//setup
			card* heart = new card('h', 24, 'r');
			int expected = 0;

			//act
			int actual = heart->getValue();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getColourRed)
		{
			//setup
			card* heart = new card('h', 8, 'r');
			string expected = "Red";

			//act
			string actual = heart->getColour();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(getColourBlack)
		{
			//setup
			card* heart = new card('h', 8, 'b');
			string expected = "Black";

			//act
			string actual = heart->getColour();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(setColourInvalid)
		{
			//setup
			card* heart = new card('h', 8, 's');
			string expected = "Error";

			//act
			string actual = heart->getColour();

			//assert
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(setSuitInvalid)
		{
			//setup
			card* heart = new card('l', 8, 'r');
			string expected = "Error";

			//act
			string actual = heart->getSuit();

			//assert
			Assert::AreEqual(expected, actual);
		}
	};
	TEST_CLASS(Deck) {
	public:
		TEST_METHOD(initializer_One_Deck_13_Diamonds) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			if (c == nullptr) {

			}
			string suit = "Diamond";
			queue<int> values;
			int expected_value = 13;



			//act
			for (int i = 0; i < CARDS_PER_DECK; i++) {
				if (c->getSuit() == suit) {
					if (c->getValue() >= 2 && c->getValue() < CARD_END_VALUE) {
						values.push(c->getValue());
				}
				}
				c = d->drawCard();
			}


			//assert
			Assert::AreEqual(expected_value, (int)values.size());
		}

		TEST_METHOD(initializer_One_Deck_13_Clubs) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			string suit = "Club";
			queue<int> values;
			int expected_value = 13;



			//act
			for (int i = 0; i < CARDS_PER_DECK; i++) {
				if (c->getSuit() == suit) {
					if (c->getValue() >= 2 && c->getValue() < CARD_END_VALUE) {
						values.push(c->getValue());
					}
				}
				c = d->drawCard();
			}


			//assert
			Assert::AreEqual(expected_value, (int)values.size());
		}
		TEST_METHOD(initializer_One_Deck_13_Hearts) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			string suit = "Heart";
			queue<int> values;
			int expected_value = 13;



			//act
			for (int i = 0; i < CARDS_PER_DECK; i++) {
				if (c->getSuit() == suit) {
					if (c->getValue() >= 2 && c->getValue() < CARD_END_VALUE) {
						values.push(c->getValue());
					}
				}
				c = d->drawCard();
			}


			//assert
			Assert::AreEqual(expected_value, (int)values.size());
		}
		TEST_METHOD(initializer_One_Deck_13_Spades) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			string suit = "Spade";
			queue<int> values;
			int expected_value = 13;



			//act
			for (int i = 0; i < CARDS_PER_DECK; i++) {
				if (c->getSuit() == suit) {
					if (c->getValue() >= 2 && c->getValue() < CARD_END_VALUE) {
						values.push(c->getValue());
					}
				}
				c = d->drawCard();
			}


			//assert
			Assert::AreEqual(expected_value, (int)values.size());
		}
		TEST_METHOD(initializer_One_Deck_26_Red) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			string colour = "Red";
			queue<int> values;
			int expected_value = 26;



			//act
			for (int i = 0; i < CARDS_PER_DECK; i++) {
				if (c->getColour() == colour) {
					if (c->getValue() >= 2 && c->getValue() < CARD_END_VALUE) {
						values.push(c->getValue());
					}
				}
				c = d->drawCard();
			}


			//assert
			Assert::AreEqual(expected_value, (int)values.size());
		}
		TEST_METHOD(initializer_One_Deck_26_Black) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			string colour = "Black";
			queue<int> values;
			int expected_value = 26;



			//act
			for (int i = 0; i < CARDS_PER_DECK; i++) {
				if (c->getColour() == colour) {
					if (c->getValue() >= 2 && c->getValue() < CARD_END_VALUE) {
						values.push(c->getValue());
					}
				}
				c = d->drawCard();
			}


			//assert
			Assert::AreEqual(expected_value, (int)values.size());
		}
		TEST_METHOD(initializer_one_Deck_4_Of_Each_Number) {
			//setup
			const int decks = 1;
			deck* d = new deck(decks);
			card* c = d->drawCard();
			int values[CARDS_PER_DECK * decks];
			bool check = true;
			bool passover = false;
			for (int b = 0; b < SUITS * decks; b++) {
				for (int i = CARD_START_VALUE; i < CARD_END_VALUE; i++) {
					values[i + ((CARD_END_VALUE - 2) * b) - 2] = i;
				}
			}
			string message = "PASS";
			//act
			for (int i = 0; i < CARDS_PER_DECK * decks; i++) {
				for (int b = 0; b < CARDS_PER_DECK * decks; b++) {
					if (values[b] == c->getValue()) {
						values[b] = 0;
						passover = true;
					}
					if (passover == true) break;
				}
				if (passover == false) {
					message = c->getColour() + "  " + c->getSuit() + "  " + to_string(c->getValue());
					Assert::AreEqual((string)"PASS", message);
				}
				passover = false;
				c = d->drawCard();
			}


			//act 2
			for (int i = 0; i < CARDS_PER_DECK * decks; i++) {
				if (values[i] != 0) {
					check = false;
				}
			}

			//assert
			Assert::AreEqual(true, check);
		}

		TEST_METHOD(initializer_two_Deck_4_Of_Each_Number) {
			//setup
			const int decks = 2;
			deck* d = new deck(decks);
			card* c = d->drawCard();
			int values[CARDS_PER_DECK* decks];
			bool check = true;
			bool passover = false;
			for (int b = 0; b < SUITS* decks; b++) {
				for (int i = CARD_START_VALUE; i < CARD_END_VALUE; i++) {
					values[i + ((CARD_END_VALUE - 2) * b) - 2] = i;
				}
			}
			string message = "PASS";
			//act
			for (int i = 0; i < CARDS_PER_DECK* decks; i++) {
				for (int b = 0; b < CARDS_PER_DECK* decks; b++) {
					if (values[b] == c->getValue()) {
						values[b] = 0;
						passover = true;
					}
					if (passover == true) break;
				}
				if (passover == false) {
					message = c->getColour() + "  " + c->getSuit() + "  " + to_string(c->getValue());
					Assert::AreEqual((string)"PASS", message);
				}
				passover = false;
				c = d->drawCard();
			}


			//act 2
			for (int i = 0; i < CARDS_PER_DECK* decks; i++) {
				if (values[i] != 0) {
					check = false;
				}
			}

			//assert
			Assert::AreEqual(true, check);
		}

		TEST_METHOD(deckReset) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			int count = 0;
			string message = "PASS";

			//ACT
			for (int i = 0; i < 12; i++) {
				c = d->drawCard();

			}

			while (c->getValue() != 0) {
				c = d->drawCard();
				count++;
			}
			if (count >= CARDS_PER_DECK) {
				message = "Count failed!" + to_string(count);
				Assert::AreEqual((string)"PASS", message);
			}

			d->reset();
			count = 0;
			while (c->getValue() != 0) {
				c = d->drawCard();
				count++;
			}


			//ASSERT
			if (count == CARDS_PER_DECK) {
				Assert::AreEqual("PASS", "PASS");
			}

			
		}
		TEST_METHOD(returnCard) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			card* test = d->drawCard();
			int count = 0;
			string colour = "";
			string suit = "";
			int value = 0;

			while (test->getValue() != 0) {
				if (test->getColour() == c->getColour() && test->getSuit() == c->getSuit() && test->getValue() == c->getValue()) {
					Assert::Fail();
				}
				test = d->drawCard();
			}
			d->returnCard(c);
			d->returnCard(test);
			d->reset();
			c = d->drawCard();
			suit = c->getSuit();
			colour = c->getColour();
			value = c->getValue();
			d->returnCard(c);
			test = d->drawCard();
			while (test->getValue() != 0) {
				if (test->getColour() == colour && test->getSuit() == suit && test->getValue() == value) {
					Assert::AreEqual(1, 1);
				}
				test = d->drawCard();
			}
		}

		TEST_METHOD(testShuffle) {
			//setup
			deck* d = new deck();
			card* c = d->drawCard();
			int value = 0;
			int iterations = 0;
			const int passIterations = 7;
			const int totalIterations = 10;

			//ACT
			for (int z = 0; z < totalIterations; z++) {
			value = c->getValue();
			while (c->getValue() != 0) {
				c = d->drawCard();
			}
			d->reset();
			
			d->shuffle();
			c = d->drawCard();
			if (c->getValue() != value) {
				iterations++;
			}
			d->reset();
			c = d->drawCard();
		}

			//ASSERT
			if (iterations >= passIterations) {
			Assert::AreEqual(1, 1);
			}
			else {
				Assert::Fail();
			}
		}
		TEST_METHOD(drawCard) {
			//SETUP
			deck* d = new deck();
			card* c = d->drawCard();


			// act // ASSERT

			if (c->getColour() == "Red" || c->getColour() == "Black" && c->getSuit() == "Spade" || c->getSuit() == "Heart" || c->getSuit() == "Club" || c->getSuit() == "Diamond" && c->getValue() >=CARD_START_VALUE && c->getValue() < CARD_END_VALUE) {
				Assert::AreEqual(1, 1);
			}
			else {
				string message = c->getColour() + "  " + c->getSuit() + "  " + to_string(c->getValue());
				Assert::AreEqual((string)"PASS", message);
			}
		}
	};
}
