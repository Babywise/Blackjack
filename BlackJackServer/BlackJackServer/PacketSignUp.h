#pragma once
#include "Packet.h"

class PacketSignUp : public Packet {

	struct Body {
		string name;
		string username;
		string password;
		int age;
	} Body;

public:
	// creating
	PacketSignUp() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetSignup; 
		Body.age = 0;
	};

	// receiving
	PacketSignUp(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->buffer = new char[this->Head.Bytes]{ NULL };
		this->buffer = src + sizeof(Head), this->Head.Bytes;

		this->pSerialBuff = nullptr;

	}

	void PacketSignUpSetUsername(string username) {
		this->Body.username = username;
	}

	string PacketSignUpGetUsername() {
		return this->Body.username;
	}

	void PacketSignUpSetPassword(string password) {
		this->Body.password = password;
	}

	string PacketSignUpGetPassword() {
		return this->Body.password;
	}

	void PacketSignUpSetAge(int age) {
		this->Body.age = age;
	}

	int PacketSignUpGetAge() {
		return this->Body.age;
	}

	void PacketSignUpSetName(string name) {
		this->Body.name = name;
	}

	string PacketSignUpGetName() {
		return this->Body.name;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};