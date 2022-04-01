#pragma once
#include "Winsock.h"
//#include "../../BlackJackServer/BlackJackServer/PacketManager.h"
#include "../../BlackJackClient/BlackJackClient/BlackJack.h"
#include "ServerThreads.h"

#define MAXCONNECTIONS 100
#define DISPLAYDATA 30
#define SENDBUFFERSIZE 5000

//int sendMessage(SOCKET socket_client,Packet* payload);
void handle_Client(SOCKET socket_client, blackjack* games[], int id);
int RecvRequestAndSendResponse(SOCKET socket_client, blackjack* games[], int* sequence);
//bool sendServerPacket(SOCKET socket_client, PacketManager& pM);
//func getplayerturn