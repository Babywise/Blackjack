#include <QtWidgets/QApplication>

#include "AlertsQT.h"
#include "BetBoxQT.h"
#include "BlackJackHomePage.h"
#include "CasinoHomePage.h"
#include "DAO.h"
#include "GamePageQT.h"
#include "helperfunctions.h"
#include "LoginDialog.h"
#include "SelectTable.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	/*AlertsQT alert;
    alert.show();

	BetBoxQT bets;
	bets.show();*/

	GamePageQT game;
	game.show();


    return a.exec();
}
