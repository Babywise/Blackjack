#pragma once

#include "Packet.h"
#include "Winsock.h"
#include <stdbool.h>
#include <string.h>
#include <string>
using namespace std;
struct response {
	int bytes_recieved;
	char* response;
};

#define BUFFER 10000
#define ADDRESS "127.0.0.1"
#define PORT "8080"





void sendMessageServer(Packet pkt, SOCKET peerSocket);


