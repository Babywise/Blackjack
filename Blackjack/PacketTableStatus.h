#pragma once


#define MAX_PLAYERS 10

class PacketTableStatus : public Packet {

	struct Body {
		int availableTables = 0;
		int players[MAX_PLAYERS] = {};
		int maxPlayers[MAX_PLAYERS] = {};
	} Body;

public:
	// creating
	PacketTableStatus() : Packet() {
		Head.Source = 0, Head.Destination = 0, Head.Bytes = sizeof(Body) + emptyPacketSize, Head.Fin = 0, Head.Ack = 0, Head.pType = PacketType::packetTableStatus;
		Body.availableTables = 0;
		std::fill_n(Body.maxPlayers, MAX_PLAYERS, MAX_PLAYERS);
	};

	// receiving
	PacketTableStatus(char* src) {
		std::memcpy(&this->Head, src, sizeof(Head));
		std::memcpy(&this->Body, src + sizeof(Head), sizeof(Body));

		this->pSerialBuff = nullptr;
		this->buffer = nullptr;

	}

	void setAvailableTables(int availableTables) {
		this->Body.availableTables = availableTables;
	}

	int getAvailableTables() {
		return this->Body.availableTables;
	}

	void setPlayers(int* players) {
		std::memcpy(this->Body.players, players, sizeof(this->Body.players));
	}

	int* getPlayers() {
		return this->Body.players;
	}

	void setMaxPlayers(int* maxPlayers) {
		std::memcpy(this->Body.maxPlayers, maxPlayers, sizeof(this->Body.maxPlayers));
	}

	int* getMaxPlayers() {
		return this->Body.maxPlayers;
	}

	char* serialize() {
		unsigned int TotalSize = emptyPacketSize + this->Head.Bytes;

		this->pSerialBuff = new char[TotalSize] { NULL };

		std::memcpy(this->pSerialBuff, &this->Head, sizeof(Head));
		std::memcpy(this->pSerialBuff + sizeof(Head), &this->Body, this->Head.Bytes);

		return this->pSerialBuff;

	}
};