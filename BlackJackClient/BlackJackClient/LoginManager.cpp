#include "loginManager.h"

void printMenu() {
	system("cls");
	cout << "1. Login\n";
	cout << "2. Signup\n";
	cout << "3. Exit\n\n";
	cout << "Enter :";
}
account* Login(string username, string password) {
	system("cls");
	account* acc = new account("", 0, 0, "");
	acc = login(username, password);
	return acc;

}
account* signup(string username, string password, string name, int age) {
	system("cls");
	account* acc = new account("", 0, 0, "");
	acc =createAccount(username, password, age, name);
	return acc;
}
