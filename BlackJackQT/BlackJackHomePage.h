#pragma once

#include "ui_BlackJackHomePage.h"
#include "CasinoHomePage.h"
#include "helperfunctions.h"
#include "ui_CasinoHomePage.h"
#include "LoginDialog.h"
#include "DAO.h"

class BlackJackHomePage : public QMainWindow, public Ui::BlackJackHomePage
{
	Q_OBJECT
private slots: 
	void on_loginButton_clicked();

public:
	BlackJackHomePage(QWidget *parent = Q_NULLPTR);
	~BlackJackHomePage();

private:
	Ui::BlackJackHomePage ui;
};
