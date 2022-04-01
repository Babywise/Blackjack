#pragma once
#include "Winsock.h"
#include "../../BlackJackServer/BlackJackServer/PacketManager.h"
#include <future>

int sendMessage(SOCKET socket_client, Packet* payload);
bool sendServerPacket(SOCKET socket_client, PacketManager& pM);
bool sendClientPacket(SOCKET peerSocket, PacketManager& pM);