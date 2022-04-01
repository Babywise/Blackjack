#include "ServerThreads.h"
#include "Logging.h"

// deal with requests for the given server here
int sendMessage(SOCKET socket_client, Packet* payload) {
	send(socket_client, (char*)&payload, sizeof(payload), 0); // <- sizeof here will not work, need to use maxPacketSize
	return 1;
}

void sendThread(SOCKET sock, char* buffer, std::future<int> future) {
	Sleep(250);
	int MAX = 0;
	while (future.wait_for(std::chrono::milliseconds(25)) == std::future_status::timeout && MAX < 20) {
		send(sock, buffer, maxPacketSize, 0);
		MAX++;
	}
	cout << "Exiting thread..";
	DataLog("Exiting thread..");
	return;
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
	DataLog("Sending Ack: " + to_string(sequence));
	thread sending(sendThread, socket_client, pM.getPacket()->serialize(), std::move(future));
	//send(socket_client, pM->getPacket()->serialize(), maxPacketSize, 0);


	//send data
	pM.getPacket()->setAck(0);

	pM.getPacket()->incrementSequence();
	sequence++;

	std::promise<int> exits;
	std::future<int> futures = exits.get_future();

	cout << "Sending data: " << sequence << "\n";
	DataLog("Sending data: " + to_string(sequence));
	thread sent(sendThread, socket_client, pM.getPacket()->serialize(), std::move(futures));
	sequence++;
	//send(socket_client, pM->getPacket()->serialize(), maxPacketSize, 0);
	// check ack
	cout << "Recieve Ack " << sequence << "\n";
	DataLog("Recieve Ack " + to_string(sequence));
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
		DataLog("promise set(Fin)");

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

bool sendClientPacket(SOCKET peerSocket, PacketManager& pM) {

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

	cout << "Sending request :" << sequence + "\n";
	DataLog("Sending request :" + sequence);
	thread sending(sendThread, peerSocket, pM.getPacket()->serialize(), std::move(future));
	// V1.0  ------------   //send(peerSocket, pM->getPacket()->serialize(), maxPacketSize, 0);
	char RxBuffer[maxPacketSize] = {};
	sequence++;
	// recv next sequence packet
	//cout << "Recieve Ack" << sequence << "\n";
	printf("Recieve Ack ", sequence);
	DataLog("Recieve Ack " + sequence);
	while (true) {
		if (recv(peerSocket, RxBuffer, maxPacketSize, 0) == -1)
			return false;
		pM = PacketManager(RxBuffer);
		cout << "Sequence :" << pM.getPacket()->getSequence() << "\n";
		DataLog("Sequence :" + to_string(pM.getPacket()->getSequence()));
		if (pM.getPacket()->getSequence() == sequence) {
			break;
		}
	}
	//pM = PacketManager(RxBuffer);
	if (pM.getPacket()->getAck() == 1) {
		exit.set_value(1);
		cout << "promise set";
		DataLog("promise set");

	}
	else {
		return false;
	}
	sending.join();

	// set buffer
	memset(RxBuffer, '\0', maxPacketSize);
	// recv next sequence packet for data
	sequence++;
	cout << "Recieve data" << sequence << "\n";
	DataLog("Recieve data" + sequence);
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
	DataLog("Send Ack" + sequence);
	thread sendingAck(sendThread, peerSocket, pM.getPacket()->serialize(), std::move(futures));

	if (sending.joinable()) {
		sending.join();
	}
	if (sendingAck.joinable()) {
		sendingAck.join();
	}

}