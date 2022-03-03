#pragma once

#include "PotentialIncludes.h"

#include "Packet.h"

const int roundUpdateMaxPublicCards = externalMaxPublicCards;
const int roundUpdateMaxPlayers = externalMaxPlayers;

class PacketRoundUpdate : public Packet {

	struct Body {
		int totalValues[roundUpdateMaxPlayers] = {};
		Card* faceUpCards[roundUpdateMaxPublicCards] = {};
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

	void setTotalValues(int* totalValues) {
		std::memcpy(this->Body.totalValues, totalValues, sizeof(this->Body.totalValues));
	}

	int* getTotalValues() {
		return this->Body.totalValues;
	}

	void setFaceUpCards(Card* faceUpCards[roundUpdateMaxPublicCards]) {
		memcpy(this->Body.faceUpCards, faceUpCards, sizeof(this->Body.faceUpCards));
	}

	Card** getFaceUpCards() {
		return this->Body.faceUpCards;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};