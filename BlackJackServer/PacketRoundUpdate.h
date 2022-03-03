#pragma once

#include "PotentialIncludes.h"

#include "Packet.h"

class PacketRoundUpdate : public Packet {

	struct Body {
		int totalValues[maxPlayers] = {};
		Card faceUpCards[maxPlayers][maxPublicCards] = {};
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
		memcpy(this->Body.totalValues, totalValues, sizeof(this->Body.totalValues));
	}

	int* getTotalValues() {
		return this->Body.totalValues;
	}

	//needs fixing

	/*void setFaceUpCards(Card* faceUpCards[]) {
		memcpy(this->Body.faceUpCards, faceUpCards, sizeof(this->Body.faceUpCards));
	}

	Card** getFaceUpCards() {
		return reinterpret_cast<Card**>(this->Body.faceUpCards);
	}*/

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};