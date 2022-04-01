#pragma once

#include <future>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <time.h>

#include "../../BlackJackClient/BlackJackClient/Account.h"
#include "PacketManager.h"

#pragma comment(lib, "ws2_32.lib")

#define _WIN32_WINNT 0x6000
#define _CRT_SECURE_NO_WARNINGS
#define DISPLAYBUFFERSIZE 20
#define SENDBUFFERSIZE 110



// initializing sockets
SOCKET CreateAndConnectRemoteSocket(struct addrinfo* peer_address);
void initializeWindowsSockets();
struct addrinfo* ConfigureLocalAddress();
struct addrinfo* ConfigureRemoteAddress(char* remoteHost, char* remotePort);
void closeSocket(SOCKET server);

//Menu
void addFunds(account* acc, SOCKET client);
void cashOut(account* acc, SOCKET client);
//Threads
void sendThread(SOCKET sock, char* buffer, std::future<int> future);
bool sendPacket(SOCKET peerSocket, PacketManager& pM);