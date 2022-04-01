#pragma once
#include "Packet.h"
#include "../../BlackJackClient/BlackJackClient/Card.h"
#define MAX_CARDS 10
#define MAX_OPTIONS 4
class PacketPlayerTurn : public Packet {

	struct Body {
		string options[MAX_OPTIONS] = {};
		int option = 0;
		int optionLength = 0;
		card hiddenCard = {};
		int numPublicCards = 0;
		int gameValues[MAX_PLAYERS] = {};
		int dealerValue = 0;
		int totalGameValues = 0;
	} Body;

	card* publicCards[MAX_CARDS] = {};

public:
	// creating
	PacketPlayerTurn() : Packet() {
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize + (sizeof(card) * MAX_CARDS), Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetPlayerTurn;
		Body.option = 0;
	};

	// receiving
	PacketPlayerTurn(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		int totalSize = 0;

		for (int i = 0; i < this->Body.numPublicCards; i++) {
			this->publicCards[i] = new card();
			std::memcpy(this->publicCards[i], src + sizeof(Head) + sizeof(Body) + totalSize, sizeof(card));
			totalSize += sizeof(card);
		}

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setOptions(string options[]) {
		std::memcpy(this->Body.options, options, sizeof(this->Body.options));
	}

	void getOptions(string options[]) {

		for (int i = 0; i < this->Body.optionLength; i++) {
			options[i] = this->Body.options[i];
		}

		//options = this->Body.options;
		//std::memcpy(options, this->Body.options, sizeof(this->Body.options));
	}

	void setOption(int option) {
		this->Body.option = option;
	}

	int getOption() {
		return this->Body.option;
	}
	void setPublicCards(card* cards[]) {
		std::memcpy(this->publicCards, cards, sizeof(this->publicCards));
		int i = 0;
		while (cards[i] != NULL && i < MAX_CARDS) {
			i++;
		}
		this->Body.numPublicCards = i;
	}
	void getPublicCards(card* cards[]) {
		std::memcpy(cards, this->publicCards, sizeof(this->publicCards));
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
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes + (sizeof(card) * MAX_CARDS);

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, sizeof(Body));

		int totalSize = 0;

		for (int i = 0; i < this->Body.numPublicCards; i++) {
			std::memcpy(this->pSerialBuff + sizeof(Head) + sizeof(Body) + totalSize, this->publicCards[i], sizeof(card));
			totalSize += sizeof(card);
		}

		/*for (int i = 0; i < MAX_CARDS; i++) {
			if (this->publicCards[i] != NULL) {
				std::memcpy(this->pSerialBuff + sizeof(Head) + this->Head.Bytes + totalSize, this->publicCards[i], sizeof(card));
				
			} else {
				std::memcpy(this->pSerialBuff + sizeof(Head) + this->Head.Bytes + totalSize, new card(), sizeof(card));
			}
			totalSize += sizeof(card);
		}*/

		return this->pSerialBuff;

	}
};