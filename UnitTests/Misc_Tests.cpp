
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
}