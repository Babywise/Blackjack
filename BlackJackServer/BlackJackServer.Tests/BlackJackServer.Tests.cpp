#include "pch.h"
#include "CppUnitTest.h"
#include "../../BlackJackClient/BlackJackClient/Card.cpp"
#include "../../BlackJackClient/BlackJackClient/Account.cpp"
#include "../BlackJackServer/Packet.h"
#include "../BlackJackServer/PacketLogin.h"
#include "../BlackJackServer/PacketManager.h"
#include "../BlackJackServer/PacketSignUp.h"
#include "../BlackJackServer/PacketResponse.h"
#include "../BlackJackServer/PacketTableStatus.h"
#include "../BlackJackServer/PacketGameUpdate.h"
#include "../BlackJackServer/PacketQuitGame.h"
#include "../BlackJackServer/PacketPlayerTurn.h"
#include "../BlackJackServer/PacketRoundUpdate.h"
#include "../BlackJackServer/PacketAddFunds.h"
#include "../BlackJackServer/PacketWithdrawFunds.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackJackServerTests
{
	TEST_CLASS(BlackJackServerTests)
	{
	public:
		
		TEST_METHOD(T001_PacketManager_CreatedAllPacketsAndDeseriallize_SnD)
		{
			//Arrange
			PacketManager* pM = new PacketManager();
			Packet p;
			PacketAddFunds pAF;
			PacketGameUpdate pGU;
			PacketPlayerTurn pPT;
			PacketQuitGame pQG;
			PacketResponse pR;
			PacketRoundUpdate pRU;
			PacketTableStatus pTS;
			PacketWithdrawFunds pWF;
			
			//Act
			PacketType expectedValue = PacketType::packetInvalid;
			pM = new PacketManager(p.serialize());
			PacketType actualValue = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue, (int)expectedValue);
			
			//Act
			PacketType expectedValue1 = PacketType::packetAddFunds;
			pM = new PacketManager(pAF.serialize());
			PacketType actualValue1 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue1, (int)expectedValue1);

			//Act
			PacketType expectedValue2 = PacketType::packetGameUpdate;
			pM = new PacketManager(pGU.serialize());
			PacketType actualValue2 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue2, (int)expectedValue2);

			//Act
			PacketType expectedValue3 = PacketType::packetPlayerTurn;
			pM = new PacketManager(pPT.serialize());
			PacketType actualValue3 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue3, (int)expectedValue3);

			//Act
			PacketType expectedValue4 = PacketType::packetQuitGame;
			pM = new PacketManager(pQG.serialize());
			PacketType actualValue4 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue4, (int)expectedValue4);

			//Act
			PacketType expectedValue5 = PacketType::packetResponse;
			pM = new PacketManager(pR.serialize());
			PacketType actualValue5 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue5, (int)expectedValue5);

			//Act
			PacketType expectedValue6 = PacketType::packetRoundUpdate;
			pM = new PacketManager(pRU.serialize());
			PacketType actualValue6 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue6, (int)expectedValue6);

			//Act
			PacketType expectedValue7 = PacketType::packetTableStatus;
			pM = new PacketManager(pTS.serialize());
			PacketType actualValue7 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue7, (int)expectedValue7);

			//Act
			PacketType expectedValue8 = PacketType::packetWithdrawFunds;
			pM = new PacketManager(pWF.serialize());
			PacketType actualValue8 = pM->getPacketType();
			//Assert
			Assert::AreEqual((int)actualValue8, (int)expectedValue8);
		}

	};

}
