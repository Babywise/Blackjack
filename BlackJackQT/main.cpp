#include "BlackJackQT.h"
#include <QtWidgets/QApplication>
#include "CasinoHomePage.h"
#include "BlackJackHomePage.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlackJackQT w;
    CasinoHomePage h;
    BlackJackHomePage b;
    
    //w.show();
    b.show();
   

	std::cout << "Hello World!" << endl;

    return a.exec();
}
