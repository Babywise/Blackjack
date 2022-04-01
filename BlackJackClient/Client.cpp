#pragma comment(lib, "Ws2_32.lib")
#include <windows.networking.sockets.h>
#include <iostream>
#include <fstream>

#include "../BlackJackServer/Packet.h"
#include "../BlackJackServer/PacketAddFunds.h"
#include "../BlackJackServer/PacketGameUpdate.h"
#include "../BlackJackServer/PacketLogin.h"
#include "../BlackJackServer/PacketManager.h"
#include "../BlackJackServer/PacketPlayerTurn.h"
#include "../BlackJackServer/PacketQuitGame.h"
#include "../BlackJackServer/PacketResponse.h"
#include "../BlackJackServer/PacketRoundUpdate.h"
#include "../BlackJackServer/PacketSignUp.h"
#include "../BlackJackServer/PacketStartup.h"
#include "../BlackJackServer/PacketTableStatus.h"
#include "../BlackJackServer/PacketWithdrawFunds.h"
using namespace std;

int main(void) {

	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}
	
	ofstream output("../../Images/ElementalCasinoBannerClient.png", ios::binary | ios::out);

	char RxBuffer[maxPacketSize];

	int currClientBlock = 0;

	while (recv(ClientSocket, RxBuffer, maxPacketSize, 0) > 0) {
		PacketManager* pM = new PacketManager(RxBuffer);
		PacketStartUp pS = PacketStartUp(pM->getPacket()->serialize());

		if (currClientBlock == pS.getCurrBlock()) {
			output.write(pS.getImageData(), BLOCK_SIZE);
			currClientBlock++;
			PacketStartUp pSS;
			pSS.setCurrBlock(currClientBlock);
			pM = new PacketManager(pSS.serialize());
			send(ClientSocket, pM->getPacket()->serialize(), pM->getPacket()->getBytes(), 0);
		}
		else {
			PacketStartUp pSS;
			pSS.setCurrBlock(currClientBlock);
			pM = new PacketManager(pSS.serialize());
			send(ClientSocket, pM->getPacket()->serialize(), pS.getBytes(), 0);
		}

	}
	output.close();

	system("pause");


	//closes connection and socket
	closesocket(ClientSocket);

	//frees Winsock DLL resources
	WSACleanup();

	int garbage;
	std::cin >> garbage;

	return 0;

}