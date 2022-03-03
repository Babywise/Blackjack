#pragma comment(lib, "Ws2_32.lib")
#include <windows.networking.sockets.h>
#include <iostream>

#include "Packet.h"
#include "PacketAddFunds.h"
#include "PacketGameUpdate.h"
#include "PacketLogin.h"
#include "PacketManager.h"
#include "PacketPlayerTurn.h"
#include "PacketQuitGame.h"
#include "PacketResponse.h"
#include "PacketRoundUpdate.h"
#include "PacketServerShutdown.h"
#include "PacketSignUp.h"
#include "PacketStartup.h"
#include "PacketTableStatus.h"
#include "PacketWithdrawFunds.h"

using namespace std;

int main(void) {
	//starts Winsock DLLs		
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//create server socket
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//binds socket to address
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	//listen on a socket
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	cout << "Waiting for client connection\n" << endl;

	//accepts a connection from a client
	SOCKET ConnectionSocket;
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	cout << "Connection Established" << endl;

	char RxBuffer[maxPacketSize] = {};
	recv(ConnectionSocket, RxBuffer, maxPacketSize, 0);

	PacketManager pM(RxBuffer);

	Packet* p = pM.getPacket();

	
	PacketLogin* pL;
	PacketSignUp* pS;

	switch (pM.getPacketType())
	{
	case PacketType::packetLogin:
		pL = new PacketLogin(RxBuffer);
		break;
	case PacketType::packetSignup:
		pS = new PacketSignUp(RxBuffer);
		break;
	default:
		break;
	}

	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();

	int garbage;
	std::cin >> garbage;

	return 0;

}