#pragma once
#include "Packet.h"

const int gameUpdateMaxPlayers = externalMaxPlayers;

class PacketGameUpdate : public Packet {

	struct Body {
		string usernames[gameUpdateMaxPlayers] = {};
		int bets[gameUpdateMaxPlayers] = {};
		Card faceUpCards[gameUpdateMaxPlayers] = {};
	} Body;

public:
	// creating
	PacketGameUpdate() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetGameUpdate;
	};

	// receiving
	PacketGameUpdate(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setUsernames(string* usernames) {
		std::memcpy(this->Body.usernames, usernames, sizeof(this->Body.usernames));
	}

	string* getUsernames() {
		return this->Body.usernames;
	}

	void setBets(int* bets) {
		std::memcpy(this->Body.bets, bets, sizeof(this->Body.bets));
	}

	int* getBets() {
		return this->Body.bets;
	}

	void setFaceUpCards(int* faceUpCards) {
		std::memcpy(this->Body.faceUpCards, faceUpCards, sizeof(this->Body.faceUpCards));
	}

	Card* getFaceUpCards() {
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