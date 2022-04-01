#include "pch.h"
#include "CppUnitTest.h"
#include "../BlackJackServer/Packet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackServerTests
{
	TEST_CLASS(BlackJackServerTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Packet p;
			Assert::AreEqual(p.getAck(), 0);
		}

	};

}
