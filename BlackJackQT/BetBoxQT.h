#pragma once

#include <QWidget>
#include "ui_BetBoxQT.h"

class BetBoxQT : public QWidget
{
	Q_OBJECT

public:
	BetBoxQT(QWidget *parent = Q_NULLPTR);
	~BetBoxQT();

private:
	Ui::BetBoxQT ui;
};
