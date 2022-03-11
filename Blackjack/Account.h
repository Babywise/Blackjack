#pragma once
#pragma once
#include <string>
using namespace std;
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <winsock.h>

struct info {
	string username;
	string password;
	int age;
	string name;

};
class account {
public:
	account(string username, float funds, int age, string name);
	string getUsername();
	float getFunds();
	int getAge();
	string getName();
	void reduceFunds(float funds);
	void addFunds(float funds);
	SOCKET connection = {};

private:
	string username;
	float funds;
	int age;
	string name;

};

account* createAccount(string username, string password, int age, string name); // encrypted password recieved from client
info getSignupInfo();
info getLoginInfo();
account* login(string username, string password);
bool userExists(string username);
