#pragma once
#include "Account.h"
#include <string>
using namespace std;
#include <stdio.h>
#include <iostream>


void printMenu();
account* Login(string username, string password);
account* signup(string username, string password, string name, int age);

