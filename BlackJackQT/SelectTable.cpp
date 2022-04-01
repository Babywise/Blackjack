#include "SelectTable.h"

SelectTable::SelectTable(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    vector<string> myTableTitle = getListOfTableInfo(); //this is an API call from DAO that provides a vector of strings
    for (auto a : myTableTitle)
    {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a), ui.listOfTables);
        ui.listOfTables->setCurrentItem(item);

    }
}

SelectTable::~SelectTable()
{
}


void SelectTable::on_listOfTables_currentItemChanged()
{
    QListWidgetItem* curItem = ui.listOfTables->currentItem();


    if (curItem) {

        //ui.tableTitle->setText(curItem->text());

        setLabelTextBox(ui.tableTitle, curItem->text(), Qt::transparent, Qt::black, 16, true, false, Qt::AlignCenter);
    }
    else {
        setLabelTextBox(ui.tableTitle, "No Table Selected...", Qt::transparent, Qt::black, 16, true, false, Qt::AlignCenter);
    }
}

void SelectTable::on_clickToJoin_clicked() {

    //GamePageQT* GPQT = new GamePageQT();
    //GamePageQT->show();
   // hide();

}