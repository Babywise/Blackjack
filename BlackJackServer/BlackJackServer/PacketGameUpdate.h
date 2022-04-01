#pragma once
#include "Packet.h"
//#include "../../BlackJackClient/BlackJackClient/BlackJack.h"
#define MAX_LINES MAX_PLAYERS + 1
#define MAX_MESSAGE_SIZE 50

class PacketGameUpdate : public Packet {

	struct Body {
		int numMessages = 0;
		int messageLength[MAX_LINES] = {};
	} Body;

	char* message[MAX_LINES] = {};

public:
	// creating
	PacketGameUpdate() : Packet() { 
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize + (sizeof(char*) * MAX_LINES), Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetGameUpdate;
	};

	// receiving
	PacketGameUpdate(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		/*int pos = 0;

		for (int i = 0; i < this->Body.numMessages; i++) {
			this->message[i] = new string();
			std::memcpy(this->message[i], src + sizeof(Head) + sizeof(Body) + pos, sizeof(string));
			pos += sizeof(string);
		}*/

		int pos = 0;

		for (int i = 0; i < this->Body.numMessages; i++) {
			this->message[i] = new char[this->Body.messageLength[i]] { NULL };
			std::memcpy(this->message[i], src + sizeof(Head) + sizeof(Body) + pos, this->Body.messageLength[i]);
			pos += this->Body.messageLength[i];
		}

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setMessages(char* message[]) {

		for (int i = 0; i < MAX_LINES; i++) {
			if (message[i] != NULL) {
				this->message[i] = new char[MAX_MESSAGE_SIZE] {};
				std::memcpy(this->message[i], message[i], MAX_MESSAGE_SIZE);
				this->Body.messageLength[i] = MAX_MESSAGE_SIZE;
				this->Body.numMessages++;
			} else {
				break;
			}
		}

	}

	void getMessages(char* message[]) {
		std::memcpy(message, this->message, sizeof(this->message));
	}

	char* serialize() {

		int TotalMessageSize = 0;

		for (int i = 0; i < this->Body.numMessages; i++) {
			TotalMessageSize += this->Body.messageLength[i];
		}

		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes + (sizeof(char*) * MAX_LINES) + TotalMessageSize;

		this->Head.Bytes = TotalSize;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, sizeof(Body));

		int pos = 0;

		for (int i = 0; i < this->Body.numMessages; i++) {
			//std::ofstream out(this->message[i]->c_str(), std::ios::binary);
			//out.write(this->pSerialBuff + sizeof(Head) + sizeof(Body) + pos, this->Body.messageLength[i]);
			std::memcpy(this->pSerialBuff + sizeof(Head) + sizeof(Body) + pos, this->message[i], this->Body.messageLength[i]);
			pos += this->Body.messageLength[i];
		}

		return this->pSerialBuff;

	}

};