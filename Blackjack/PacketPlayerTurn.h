#pragma once
#include "Packet.h"
#include "Card.h"
#define MAX_CARDS 10
#define MAX_OPTIONS 4
class PacketPlayerTurn : public Packet {

	struct Body {
		string options[4] = {};
		int option = 0;
		int optionLength = 0;
		card publicCards[MAX_CARDS] = {};
		card hiddenCard = {};

	} Body;

public:
	// creating
	PacketPlayerTurn() : Packet() {
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetPlayerTurn;
		Body.option = 0;
	};

	// receiving
	PacketPlayerTurn(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setOptions(string options[]) {

		std::memcpy(this->Body.options, options, sizeof(this->Body.options));
	}

	string* getOptions() {
		return this->Body.options;
	}

	void setOption(int option) {
		this->Body.option = option;
	}

	int getOption() {
		return this->Body.option;
	}
	void setPublicCards(card* cards) {

		std::memcpy(this->Body.publicCards, cards, sizeof(this->Body.publicCards));
	}
	card* getPublicCards() {
		return this->Body.publicCards;
	}
	void setPrivateCard(card card) {
		this->Body.hiddenCard = card;
	}
	card* getPrivateCard() {
		return &this->Body.hiddenCard;
	}
	int getOptionSize() {
		return this->Body.optionLength;
	}
	void setOptionSize(int amt) {
		this->Body.optionLength = amt;
	}
	int getMaxPublicCards() {
		return this->Body.optionLength;
	}
	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};