#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_BlackJackQT.h"

class BlackJackQT : public QMainWindow
{
    Q_OBJECT

public:
    BlackJackQT(QWidget *parent = Q_NULLPTR);

private:
    Ui::BlackJackQTClass ui;
};
