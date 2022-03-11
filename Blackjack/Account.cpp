#include "Account.h"

account::account(string username, float funds, int age, string name) {
	this->age = age;
	this->funds = funds;
	this->name = name;
	this->username = username;
}

void account::addFunds(float funds) {
	this->funds += funds;
	fstream f;
	f.open(("./Users/" + this->getUsername()), ios::in);
	if (!f) {
		//failed
	}
	string password;
	getline(f, password);
	f.close();

	f.open(("./Users/" + this->getUsername()), ios::out);
	if (!f) {
		//failed
	}
	f << password << "\n";
	f << this->getFunds() << "\n";
	f << this->getAge() << "\n";
	f << this->getName();
	f.close();
	
}
string account::getUsername() {
	return this->username;
}
float account::getFunds() {
	return this->funds;
}
int account::getAge() {
	return this->age;
}
string account::getName() {
	return this->name;
}




// getters
account* login(string username, string password) {
	if (userExists(username)) {
		fstream f;
		string input;
		hash<string> h;
		const size_t value = h(password);
		string temp = to_string(value);

		string tempName;
		string tempAge;
		string tempFunds;


		f.open(("./Users/" + username), ios::in);
		getline(f, input);
		if (input == temp) { // password matches
			getline(f, tempFunds);// funds
			getline(f, tempAge); // age
			getline(f, tempName); // name
			f.close();
			account* acc = new account(username, stof(tempFunds), stoi(tempAge), tempName);
			return acc;
		}
		else {
			account* acc = new account("", 0, 0, "");
			return acc;
		}
		// if password from file == temp GOOD
	}
	else {
		account* acc = new account("", 0, 0, "");
		return acc;
	}

}
bool userExists(string username) { // check if user exists
	fstream f;
	f.open(("./Users/" + username), ios::in);

	if (!f) {

		return false;

	}
	else {
		f.close();
		return true;
	}

}

void account::reduceFunds(float funds) {
	this->funds -= funds;
}

account* createAccount(string username, string password, int age, string name) {
	account* newAccount = new account(username, 0, age, name);
	if (!userExists(username)) {
		hash<string> h;
		const size_t value = h(password);
		string temp = to_string(value);

		fstream f;
		f.open(("./Users/" + newAccount->getUsername()), ios::out);
		if (!f) {
			newAccount = new account("", 0, 0, "");
			return newAccount;
		}
		f << password << "\n";
		f << newAccount->getFunds() << "\n";
		f << newAccount->getAge() << "\n";
		f << newAccount->getName();
		f.close();
		return newAccount;

	}
	else {
		newAccount = new account("", 0, 0, "");
		return newAccount;
	}
}

info getSignupInfo() {
	info packet;
	system("cls");
	cout << "************************     BLACKJACK     ****************************\n-------- SIGNUP ----------\n";
	cout << "Name : ";
	string name;
	cin >> name;
	packet.name = name;
	cout << "Username : ";
	string username;
	cin >> username;
	packet.username = username;
	cout << "Password :";
	string password;
	cin >> password;
	packet.password = password;
	cout << "Age :";
	int age;
	cin >> age;
	packet.age = age;
	return packet;
}
info getLoginInfo() {
	info packet;
	system("cls");
	cout << "************************     BLACKJACK     ****************************\n-------- LOGIN ----------\n";
	cout << "Username : ";
	string username;
	cin >> username;
	packet.username=username;
	cout << "Password :";
	string password;
	cin >> password;
	packet.password=password;
	return packet;
}