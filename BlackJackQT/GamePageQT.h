#pragma once

#include <QWidget>
#include "ui_GamePageQT.h"

class GamePageQT : public QWidget
{
	Q_OBJECT

public:
	GamePageQT(QWidget *parent = Q_NULLPTR);
	~GamePageQT();

private:
	Ui::GamePageQT ui;
};
