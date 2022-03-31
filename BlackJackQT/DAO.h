#pragma once
#include <QtWidgets/QMainWindow>
#include <QVector>
#include <vector>

using namespace std;
typedef class PlayerData {

}PlayerData;




typedef class RegisterInfo {
	string name;
	string email;
}RegisterInfo;

typedef class ManageInfo {

}ManageInfo;


//Login

bool isAuthenticated(QString userName, QString password);

//Register 

bool isRegistered(QString userName, QString password);


//Casino Homepage 

vector<string> getListOfGameTitles();


//Select Table 

vector<string> getListOfTableInfo();

//Game Page 

vector<PlayerData> getPlayerDataList();
PlayerData getMyPlayerData();
PlayerData getDealerData();
bool isMyTurn();

//Bet Box

bool sendBet(int value);

//ManageFunds 

bool deposit(ManageInfo info);
bool withdraw(ManageInfo info);



