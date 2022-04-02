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
	PacketGameUpdate* pGu = {};
	PacketQuitGame* pQg = {};
	PacketRoundUpdate* pRu = {};

	while (acc->getUsername() == "") {

		system("cls");
		int input = 0;

		while (input == 0) {

			printStartMenu();

			switch (input = getMenuOption()) {
			case 1: {
				PacketLogin pL;
				pL.setSequence(pM->getPacket()->getSequence());
				getLoginInfo(pL);
				pM = new PacketManager(pL.serialize());
				break;
			}
			case 2:{
				PacketSignUp pS;
				pS.setSequence(pM->getPacket()->getSequence());
				getSignupInfo(pS);
				pM = new PacketManager(pS.serialize());
				break;
			}
			case 3:
				exit(1);
				break;
			default:
				system("cls");
				alertMessage("Please Enter a Valid Option");
				input = 0;
				break;
			}
		}
		
		sendClientPacket(peerSocket, *pM);
		//sequence = pM->getPacket()->getSequence();

		pR = new PacketResponse(pM->getPacket()->serialize());
		acc = new account(pR->getUsername(), pR->getValue(), pR->getAge(), pR->getName());
	
	} // login signup with server

	srand(time(0));
	
	int choice = 0;
	int MAX_GAMES;
	//tableStatusPacket* pkt = new tableStatusPacket();

	while (true) {

		system("cls");

		cout << "Player Funds : " << acc->getFunds() << endl;

		printMenuUsers(); // user gets menu to add or remove funds, logout, or join a table
		
		//cin >> choice;
		choice = getMenuOption();
		//std::cout << "Current Funds" << acc->getFunds() << std::endl;
		//system("pause");

		switch (choice) {
		case 1:
			while (true) {
				tS = new PacketTableStatus();
				tS->setSequence(pM->getPacket()->getSequence());
				pM = new PacketManager(tS->serialize());

				/*send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);

				char RxBuffer[maxPacketSize] = {};
				recv(peerSocket, RxBuffer, maxPacketSize, 0);*/
				sendClientPacket(peerSocket, *pM);
				sequence = pM->getPacket()->getSequence();

				tS = new PacketTableStatus(pM->getPacket()->serialize());
				int choice2 = 0;
				while (choice2 <= 0 || choice2 > tS->getAvailableTables() + 1) {
					printGamesAvailable(tS->getPlayers(), tS->getMaxPlayers(), tS->getAvailableTables()); // show all available games


					//cin >> choice2;

					choice2 = getMenuOption();
				}
				if (choice2 > 0 && choice2 <= tS->getAvailableTables() + 1) { // GET FROM SERVER -----------------
					if (choice2 == tS->getAvailableTables() + 1) { // if table MAXTABLE + 1 user has chosen to return to main menu
						break;
					} else {
						if (acc->getFunds() < 5) {
							break;
						}
						// Request server to join game ------------------
						pR = new PacketResponse();
						pR->setSequence(pM->getPacket()->getSequence());
						pR->setName(acc->getName());
						pR->setAge(acc->getAge());
						pR->setUsername(acc->getUsername());
						pR->setValue(acc->getFunds());
						pR->setResponse(to_string(choice2 - 1));

						pM = new PacketManager(pR->serialize());
					
						/*Sleep(250);

						send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);*/

						//recv ready to take our turn
						//serverpacketsend 
						// send ack ready to take turn
						//send data(turn choice)
						// recv ack // turn was recieved


						// sending packet response
						// getting ack
						// getting data????
						// sending ack that we got ??? data
						//std::cout << "Sending join table";
						//alertMessage("Sending join table");
						sendClientPacket(peerSocket, *pM);
						sequence = pM->getPacket()->getSequence();
						char RxBuffer[maxPacketSize] = {};
						
						
						//sendServerPacket(peerSocket, *pM);
				
						bool gameStatus = true;
						//char RxBuffer[maxPacketSize] = {};
						while (gameStatus) {
							//std::cout << "waiting to recieve turn";
							alertMessage("waiting to recieve turn");
							while (true) {
								if (recv(peerSocket, RxBuffer, maxPacketSize, 0) == -1)
									break;
								pM = new PacketManager(RxBuffer);
								if (pM->getPacket()->getSequence() == sequence + 1) {
									break;
								}
							}

							pM = new PacketManager(RxBuffer);

							int choice3 = 0;
							switch (pM->getPacketType()) {
							case PacketType::packetRoundUpdate: {
								system("cls");
								pRu = new PacketRoundUpdate(pM->getPacket()->serialize());

								printUpdateValues(pRu->getDealerValue(), pRu->getGameValues(), pRu->getTotalGameValues());

								/*std::cout << "Dealer has : " << pRu->getDealerValue() << std::endl;
								int* gameValues = pRu->getGameValues();
								for (int i = 0; i < pRu->getTotalGameValues(); i++) {
									std::cout << "Computer" << i + 1 << " has : " << gameValues[i] << std::endl;
								}
								std::cout << std::endl << std::endl;*/

								pT->getPrivateCard()->print();
								int i = 0;

								card* publicCard[MAX_CARDS];

								pT->getPublicCards(publicCard);

								

								

								std::cout << std::endl;

								//pM = new PacketManager(pRu->serialize());
								sendServerPacket(peerSocket, *pM); // serversendpacket send send recv

								for (int i = 0; i < pT->getMaxPublicCards(); i++) {
									if (publicCard[i]->getValue() > 1 && publicCard[i]->getValue() <= 14) {
										publicCard[i]->print();
									}
								}

								sequence = pM->getPacket()->getSequence();
								break;
							}
							case PacketType::packetPlayerTurn:
							{
								
								pT = new PacketPlayerTurn(pM->getPacket()->serialize());
								int maxChoice = pT->getOptionSize();
								
								while (choice3 <= 0 || choice3 > maxChoice) {
									system("cls");
									choice3 = 0;

									printUpdateValues(pT->getDealerValue(), pT->getGameValues(), pT->getTotalGameValues());

									/*std::cout << "Dealer has : " << pT->getDealerValue() << std::endl;
									
									int* gameValues = pT->getGameValues();
									for (int i = 0; i < pT->getTotalGameValues(); i++) {
										std::cout << "Computer" << i + 1 << " has : " << gameValues[i] << std::endl;
									}
									std::cout << std::endl << std::endl;*/

									pT->getPrivateCard()->print();
									int i = 0;
									
									card* publicCard[MAX_CARDS];

									pT->getPublicCards(publicCard);
									
									for (int i = 0; i < pT->getMaxPublicCards(); i++) {
										if (publicCard[i]->getValue() > 1 && publicCard[i]->getValue() <= 14) {
											publicCard[i]->print();
										}
									}
									
									string options[MAX_OPTIONS];
									pT->getOptions(options);
								
									
									for (int i = 0; i < pT->getOptionSize(); i++) {
										std::cout << i + 1 << ". " << options[i] << "\n";
									}
									
									std::cout << "Enter: ";
									choice3 = getMenuOption();
									std::cout << "\n-----------------------------\n";

									//^ prints get deleted for gui

									if (choice3 > 0 && choice3 < maxChoice + 1) {
										pT->setOption(choice3);
										pM = new PacketManager(pT->serialize());

										//std::cout << "Sending turn choice";
										alertMessage("Sending turn choice");
										sendServerPacket(peerSocket, *pM); // serversendpacket send send recv
										sequence = pM->getPacket()->getSequence();
									}
									
								}
								break;
							}
							case PacketType::packetGameUpdate: {

								system("cls");

								pGu = new PacketGameUpdate(pM->getPacket()->serialize());

								char* message[MAX_LINES] = {};

								pGu->getMessages(message);

								gameMessages(message);

								/*for (int i = 0; i < MAX_LINES; i++) {
									if (message[i] != NULL) {
										std::cout << message[i];
									} else {
										break;
									}
								}*/

								system("pause");

								pR->setSequence(pGu->getSequence());
								pR->setResponse("PacketGameUpdate");

								pM = new PacketManager(pR->serialize());

								sendServerPacket(peerSocket, *pM); // serversendpacket send send recv
								sequence = pM->getPacket()->getSequence();
								break;
							}
							case PacketType::packetQuitGame: {
								
								pQg = new PacketQuitGame(pM->getPacket()->serialize());

								pR->setValue(pQg->getAccFunds());
								float difference = pQg->getAccFunds() - acc->getFunds();
								acc->addFunds(difference);

								pR->setSequence(pQg->getSequence());
								pR->setResponse("PacketQuitGame");

								pM = new PacketManager(pR->serialize());

								sendServerPacket(peerSocket, *pM); // serversendpacket send send recv
								sequence = pM->getPacket()->getSequence();
								gameStatus = false;
								break;
							}							
							default: // QUIT GAME PACKKET SEND FUNDS
								gameStatus = false;
								break;
							}
						}
						//choice2 = 0; // once game has concluded allow user to select new table or select back
					}

				}
			} // while true
			break;
		case 2: // add funds
			addFunds(*pM, acc, peerSocket);
			sequence = pM->getPacket()->getSequence();
			break;
		case 3: // remove funds
			cashOut(*pM, acc, peerSocket);
			sequence = pM->getPacket()->getSequence();
			break;
		case 4: // logout
			exit(2);
			break;
		default:
			system("cls");
			alertMessage("Please Enter a Valid Option");
			break;
		}
	}// infinate loop

	// BLACKJACK MAINMENU



}




