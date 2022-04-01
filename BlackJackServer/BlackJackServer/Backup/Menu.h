#pragma once
#include <iostream>
#include "PacketManager.h"

void printMenuUsers();
void printGamesAvailable(int* players, int* maxPlayers, int availableTables);
void printStartMenu();
int getMenuOption();
void getLoginInfo(PacketLogin &pL);
void getSignupInfo(PacketSignUp &pS);