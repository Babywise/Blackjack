#include "Server.h"
#include "Winsock.h"
#include <future>
#include "Logging.h"

// deals with requests from client
void handle_Client(SOCKET socket_client, blackjack* games[], int id) {
	int sequence = 0;
	std::cout << "Client #" << id << " is Connected ( Thread: " << std::this_thread::get_id() << " )" << std::endl;
	//DataLog("Client #" + to_string(id) + " is Connected ( Thread: " + (char*)(std::this_thread::get_id()) + " )");
	int i;
	// stay connected until no message is recieved


	i = RecvRequestAndSendResponse(socket_client, games, &sequence);
	while (i == 1) {
		i = RecvRequestAndSendResponse(socket_client, games, &sequence);
	}

	closesocket(socket_client);

}
bool checkLuhn(const string& cardNo) // https://www.geeksforgeeks.org/luhn-algorithm/
{
	int nDigits = cardNo.length();

	int nSum = 0, isSecond = false;
	for (int i = nDigits - 1; i >= 0; i--) {

		int d = cardNo[i] - '0';

		if (isSecond == true)
			d = d * 2;

		// We add two digits to handle
		// cases that make two digits after
		// doubling
		nSum += d / 10;
		nSum += d % 10;

		isSecond = !isSecond;
	}
	return (nSum % 10 == 0);
}
int RecvRequestAndSendResponse(SOCKET socket_client, blackjack* games[], int* sequence) {
	//cout << "------------------------------------------------------" << std::endl;
	//cout << "( Thread: " << std::this_thread::get_id() << " )..." << std::endl;

	char RxBuffer[maxPacketSize] = {};
	int bytes_recvd = 0;
	PacketManager* pM;
	// clears buffer of sends | lets the next sequence number through
	while (true) {
		if (recv(socket_client, RxBuffer, maxPacketSize, 0) == -1) return -1;
		pM = new PacketManager(RxBuffer);
		if (pM->getPacket()->getSequence() == sequence[0]) {
			break;
		}
	}

	cout << "Recieved Request " << *sequence << "\n";
	DataLog("Recieved Request " + to_string(*sequence));
	pM = new PacketManager(RxBuffer); // gets next real packet
	sequence[0]++; // increments the expected sequence value

	PacketSignUp* pS;
	PacketLogin* pL;
	PacketTableStatus* tS;
	PacketResponse* pR;
	PacketAddFunds* pF;
	PacketWithdrawFunds* pWf;
	account* acc = new account("", 0, 0, "");

	// for sending thread
	std::promise<int> exit;
	std::future<int> future = exit.get_future();
	std::promise<int> exits;
	std::future<int> futures = exits.get_future();
	//
	player* p1;
	switch (pM->getPacketType())
	{
	case PacketType::packetInvalid:
		//------------------------------------PLEASE CODE ME----------------------------------
		break;
	case PacketType::packetStartUp:

		//------------------------------------PLEASE CODE ME----------------------------------

		break;
	case PacketType::packetResponse: // join game
		pR = new PacketResponse(RxBuffer);
		pR->setSequence(pM->getPacket()->getSequence());
		acc = new account(pR->getUsername(), pR->getValue(), pR->getAge(), pR->getName());
		acc->connection = &socket_client;
		p1 = new player(acc);

		if (games[atoi(pR->getResponse().c_str())]->players.size() == 0) {
			games[atoi(pR->getResponse().c_str())]->players.push(p1);
		}
		else {
			games[atoi(pR->getResponse().c_str())]->incomingPlayers.push(p1);
		}

		sendServerPacket(socket_client, *pM);
		games[atoi(pR->getResponse().c_str())]->startGame(*pM); // pass in packet manager
		games[atoi(pR->getResponse().c_str())] = new blackjack();
		sequence[0] = pM->getPacket()->getSequence();
		sequence[0]++;
		break;
	case PacketType::packetTableStatus:

		tS = new PacketTableStatus(RxBuffer);
		tS->setSequence(pM->getPacket()->getSequence());

		int players[NUMBEROFTABLES];

		for (int i = 0; i < NUMBEROFTABLES; i++) {
			players[i] = games[i]->players.size() + games[i]->computers.size();
		}

		tS->setPlayers(players);
		tS->setAvailableTables(NUMBEROFTABLES);
		pM = new PacketManager(tS->serialize());
		
		sendServerPacket(socket_client, *pM);

		sequence[0] = pM->getPacket()->getSequence();
		sequence[0]++;
		//recv ack
		break;
	case PacketType::packetAddFunds:

		pF = new PacketAddFunds(RxBuffer);
		if (checkLuhn(to_string(pF->getCardNumber()))) {
			pF->getAccount().addFunds(pF->getAmountToAdd());
		}
		else {
			pF->setAmountToAdd(0);
		}

		pM = new PacketManager(pF->serialize());

		sendServerPacket(socket_client, *pM);

		sequence[0] = pM->getPacket()->getSequence();
		sequence[0]++;

		break;
	case PacketType::packetWithdrawFunds:
		pWf = new PacketWithdrawFunds(RxBuffer);
		if (checkLuhn(to_string(pWf->getCardNumber()))) {
			pWf->getAccount().reduceFunds(pWf->getAmountToRemove());
		}
		else {
			pWf->setAmountToRemove(0);
		}

		pM = new PacketManager(pWf->serialize());

		sendServerPacket(socket_client, *pM);

		sequence[0] = pM->getPacket()->getSequence();
		sequence[0]++;
		break;
	case PacketType::packetQuitGame:
		return 0;//exit
		break;
	case PacketType::packetLogin:
	{
		pL = new PacketLogin(RxBuffer);
		acc = login(pL->PacketLoginGetUsername(), pL->PacketLoginGetPassword());

		pR = new PacketResponse();
		pR->setSequence(pL->getSequence());
		pR->setName(acc->getName());
		pR->setAge(acc->getAge());
		pR->setUsername(acc->getUsername());
		pR->setValue(acc->getFunds());

		pM = new PacketManager(pR->serialize());

		sendServerPacket(socket_client, *pM);

		sequence[0] = pM->getPacket()->getSequence();
		sequence[0]++;

		break;
	} // packet login scope
	case PacketType::packetSignup:
		pS = new PacketSignUp(RxBuffer);
		acc = signup(pS->PacketSignUpGetUsername(), pS->PacketSignUpGetPassword(), pS->PacketSignUpGetName(), pS->PacketSignUpGetAge());

		pR = new PacketResponse();
		pR->setSequence(pS->getSequence());
		pR->setName(acc->getName());
		pR->setAge(acc->getAge());
		pR->setUsername(acc->getUsername());
		pR->setValue(acc->getFunds());

		pM = new PacketManager(pR->serialize());

		sendServerPacket(socket_client, *pM);

		sequence[0] = pM->getPacket()->getSequence();
		sequence[0]++;

		break;
	default:
		break;
	}

	return 1;
}