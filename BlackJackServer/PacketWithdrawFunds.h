#pragma once

#include "Packet.h"

class PacketWithdrawFunds : public Packet {

	struct Body {
		Account* acc;
		long int cardNumber;
		int amountToRemove;
	} Body;

public:
	// creating
	PacketWithdrawFunds() : Packet() {
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetAddFunds;
		Body.acc = NULL, Body.cardNumber = 0, Body.amountToRemove = 0;
	};

	// receiving
	PacketWithdrawFunds(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setAccount(Account* acc) {
		this->Body.acc = acc;
	}

	Account* getAccount() {
		return this->Body.acc;
	}

	void setCardNumber(long cardNumber) {
		this->Body.cardNumber = cardNumber;
	}

	long getCardNumber() {
		return this->Body.cardNumber;
	}

	void setAmountToAdd(long amountToRemove) {
		this->Body.amountToRemove = amountToRemove;
	}

	long getAmountToAdd() {
		return this->Body.amountToRemove;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};