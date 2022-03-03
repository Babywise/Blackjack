#pragma once
#include "Packet.h"

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

	Packet* doPacket(char* buffer) {

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



};