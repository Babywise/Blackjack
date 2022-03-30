#pragma once

#include <QWidget>
#include "ui_BlackJackHomePage.h"

class BlackJackHomePage : public QWidget
{
	Q_OBJECT

public:
	BlackJackHomePage(QWidget *parent = Q_NULLPTR);
	~BlackJackHomePage();

private:
	Ui::BlackJackHomePage ui;
};
