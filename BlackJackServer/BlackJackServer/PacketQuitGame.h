#pragma once
#include "Packet.h"

class PacketQuitGame : public Packet {

	struct Body {
		float accFunds;
	} Body;

public:
	// creating
	PacketQuitGame() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetQuitGame;
		Body.accFunds = 0;
	};

	// receiving
	PacketQuitGame(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setAccFunds(float accFunds) {
		this->Body.accFunds = accFunds;
	}

	float getAccFunds() {
		return this->Body.accFunds;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};