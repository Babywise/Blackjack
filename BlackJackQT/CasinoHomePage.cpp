#include "CasinoHomePage.h"




CasinoHomePage::CasinoHomePage(QWidget *parent)
	: QWidget(parent)
{  
    ui.setupUi(this);

    vector<string> myGameTitle = getListOfGameTitles(); //this is an API call from DAO that provides a vector of strings
    for (auto a : myGameTitle)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a), ui.listOfGames);
        ui.listOfGames->setCurrentItem(item);

    }
}

CasinoHomePage::~CasinoHomePage()
{
}


void CasinoHomePage::on_listOfGames_currentItemChanged()
{
    QListWidgetItem* curItem = ui.listOfGames->currentItem();
    

    if (curItem) {
        
        ui.gameTitle->setText(curItem->text());

        setLabelTextBox(ui.gameTitle, curItem->text(), Qt::transparent, Qt::black, 16, true, false, Qt::AlignCenter);
    }
    else {
        ui.gameTitle->setText("No Game Selected");
    }
}

void CasinoHomePage::on_clickToPlay_clicked() {
    
    BlackJackHomePage* BJHP = new BlackJackHomePage();
    BJHP->show();
    hide();

}