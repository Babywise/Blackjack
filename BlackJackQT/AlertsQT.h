#pragma once

#include <QWidget>
#include "ui_AlertsQT.h"

class AlertsQT : public QWidget
{
	Q_OBJECT

public:
	AlertsQT(QWidget *parent = Q_NULLPTR);
	~AlertsQT();

private:
	Ui::AlertsQT ui;
};
