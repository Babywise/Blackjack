#pragma once
#include "Packet.h"

class PacketPlayerTurn : public Packet {

	struct Body {
		string options[maxOptions] = {};
		int option = 0;
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

	void setOptions(string* options) {
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

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};