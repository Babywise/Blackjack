#pragma once
#define _WIN32_WINNT 0x6000
#define _CRT_SECURE_NO_WARNINGS
#define BUFFER 100
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <string.h>
#include <stdbool.h>
#pragma comment(lib, "ws2_32.lib")
#define MAXLISTENERS 30
using namespace std;


// inits
SOCKET CreateAndConnectRemoteSocket(struct addrinfo* peer_address);
void initializeWindowsSockets();
struct addrinfo* ConfigureLocalAddress();
SOCKET CreateBindListeningSocket(struct addrinfo* bind_address);
void StartListeningForConnections(SOCKET socket_listen);
SOCKET WaitForAndAcceptConnection(SOCKET socket_listen);
struct addrinfo* ConfigureRemoteAddress(char* remoteHost, char remotePort);

// clients



