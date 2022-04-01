#pragma comment(lib, "Ws2_32.lib")
#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream>

#include "Packet.h"
#include "PacketAddFunds.h"
#include "PacketGameUpdate.h"
#include "PacketLogin.h"
#include "PacketManager.h"
#include "PacketPlayerTurn.h"
#include "PacketQuitGame.h"
#include "PacketResponse.h"
#include "PacketRoundUpdate.h"
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

	ifstream input("../../Images/ElementalCasinoBanner.png", ios::binary | ios::in);

	char RxBuffer[maxPacketSize];
	char TxBuffer[maxPacketSize];

	int numBlocks = 0;
	while (input.read(RxBuffer, BLOCK_SIZE)) {
		if (!input.eof()) {
			numBlocks++;
		}
	}

	input.close();

	PacketManager* pM;
	PacketStartUp* pS = new PacketStartUp();
	PacketStartUp* pSS;
	pS->setNumBlocks(numBlocks);

	int currBlock = 0;
	int currClientBlock = 0;
	input.open("../../Images/ElementalCasinoBanner.png", ios::binary | ios::in);
	while (input.read(RxBuffer, BLOCK_SIZE)) {
		if (!input.eof()) {

			pS->setCurrBlock(currBlock);
			pS->setImageData(RxBuffer);

			pM = new PacketManager(pS->serialize());

			while (currClientBlock != pS->getCurrBlock() + 1) {
				int sentBytes = send(ConnectionSocket, pM->getPacket()->serialize(), pS->getBytes(), 0);
				//std::cout << "Current Block :" << currBlock;
				if (sentBytes == pS->getBytes()) {
					recv(ConnectionSocket, RxBuffer, maxPacketSize, 0);
					pM = new PacketManager(RxBuffer);
					pSS = new PacketStartUp(pM->getPacket()->serialize());
					currClientBlock = pSS->getCurrBlock();

				}
			}
			currBlock++;
		}
	}

	input.close();



	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();

	int garbage;
	std::cin >> garbage;

	return 0;

}