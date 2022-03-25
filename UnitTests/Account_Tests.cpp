#include "pch.h"
#include "CppUnitTest.h"
#include "Account.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackObjects
{
	TEST_CLASS(AccountTests) {
		TEST_METHOD(account_initalizer) {
			account* acc = new account("Test", 20, 20, "Testing");

			if (acc->getAge() != 20) {
				Assert::Fail();
			}
			if (acc->getFunds() != 20) {
				Assert::Fail();
			}
			if (acc->getName() != "Testing") {
				Assert::Fail();
			}
			if (acc->getUsername() != "Test") {
				Assert::Fail();
			}

		
		}
		TEST_METHOD(getAge) {
			account* acc = new account("", 0, 20, "");
			int expectedResults = 20;
			int Result = 0;
			Result = acc->getAge();

			Assert::AreEqual(expectedResults, Result);
		}
		TEST_METHOD(getName) {
			account* acc = new account("Test", 0, 0, "Testing");
			string expectedResults = "Testing";
			string Result = "";
			Result = acc->getName();

			Assert::AreEqual(expectedResults, Result);
		}
		TEST_METHOD(getUsername) {
			account* acc = new account("Test", 0, 0, "");
			string expectedResults = "Test";
			string Result = "";
			Result = acc->getUsername();

			Assert::AreEqual(expectedResults, Result);
		}
		TEST_METHOD(reduceFunds) {
			account* acc = new account("", 30, 0, "");
			float expectedResults = 10;
			float Result = 0;
			acc->reduceFunds(20);
			Result = acc->getFunds();

			Assert::AreEqual(expectedResults, Result);
		}
		TEST_METHOD(addFunds) {
			account* acc = new account("", 0, 0, "");
			float expectedResults = 20;
			float Result = 0;
			acc->addFunds(20);
			Result = acc->getFunds();
			
			Assert::AreEqual(expectedResults, Result);
		}
		TEST_METHOD(createAccountTest) {
			
			account* test = createAccount("Test", "Password", 20, "Testing");
			Assert::AreEqual((string)"", test->getUsername()); // returns nothing becuase unit tests cant create files
		}
		TEST_METHOD(loginTest) {
			account* acc =login("Test", "Password");
			Assert::AreEqual((string)"", acc->getUsername()); // returns nothing because no account exists
		}

	};
}