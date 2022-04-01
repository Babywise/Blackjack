#pragma once
#include <string>
using namespace std;
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <winsock.h>
class account {
	string username;
	float funds;
	int age;
	string name;
public:
	account(string username, float funds, int age, string name);
	string getUsername();
	float getFunds();
	int getAge();
	string getName();
	void reduceFunds(float funds);
	void addFunds(float funds);
	SOCKET* connection = {};
protected:
	bool save();
};

account* createAccount(string username, string password, int age, string name); // encrypted password recieved from client
account* login(string username, string password);
bool Save(string password, account* acc);
bool userExists(string username);
