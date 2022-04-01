#pragma once

#include <QWidget>
#include "ui_SelectTable.h"
#include "DAO.h"
#include "helperfunctions.h"
#include "QtWidgets/qmainwindow.h"
//#include "GamePageQT.h"

class SelectTable : public QWidget
{
	Q_OBJECT
private slots:
	void on_listOfTables_currentItemChanged();
	void on_clickToJoin_clicked();
public:
	SelectTable(QWidget *parent = Q_NULLPTR);
	~SelectTable();

private:
	Ui::SelectTable ui;
};
