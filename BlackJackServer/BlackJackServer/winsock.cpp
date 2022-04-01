#include "Winsock.h"
#include "client.h"

void initializeWindowsSockets() {
	WSADATA d;
	if (WSAStartup(MAKEWORD(2, 2), &d)) {
		fprintf(stderr, "failed to init\n");
		exit(1);
	}
	//WSACleanup();
}

struct addrinfo* ConfigureLocalAddress()
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo* bind_address;
	getaddrinfo(0, PORT, &hints, &bind_address);

	return bind_address;
}


void closeSocket(SOCKET connection) {
	printf("Closing the connection");
	closesocket(connection);
}


SOCKET CreateAndConnectRemoteSocket(struct addrinfo* peer_address) {
	SOCKET socket_peer = socket(peer_address->ai_family, peer_address->ai_socktype, peer_address->ai_protocol);
	if ((socket_peer) == INVALID_SOCKET) {
		fprintf(stderr, "socket() failed, exiting with error (%d)\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if (connect(socket_peer, peer_address->ai_addr, peer_address->ai_addrlen)) {
		fprintf(stderr, "connect() failed, exiting with error (%d)\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(peer_address);
	return socket_peer;
}

struct addrinfo* ConfigureRemoteAddress(char* remoteHost, char* remotePort) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	struct addrinfo* peer_address;
	getaddrinfo(ADDRESS, PORT, &hints, &peer_address);
	return peer_address;
}


//Menu

void addFunds(PacketManager &pM, account* acc, SOCKET client) {
	system("cls");
	//cout << "Enter Card Number ('0') to return : ";
	long long int cardNumber = getCardNumber();
	//cin >> cardNumber;
	if (cardNumber == 0) {
		return;
	}
	//cout << "Enter amount to add ('0') to return : ";
	int amount = getFundsToAdd();
	//cin >> amount;
	if (amount == 0) {
		return;
	}

	PacketAddFunds* pAf = new PacketAddFunds();
	pAf->setSequence(pM.getPacket()->getSequence());
	pAf->setAccount(*acc);
	pAf->setCardNumber(cardNumber);
	pAf->setAmountToAdd(amount);

	pM = PacketManager(pAf->serialize());

	sendClientPacket(client, pM);
	pAf = new PacketAddFunds(pM.getPacket()->serialize());
	acc->addFunds(pAf->getAmountToAdd());
	//cout << std::endl << "Funds added : " << pAf->getAmountToAdd() << std::endl;
	alertMessage("Funds added : " + to_string(pAf->getAmountToAdd()) + "\n");
	system("pause");

}

void cashOut(PacketManager& pM, account* acc, SOCKET client) {
	system("cls");
	//cout << "Enter Card Number ('0') to return : ";
	long long int cardNumber = getCardNumber();
	//cin >> cardNumber;
	if (cardNumber == 0) {
		return;
	}
	//cout << "Enter amount to withdraw ('0') to return : ";
	int amount = getFundsToRemove();
	//cin >> amount;
	if (amount == 0) {
		return;
	}

	PacketWithdrawFunds* pWf = new PacketWithdrawFunds();
	pWf->setSequence(pM.getPacket()->getSequence());
	pWf->setAccount(*acc);
	pWf->setCardNumber(cardNumber);
	pWf->setAmountToRemove(amount);

	pM = PacketManager(pWf->serialize());

	sendClientPacket(client, pM);
	pWf = new PacketWithdrawFunds(pM.getPacket()->serialize());
	acc->reduceFunds(pWf->getAmountToRemove());
	//cout << std::endl << "Funds removed : " << pWf->getAmountToRemove() << std::endl;
	alertMessage("Funds removed : " + to_string(pWf->getAmountToRemove()) + "\n");
	system("pause");
}

//Threads

void sendThread(SOCKET sock, char* buffer, std::future<int> future) {
	Sleep(250);
	int MAX = 0;
	while (future.wait_for(std::chrono::milliseconds(25)) == std::future_status::timeout && MAX < 20) {
		send(sock, buffer, maxPacketSize, 0);
		MAX++;
	}
	cout << "Exiting thread..";
	return;
}

//Packets
bool sendClientPacket(SOCKET peerSocket, PacketManager &pM) {

	int sequence = pM.getPacket()->getSequence();

	//send function

	//sets a promise for an exit clause
	//thread waits 15ms before sending
	// this allows time for this application to move into recv mode
	// once recieved ack promise is set to 1 telling the send thread to stop
	std::promise<int> exit;
	std::future<int> future = exit.get_future();
	
	if (pM.getPacket()->getSequence() != 0) {
		pM.getPacket()->incrementSequence();
		sequence++;
	}

	cout << "Sending request :" << sequence << "\n";
	thread sending(sendThread, peerSocket, pM.getPacket()->serialize(), std::move(future));
	// V1.0  ------------   //send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);
	char RxBuffer[maxPacketSize] = {};
	sequence++;
	// recv next sequence packet
	cout << "Recieve Ack" << sequence << "\n";
	while (true) {
		if (recv(peerSocket, RxBuffer, maxPacketSize, 0) == -1)
			return false;
		pM = PacketManager(RxBuffer);
		cout << "Sequence :" << pM.getPacket()->getSequence() << "\n";
		if (pM.getPacket()->getSequence() == sequence) {
			break;
		}
	}

	if (sending.joinable()) {
		sending.join();
	}

	//pM = PacketManager(RxBuffer);
	if (pM.getPacket()->getAck() == 1) {
		exit.set_value(1);
		cout << "promise set";
		
	} else {
		return false;
	}

	// set buffer
	memset(RxBuffer, '\0', maxPacketSize);
	// recv next sequence packet for data
	sequence++;
	cout << "Recieve data" << sequence << "\n";
	while (true) {
		if (recv(peerSocket, RxBuffer, maxPacketSize, 0) == -1)
			return false;
		pM = PacketManager(RxBuffer);
		if (pM.getPacket()->getSequence() == sequence) {
			break;
		}
	}
	//recv(peerSocket, RxBuffer, maxPacketSize, 0); // recv data
	// send ack

	/*while (pM.getPacket()->getSequence() != sequence) {
		pM.getPacket()->incrementSequence();

	}*/
	sequence++;
	pM.getPacket()->setFin(1);
	pM.getPacket()->incrementSequence();
	std::promise<int> exits;
	std::future<int> futures = exits.get_future();
	cout << "Send Ack" << sequence << "\n";
	thread sendingAck(sendThread, peerSocket, pM.getPacket()->serialize(), std::move(futures));

	if (sendingAck.joinable()) {
		sendingAck.join();
	}

}

bool sendServerPacket(SOCKET socket_client, PacketManager& pM) {

	char RxBuffer[maxPacketSize] = {};
	// for sending thread
	std::promise<int> exit;
	std::future<int> future = exit.get_future();


	int sequence = pM.getPacket()->getSequence();

	// send ack
	pM.getPacket()->setAck(1);

	pM.getPacket()->incrementSequence();
	sequence++;

	cout << "Sending Ack: " << sequence << "\n";
	thread sending(sendThread, socket_client, pM.getPacket()->serialize(), std::move(future));
	//send(socket_client, pM->getPacket()->serialize(), maxPacketSize, 0);


	//send data
	pM.getPacket()->setAck(0);

	pM.getPacket()->incrementSequence();
	sequence++;

	std::promise<int> exits;
	std::future<int> futures = exits.get_future();

	cout << "Sending data: " << sequence << "\n";
	thread sent(sendThread, socket_client, pM.getPacket()->serialize(), std::move(futures));
	sequence++;
	//send(socket_client, pM->getPacket()->serialize(), maxPacketSize, 0);
	// check ack
	cout << "Recieve Ack " << sequence << "\n";
	while (true) {
		if (recv(socket_client, RxBuffer, maxPacketSize, 0) == -1)
			return false;
		pM = PacketManager(RxBuffer);
		if (pM.getPacket()->getSequence() == sequence) {
			break;
		}
	}

	if (pM.getPacket()->getFin() == 1) {
		exit.set_value(1);
		cout << "promise set (Fin)\n";

	}
	else {
		return false;
	}

	if (sent.joinable()) {
		sent.join();
	}
	if (sending.joinable()) {
		sending.join();
	}
	//sequence++;

	return true;
}