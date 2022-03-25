#include "BlackJackQT.h"
#include <QtWidgets/QApplication>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackJackQT w;
    w.show();

	cout << "Hello World!" << endl;

    return a.exec();
}
