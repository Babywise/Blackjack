#define _CRT_SECURE_NO_WARNINGS
#pragma once
#define ERRORLOG "./Logs/ErrorLog.txt"
#define DATALOG "./Logs/DataLog.txt"
#include <fstream>
#include <iostream>
#include <direct.h>
#include <ctime>
using namespace std;
void ErrorLog(string message, string Severity);
void DataLog(string message);