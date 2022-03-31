#pragma once

#include <QDialog>
#include "ui_LoginDialog.h"

class LoginDialog : public QDialog, public Ui::LoginDialog
{
	Q_OBJECT

public:
	LoginDialog(QWidget *parent = Q_NULLPTR);
	~LoginDialog();
};
