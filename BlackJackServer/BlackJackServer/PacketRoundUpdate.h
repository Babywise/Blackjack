#pragma once
#include "Packet.h"
#include "../../BlackJackClient/BlackJackClient/Card.h"

class PacketRoundUpdate : public Packet {

	struct Body {
		int gameValues[MAX_PLAYERS] = {};
		int dealerValue = 0;
		int totalGameValues = 0;
	} Body;

public:
	// creating
	PacketRoundUpdate() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetRoundUpdate; 

	};

	// receiving
	PacketRoundUpdate(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setGameValues(int* gameValues) {
		std::memcpy(this->Body.gameValues, gameValues, sizeof(this->Body.gameValues));
	}
	int* getGameValues() {
		return this->Body.gameValues;
	}
	void setDealerValue(int dealerValue) {
		this->Body.dealerValue = dealerValue;
	}
	int getDealerValue() {
		return this->Body.dealerValue;
	}
	void setTotalGameValues(int totalGameValues) {
		this->Body.totalGameValues = totalGameValues;
	}
	int getTotalGameValues() {
		return this->Body.totalGameValues;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};