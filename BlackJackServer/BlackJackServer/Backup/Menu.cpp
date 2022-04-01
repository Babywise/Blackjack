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

void printGamesAvailable(int* players, int* maxPlayers, int availableTables) {

	system("cls");
	for (int i = 0; i < availableTables; i++) {
		std::cout << i << ". " << players[i] << "/" << maxPlayers[i] << " Players\n";
	}
	std::cout << availableTables << ". Back\n";
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
