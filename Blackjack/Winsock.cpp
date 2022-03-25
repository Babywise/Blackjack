#include "Winsock.h"
#include "Server.h"
#include "PacketManager.h"
#include "Account.h"
#include "windows.h"
#include "iostream"
#include <iostream>      
#include <thread>
#include <Windows.h>
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

SOCKET CreateBindListeningSocket(struct addrinfo* bind_address) {
	SOCKET socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
	if ((socket_listen) == INVALID_SOCKET) {
		fprintf(stderr, "Socket() failed, Exiting with error (%d)\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
		fprintf(stderr, "bind() failed, exiting with error (%d)\n", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(bind_address);
	return socket_listen;
}

void StartListeningForConnections(SOCKET socket_listen) {
	if (listen(socket_listen, MAXLISTENERS) < 0)
	{
		fprintf(stderr, "listen() failed, exiting with error of (%d)\n", WSAGetLastError());
		exit(1);
	}
}

SOCKET WaitForAndAcceptConnection(SOCKET socket_listen) {
	struct sockaddr_storage client_address;
	socklen_t client_len = sizeof(client_address);
	SOCKET socket_client = accept(socket_listen, (struct sockaddr*)&client_address, &client_len);
	if ((socket_client) == INVALID_SOCKET) {
		fprintf(stderr, "accept() failed. (%d)\n", WSAGetLastError());
		return NULL;

	}
	char address_buffer[DISPLAYBUFFERSIZE];
	getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
	fprintf(stderr, "%s\n", address_buffer);
	return socket_client;

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

struct addrinfo* ConfigureRemoteAddress(char* remoteHost, char remotePort) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	struct addrinfo* peer_address;
	getaddrinfo(0, PORT, &hints, &peer_address);
	return peer_address;
}
