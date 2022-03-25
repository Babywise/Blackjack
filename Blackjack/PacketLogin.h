#pragma once
#include "Packet.h"

class PacketLogin : public Packet {

	struct Body {
		string username;
		string password;
	} Body;

public:
	// creating
	PacketLogin() : Packet() { Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetLogin; };

	// receiving
	PacketLogin(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void PacketLoginSetUsername(string username) {
		this->Body.username = username;
	}

	string PacketLoginGetUsername() {
		return this->Body.username;
	}

	void PacketLoginSetPassword(string password) {
		this->Body.password = password;
	}

	string PacketLoginGetPassword() {
		return this->Body.password;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};