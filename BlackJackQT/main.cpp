#include <QtWidgets/QApplication>

#include "AlertsQT.h"
#include "BetBoxQT.h"
#include "GamePageQT.h"

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
