#include "BlackJackQT.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackJackQT w;
    w.show();
    return a.exec();
}
