#include "DAO.h"



//Login
bool isAuthenticated(QString userName, QString password)
{
    //1.connect to database 
    //2. send api request to see if user exists 
    //3. receive true or false
    srand(time(NULL));
    return rand() % 2;
}
//Register 

bool isRegistered(QString username, QString password) {

    string name = username.toStdString();
    string pw = username.toStdString();

    //send an API call with QString paramaters, username and password

    return true;

}



//Casino Homepage 

vector<string> getListOfGameTitles() {

    //return an API call with a vector of strings that showcase the titles of Games we have
    //(Currently it would only be a vector of size 1 with title "Blackjack") 

    vector<string> myvector; 
   myvector.push_back("BLACKJACK");
   myvector.push_back("CHECKERS");  
   myvector.push_back("CHESS");

    return myvector;
}

//Select Table 

vector<TableInfo> getTableInfoList() {
    vector<TableInfo> myvector; 



    return myvector; 

}

//Game Page 

vector<PlayerData> getPlayerDataList() {

    vector<PlayerData> myvector; 

    return myvector; 
}
PlayerData getMyPlayerData() {
    PlayerData myPlayer;

    return myPlayer;
}
PlayerData getDealerData() {
    PlayerData myDealer; 

    return myDealer; 
}
bool isMyTurn() {

    return true;
}

//Bet Box

bool sendBet(int value) {

    return true;

}

//ManageFunds 

bool deposit(ManageInfo info, float value) {

    return true;
}
bool withdraw(ManageInfo info, float value) {

    return true;

}