#include "Client.h"
#include "Packet.h"
#include "../../BlackJackClient/BlackJackClient/LoginManager.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <iostream>      
#include <thread>
#include <Windows.h>
#include <future>
#include "Menu.h"
using namespace std;

int main(void) {
	// initialize
	int sequence = 0;
	WSACleanup();
	initializeWindowsSockets();
	struct addrinfo* bind_address = ConfigureRemoteAddress((char*)ADDRESS, (char*)PORT);
	SOCKET peerSocket = CreateAndConnectRemoteSocket(bind_address);
	account* acc = new account("", 0, 0, "");
	PacketManager* pM = new PacketManager();
	PacketTableStatus* tS = {};
	PacketResponse* pR = {};
	PacketPlayerTurn* pT = {};


	while (acc->getUsername() == "") {

		system("cls");
		int input = 0;

		while (input == 0) {

			PacketSignUp pS;

			printStartMenu();

			switch (input = getMenuOption()) {
			case 1: {
				PacketLogin pL;
				pL.setSequence(pM->getPacket()->getSequence());
				getLoginInfo(pL);
				pM = new PacketManager(pL.serialize());
				break;
			}
			case 2:
				getSignupInfo(pS);
				pM = new PacketManager(pS.serialize());
				break;
			case 3:
				break;
			default:
				system("cls");
				std::cout << "Please Enter a Valid Option" << std::endl << std::endl;
				input = 0;
				break;
			}
		}
		
		sendPacket(peerSocket, *pM);
		sequence = pM->getPacket()->getSequence();

		pR = new PacketResponse(pM->getPacket()->serialize());
		acc = new account(pR->getUsername(), pR->getValue(), pR->getAge(), pR->getName());
	
	} // login signup with server

	srand(time(0));
	
	int choice = 0;
	int MAX_GAMES;
	//tableStatusPacket* pkt = new tableStatusPacket();

	while (true) {
		printMenuUsers(); // user gets menu to add or remove funds, logout, or join a table
		//cin >> choice;
		choice = getMenuOption();
		switch (choice) {
		case 1:
			while (true) {
				tS = new PacketTableStatus();
				pM = new PacketManager(tS->serialize());

				send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);

				char RxBuffer[maxPacketSize] = {};
				recv(peerSocket, RxBuffer, maxPacketSize, 0);
				tS = new PacketTableStatus(RxBuffer);
				printGamesAvailable(tS->getPlayers(), tS->getMaxPlayers(), tS->getAvailableTables()); // show all available games

				int choice2 = 0;
				//cin >> choice2;
				choice2 = getMenuOption();

				if (choice2 >= 0 && choice2 <= tS->getAvailableTables()) { // GET FROM SERVER -----------------
					if (choice2 == tS->getAvailableTables()) { // if table MAXTABLE + 1 user has chosen to return to main menu
						break;
					} else {
						// Request server to join game ------------------
						pR = new PacketResponse();
						pR->setName(acc->getName());
						pR->setAge(acc->getAge());
						pR->setUsername(acc->getUsername());
						pR->setValue(acc->getFunds());
						pR->setResponse(to_string(choice2));

						pM = new PacketManager(pR->serialize());
						
						Sleep(250);

						send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);
				
						int fin = 0;
						char RxBuffer[maxPacketSize] = {};
						while (fin == 0) {
							
							recv(peerSocket, RxBuffer, maxPacketSize, 0);
							pM = new PacketManager(RxBuffer);

							int choice = 0;
							switch (pM->getPacketType()) {

							case PacketType::packetPlayerTurn:
								pT = new PacketPlayerTurn(RxBuffer);

								while (choice <= 0 || choice > pT->getOptionSize()) {
									system("cls");
									choice = 0;
									pT->getPrivateCard()->print();
									int i = 0;
									card* publicCard = {pT->getPublicCards()};
									for (int i = 0; i < pT->getMaxPublicCards(); i++) {
										if (publicCard[i].getValue() >1 && publicCard[i].getValue() <= 14) {
											publicCard[i].print();
										}

										
									}
									string options[4] = {};
									memcpy(options,pT->getOptions(),sizeof(string)*4);
									for (int i = 0; i < pT->getOptionSize(); i++) {
										cout << i + 1 << ". " << options[i] << "\n";
									}
									cout << "Enter: ";
									cin >> choice;
									cout << "\n-----------------------------\n";
									if (choice > 0 && choice < pT->getOptionSize() + 1) {
										pT->setOption(choice);
										pM = new PacketManager(pT->serialize());
										Sleep(1000);
										send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);
									}
								}

								break;
							default:
								fin = 1;
								break;
							}
						}
						choice2 = 0; // once game has concluded allow user to select new table or select back
					}

				}
			} // while true
			break;
		case 2: // add funds
			addFunds(acc, peerSocket);
			break;
		case 3: // remove funds
			cashOut(acc, peerSocket);
			break;
		case 4: // logout
			exit(2);
			break;
		default:
			system("cls");
			std::cout << "Please Enter a Valid Option" << std::endl << std::endl;
			break;
		}
	}// infinate loop

	// BLACKJACK MAINMENU



}




