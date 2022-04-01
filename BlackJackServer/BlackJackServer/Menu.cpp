#include "Menu.h"

void printMenuUsers() {
	system("cls");
	std::cout << "1. Join Table\n";
	std::cout << "2. Add Funds\n";
	std::cout << "3. Cash out\n";
	std::cout << "4. Logout\n";
	std::cout << "Enter : ";
}

void printStartMenu() {
	cout << "1. Login\n";
	cout << "2. Signup\n";
	cout << "3. Exit\n\n";
	cout << "Enter :";
}

int getMenuOption() {
	string inputString;
	cin >> inputString;
	int input = atoi(inputString.c_str());
	if (input < 0) {
		input = 0;
	}
	return input;
}

void alertMessage(string message) {
	std::cout << message << std::endl << std::endl;
}

void gameMessages(char* message[]) {
	vector<string> gameMessages; // for gui
	for (int i = 0; i < MAX_LINES; i++) {
		if (message[i] != NULL) {
			std::cout << message[i];
			gameMessages.push_back(message[i]);
		}
		else {
			break;
		}
	}
}

long long getCardNumber() {
	cout << "Enter Card Number ('0') to return : ";
	string inputString;
	cin >> inputString;
	long long input = stoll(inputString.c_str());
	if (input < 0) {
		input = 0;
	}
	return input;
}

int getFundsToAdd() {
	cout << "Enter amount to add ('0') to return : ";
	string inputString;
	cin >> inputString;
	int input = atoi(inputString.c_str());
	if (input < 0) {
		input = 0;
	}
	return input;
}

int getFundsToRemove() {
	cout << "Enter amount to withdraw ('0') to return : ";
	string inputString;
	cin >> inputString;
	int input = atoi(inputString.c_str());
	if (input < 0) {
		input = 0;
	}
	return input;
}

void printUpdateValues(int dealerValue, int* gameValues, int totalGameValues) {
	std::cout << "Dealer has : " << dealerValue << std::endl;
	for (int i = 0; i < totalGameValues; i++) {
		std::cout << "Computer" << i + 1 << " has : " << gameValues[i] << std::endl;
	}
	std::cout << std::endl << std::endl;
}

void printGamesAvailable(int* players, int* maxPlayers, int availableTables) {

	system("cls");
	for (int i = 0; i < availableTables; i++) {
		std::cout << i+1 << ". " << players[i] << "/" << maxPlayers[i] << " Players\n";
	}
	std::cout << availableTables + 1 << ". Back\n";
	std::cout << "Enter : ";
}

void getLoginInfo(PacketLogin &pL) {
	system("cls");
	cout << "************************     BLACKJACK     ****************************\n-------- LOGIN ----------\n";
	cout << "Username : ";
	string username;
	cin >> username;
	pL.PacketLoginSetUsername(username);
	cout << "Password :";
	string password;
	cin >> password;
	pL.PacketLoginSetPassword(password);
}

void getSignupInfo(PacketSignUp &pS) {
	system("cls");
	cout << "************************     BLACKJACK     ****************************\n-------- SIGNUP ----------\n";
	cout << "Name : ";
	string name;
	cin >> name;
	pS.PacketSignUpSetName(name);
	cout << "Username : ";
	string username;
	cin >> username;
	pS.PacketSignUpSetUsername(username);
	cout << "Password :";
	string password;
	cin >> password;
	pS.PacketSignUpSetPassword(password);
	cout << "Age :";
	int age;
	cin >> age;
	pS.PacketSignUpSetAge(age);
}
