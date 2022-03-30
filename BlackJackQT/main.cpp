#include "BlackJackQT.h"
#include  "AlertsQT.h"
#include "BetBoxQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //BlackJackQT w;
	AlertsQT alert;
    alert.show();
	BetBoxQT bets;
	bets.show();
    return a.exec();
}
