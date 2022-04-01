#pragma once

#include "Packet.h"
#include "../../BlackJackClient/BlackJackClient/Account.h"

class PacketWithdrawFunds : public Packet {

	struct Body {
		account acc = account("", 0, 0, "");
		long long cardNumber;
		float amountToRemove;
		
	} Body;



public:
	// creating
	PacketWithdrawFunds() : Packet() {
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetAddFunds;
		Body.cardNumber = 0, Body.amountToRemove = 0;
	};

	// receiving
	PacketWithdrawFunds(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));
		//std::memcpy(&this->acc, src + sizeof(Head) + sizeof(Body), sizeof(this->acc));

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

	void setAmountToRemove(float amountToRemove) {
		this->Body.amountToRemove = amountToRemove;
	}

	float getAmountToRemove() {
		return this->Body.amountToRemove;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, sizeof(Body));
		//std::memcpy(this->pSerialBuff + sizeof(Head) + this->Head.Bytes, &this->acc, sizeof(this->acc));

		return this->pSerialBuff;

	}
};