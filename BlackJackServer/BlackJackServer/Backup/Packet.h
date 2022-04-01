#pragma once


#include <iostream>

using namespace std;

enum class PacketType {
	packetInvalid,
	packetStartUp,
	packetResponse,
	packetTableStatus,
	packetGameUpdate,
	packetRoundUpdate,
	packetAddFunds,
	packetWithdrawFunds,
	packetPlayerTurn,
	packetQuitGame,
	packetServerShutdown,
	packetLogin,
	packetSignup
};

const unsigned int maxPacketSize = 5000;
const unsigned int emptyPacketSize = 18;

class Packet {
protected:
	struct Header {
		unsigned Source : 16;			//2 Bytes -> max = 65,535
		unsigned Destination : 16;		//2 Bytes -> max = 65,535
		PacketType pType;				//4 Bytes -> max = 2,147,483,647
		unsigned int Bytes;				//4 Bytes -> max = 4,294,967,295
		unsigned Fin : 16;				//2 byte  -> max = 255
		unsigned Ack : 16;				//2 byte  -> max = 255
		unsigned Seq : 16;				//2 bytes
	} Head;

	char* pSerialBuff;					//4 Bytes
	char* buffer;						//4 Bytes

public:
	// creating
	Packet() : pSerialBuff(nullptr), buffer(nullptr) { 
		Head.Source = 0, Head.Destination = 0, Head.pType = PacketType::packetInvalid, Head.Bytes = 0, Head.Fin = 0, Head.Ack = 0,Head.Seq=0; 
	};

	// receiving

	Packet(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;
	}

	void setSource(unsigned source) {
		this->Head.Source = source;
	}

	int getSource() {
		return this->Head.Source;
	}

	void setDestination(unsigned dest) {
		this->Head.Destination = dest;
	}

	int getDestination() {
		return this->Head.Destination;
	}

	void setPacketType(PacketType pType) {
		this->Head.pType = pType;
	}

	PacketType getPacketType() {
		return this->Head.pType;
	}

	void setBytes(int Bytes) {
		this->Head.Bytes = Bytes;
	}

	int getBytes() {
		return this->Head.Bytes;
	}

	void setAck(unsigned ack) {
		this->Head.Ack = ack;
	}

	int getAck() {
		return this->Head.Ack;
	}

	void setFin(unsigned fin) {
		this->Head.Fin = fin;
	}

	int getFin() {
		return this->Head.Fin;
	}

	char* getpSerialBuff() {
		return this->pSerialBuff;
	}

	char* getBuffer() {
		return this->buffer;
	}

	void setSequence(unsigned int sequence) {
		Head.Seq = sequence;
	}

	void incrementSequence() {
		Head.Seq++;
	}
	void decrementSequence() {
		Head.Seq--;
	}
	int getSequence() {
		return Head.Seq;
	}


	virtual char* serialize() {

		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff, this->buffer, this->Head.Bytes);

		return this->pSerialBuff;

	}

};