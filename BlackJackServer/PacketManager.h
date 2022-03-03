#pragma once
#include "Packet.h"
#include "PacketAddFunds.h"
#include "PacketGameUpdate.h"
#include "PacketLogin.h"
#include "PacketManager.h"
#include "PacketPlayerTurn.h"
#include "PacketQuitGame.h"
#include "PacketResponse.h"
#include "PacketRoundUpdate.h"
#include "PacketServerShutdown.h"
#include "PacketSignUp.h"
#include "PacketStartup.h"
#include "PacketTableStatus.h"
#include "PacketWithdrawFunds.h"

class PacketManager {
	Packet* packet;
	PacketType pType;
public:

	PacketManager(char* buffer) {
		Packet* p = new Packet(buffer);
		this->pType = p->getPacketType();
		this->packet = this->setupPacket(buffer);
	}

	Packet* getPacket() {
		return this->packet;
	}

	PacketType getPacketType() {
		return this->pType;
	}

	//not used yet
	Packet* doPacket(char* buffer) {

		PacketLogin pp;

		switch (this->pType)
		{
		case PacketType::packetInvalid:
			//throw new exception("Not Implemented");
			break;
		case PacketType::packetStartUp:
			break;
		case PacketType::packetResponse:
			break;
		case PacketType::packetTableStatus:
			break;
		case PacketType::packetGameUpdate:
			break;
		case PacketType::packetRoundUpdate:
			break;
		case PacketType::packetAddFunds:
			break;
		case PacketType::packetWithdrawFunds:
			break;
		case PacketType::packetPlayerTurn:
			break;
		case PacketType::packetQuitGame:
			break;
		case PacketType::packetServerShutdown:
			break;
		case PacketType::packetLogin:
			break;
		case PacketType::packetSignup:
			break;
		default:
			return this->packet;
		}
	}


private:
	Packet* setupPacket(char* buffer) {

		PacketLogin pp;

		switch (this->pType)
		{
		case PacketType::packetInvalid:
			//throw new exception("Not Implemented");
			break;
		case PacketType::packetStartUp:
			return new PacketStartUp(buffer);
			break;
		case PacketType::packetResponse:
			return new PacketResponse(buffer);
			break;
		case PacketType::packetTableStatus:
			return new PacketTableStatus(buffer);
			break;
		case PacketType::packetGameUpdate:
			return new PacketGameUpdate(buffer);
			break;
		case PacketType::packetRoundUpdate:
			return new PacketRoundUpdate(buffer);
			break;
		case PacketType::packetAddFunds:
			return new PacketAddFunds(buffer);
			break;
		case PacketType::packetWithdrawFunds:
			return new PacketWithdrawFunds(buffer);
			break;
		case PacketType::packetPlayerTurn:
			return new PacketPlayerTurn(buffer);
			break;
		case PacketType::packetQuitGame:
			return new PacketQuitGame(buffer);
			break;
		case PacketType::packetServerShutdown:
			return new PacketServerShutdown(buffer);
			break;
		case PacketType::packetLogin:
			return new PacketLogin(buffer);
			break;
		case PacketType::packetSignup:
			return new PacketSignUp(buffer);
			break;
		default:
			return this->packet;
		}
	}



};