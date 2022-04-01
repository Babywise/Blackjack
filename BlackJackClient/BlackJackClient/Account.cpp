#include "Account.h"

account::account(string username, float funds, int age, string name) {
	this->age = age;
	this->funds = funds;
	this->name = name;
	this->username = username;
}

void account::addFunds(float funds) {
	this->funds += funds;
	this->save();
}
bool account::save() { // save data to a current account
	fstream f;
	f.open(("./Users/" + this->getUsername()), ios::in);
	if (!f) {
		return false;
	}
	string password;
	getline(f, password);
	f.close();

	f.open(("./Users/" + this->getUsername()), ios::out);
	if (!f) {
		return false;
	}
	f << password << "\n";
	f << this->getFunds() << "\n";
	f << this->getAge() << "\n";
	f << this->getName();
	f.close();

	return true;
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




bool Save(string password, account* acc)// done in this object used to create an account
{

	fstream f;
	f.open(("./Users/" + acc->getUsername()), ios::out);
	if (!f) {
		return false;
	}
	f << password << "\n";
	f << acc->getFunds() << "\n";
	f << acc->getAge() << "\n";
	f << acc->getName();
	f.close();
	return true;
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

		if (Save(temp, newAccount)) {
			return newAccount;
		}
		else {
			newAccount = new account("", 0, 0, "");
			return newAccount;
		}

	}
	else {
		newAccount = new account("", 0, 0, "");
		return newAccount;
	}
}