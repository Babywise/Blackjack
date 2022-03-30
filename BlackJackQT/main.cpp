#include "BlackJackQT.h"
#include  "AlertsQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //BlackJackQT w;
	AlertsQT w;
    w.show();
    return a.exec();
}
