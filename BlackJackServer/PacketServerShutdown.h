#pragma once
#include "Packet.h"

class PacketServerShutdown : public Packet {

	struct Body {
		bool status;
	} Body;

public:
	// creating
	PacketServerShutdown() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetServerShutdown; 
		Body.status = false;
	};

	// receiving
	PacketServerShutdown(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setStatus(int status) {
		this->Body.status = status;
	}

	bool getStatus() {
		return this->Body.status;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};