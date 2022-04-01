//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Winsock.h"
#include <thread>
#include "Server.h"
#include "Logging.h"
//ErrorLog("Error file writing", "High");
//DataLog("Recieved Ack" + to_string(3));
int main() {
	srand(time(NULL));
	//printf("Random Seeded...\n");
	printf("Random Seeded...\n");
	DataLog("Random Seeded...");
	//printf("Creating Games... \n");
	printf("Creating Games... \n");
	DataLog("Creating Games... ");
	blackjack* games[NUMBEROFTABLES] = {};
	for (int i = 0; i < NUMBEROFTABLES; i++) {
		games[i] = new blackjack();
		//printf("Game %d created... \n", i + 1);
		printf("Game %d created... \n",i + 1);
		DataLog("Game %d created... \n" + to_string(i) + to_string(1));
	}
	
	//printf("Cleaning WSA... \n");
	printf("Cleaning WSA... \n");
	DataLog("Cleaning WSA... ");
	WSACleanup();
	// initialize

	initializeWindowsSockets();
	printf("Config the local address... \n");
	DataLog("Config the local address... ");
	struct addrinfo* bind_address = ConfigureLocalAddress();
	printf("Creating Socket... \n");
	DataLog("Creating Socket... ");
	SOCKET socket_listen = CreateBindListeningSocket(bind_address);
	printf("Start Listening... \n");
	DataLog("Start Listening... ");
	StartListeningForConnections(socket_listen);

	thread threads; // a thread that is detached for every connection
	//SOCKET socket_client[MAXCONNECTIONS]; // list of sockets for active connections
	SOCKET socket_client; // list of sockets for active connections

	int b = 0;// b decides which socket thread connection to take.

	// creates a new thread to handle a client every time a new connection is made
	while (b < MAXCONNECTIONS) {
		printf("Waiting for connection... \n");
		DataLog("Waiting for connection... ");
		socket_client = WaitForAndAcceptConnection(socket_listen);
		//socket_client[b] = WaitForAndAcceptConnection(socket_listen);
		handle_Client(socket_client, games, b);
		//threads = thread(handle_Client, socket_client[b], games, b);
		//threads.detach();
		b++;
	}

	// insert server side thread to handle server stuff such as shutdown
	exit(2);
}

