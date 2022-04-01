#pragma once
#include "Packet.h"

#define BLOCK_SIZE 1000

class PacketStartUp : public Packet {

	struct Body {
		int currBlock = 0;
		int numBlocks = 0;
		char imageData[BLOCK_SIZE] = {};
	} Body;

public:
	// creating
	PacketStartUp() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetStartUp;
	};

	// receiving
	PacketStartUp(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setImageData(char* imageData) {
		std::memcpy(this->Body.imageData, imageData, sizeof(this->Body.imageData));
	}

	char* getImageData() {
		return this->Body.imageData;
	}

	void setCurrBlock(int currBlock) {
		this->Body.currBlock = currBlock;
	}

	int getCurrBlock() {
		return this->Body.currBlock;
	}

	void setNumBlocks(int numBlocks) {
		this->Body.numBlocks = numBlocks;
	}

	int getNumBlocks() {
		return this->Body.numBlocks;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};