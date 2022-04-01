#pragma once
#include "Packet.h"
#include "../../BlackJackClient/BlackJackClient/Account.h"

class PacketAddFunds : public Packet {

	struct Body {
		account acc = account("", 0, 0, "");
		long long cardNumber;
		float amountToAdd;
	} Body;

public:
	// creating
	PacketAddFunds() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetAddFunds,
		Body.cardNumber = 0, Body.amountToAdd = 0;
	};

	// receiving
	PacketAddFunds(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setAccount(account acc) {
		this->Body.acc = acc;
	}

	account getAccount() {
		return this->Body.acc;
	}

	void setCardNumber(long long cardNumber) {
		this->Body.cardNumber = cardNumber;
	}

	long long getCardNumber() {
		return this->Body.cardNumber;
	}

	void setAmountToAdd(float amountToAdd) {
		this->Body.amountToAdd = amountToAdd;
	}

	float getAmountToAdd() {
		return this->Body.amountToAdd;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};