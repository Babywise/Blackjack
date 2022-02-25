#include "pch.h"
#include "CppUnitTest.h"
#include "card.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
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
			string actual = heart->getColour();

			//assert
			Assert::AreEqual(expected, actual);
		}
	};
}
