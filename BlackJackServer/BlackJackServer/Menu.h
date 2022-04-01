#pragma once
#include <iostream>
#include "PacketManager.h"
#include <vector>

void printMenuUsers();
void printStartMenu();
int getMenuOption();
void alertMessage(string message);
void gameMessages(char* message[]);
long long getCardNumber();
int getFundsToAdd();
int getFundsToRemove();
void printUpdateValues(int dealerValue, int* gameValues, int totalGameValues);
void printGamesAvailable(int* players, int* maxPlayers, int availableTables);
void getLoginInfo(PacketLogin &pL);
void getSignupInfo(PacketSignUp &pS);