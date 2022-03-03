#pragma comment(lib, "Ws2_32.lib")
#include <windows.networking.sockets.h>
#include <iostream>

#include "../BlackJackServer/Packet.h"
#include "../BlackJackServer/PacketAddFunds.h"
#include "../BlackJackServer/PacketGameUpdate.h"
#include "../BlackJackServer/PacketLogin.h"
#include "../BlackJackServer/PacketManager.h"
#include "../BlackJackServer/PacketPlayerTurn.h"
#include "../BlackJackServer/PacketQuitGame.h"
#include "../BlackJackServer/PacketResponse.h"
#include "../BlackJackServer/PacketRoundUpdate.h"
#include "../BlackJackServer/PacketServerShutdown.h"
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

	Card* faceUpCards[externalMaxPublicCards] = {};

	for (int h = 0; h < externalMaxPlayers; h++) {
		faceUpCards[h] = new Card[externalMaxPublicCards];

		for (int w = 0; w < externalMaxPublicCards; w++) {
			faceUpCards[h][w] = Card();
		}
	}

	faceUpCards[0][1] = Card();
	faceUpCards[0][1].num = 10;
	faceUpCards[9][1] = Card();
	faceUpCards[9][1].num = 50;

	PacketRoundUpdate pRU;

	pRU.setFaceUpCards(faceUpCards);
	Card** fp = pRU.getFaceUpCards();

	std::cout << fp[0][1].num;
	std::cout << fp[9][1].num;
	//pRU.getFaceUpCards();


	PacketSignUp pp;
	string name, username, password;
	int age = 0;
	std::cout << "---- Name ----" << std::endl;
	std::cout << ": ";
	std::cin >> name;
	std::cout << "---- Username ----" << std::endl;
	std::cout << ": ";
	std::cin >> username;
	std::cout << "---- Password ----" << std::endl;
	std::cout << ": ";
	std::cin >> password;
	std::cout << "---- Age ----" << std::endl;
	std::cout << ": ";
	std::cin >> age;
	pp.PacketSignUpSetName(name);
	pp.PacketSignUpSetUsername(username);
	pp.PacketSignUpSetPassword(password);
	pp.PacketSignUpSetAge(age);

	PacketManager pM(pp.serialize());

	send(ClientSocket, pM.getPacket()->serialize(), maxPacketSize, 0);

	


	//closes connection and socket
	closesocket(ClientSocket);

	//frees Winsock DLL resources
	WSACleanup();

	int garbage;
	std::cin >> garbage;

	return 0;
	return 0;

}