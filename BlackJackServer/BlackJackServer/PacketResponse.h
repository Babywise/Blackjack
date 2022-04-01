#pragma once
#include "Packet.h"
class PacketResponse : public Packet {

	struct Body {
		string response;
		float amount = 0;
		int age = 0;
		string name = ""; //potential different packet
		string username = "";
	} Body;

public:
	// creating
	PacketResponse() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetResponse; 
	};

	// receiving
	PacketResponse(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setResponse(string response) {
		this->Body.response = response;
	}

	string getResponse() {
		return this->Body.response;
	}
	void setName(string name) {
		this->Body.name = name;
	}

	string getName() {
		return this->Body.name;
	}
	void setUsername(string name) {
		this->Body.username = name;
	}

	string getUsername() {
		return this->Body.username;
	}
	void setValue(float value) {
		this->Body.amount = value;
	}

	float getValue() {
		return this->Body.amount;
	}
	void setAge(int age) {
		this->Body.age = age;
	}

	int getAge() {
		return this->Body.age;
	}


	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};