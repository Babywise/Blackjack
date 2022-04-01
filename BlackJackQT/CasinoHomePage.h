#pragma once

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include "ui_CasinoHomePage.h"
#include "DAO.h"
#include <QVector>
#include "helperfunctions.h"
#include "SelectTable.h"

class CasinoHomePage : public QWidget
{
	Q_OBJECT



private slots: 
	void on_listOfGames_currentItemChanged();
	void on_clickToPlay_clicked(); 
	


public:
	CasinoHomePage(QWidget *parent = Q_NULLPTR);
	~CasinoHomePage();

private:
	Ui::CasinoHomePage ui;
};
