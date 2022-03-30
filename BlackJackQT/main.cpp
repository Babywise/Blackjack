#include "BlackJackQT.h"
#include <QtWidgets/QApplication>
#include "CasinoHomePage.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackJackQT w;
    CasinoHomePage h;
    //w.show();
    h.show();

	cout << "Hello World!" << endl;

    return a.exec();
}
