#include "BlackJackHomePage.h"

BlackJackHomePage::BlackJackHomePage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

BlackJackHomePage::~BlackJackHomePage()
{
}

void BlackJackHomePage::on_loginButton_clicked()
{
    clearLabelTextBox(ui.warningSign);
    LoginDialog dialog(this);
    
    if (dialog.exec()) {
        QString userName = dialog.userNameEdit->text();
        QString password = dialog.passwordEdit->text();

        if (!userName.isEmpty() && !password.isEmpty())
        {
            if (isAuthenticated(userName, password))  //DAO call
            {
                CasinoHomePage* CHP = new CasinoHomePage();
                CHP->show();
                hide();
            }
            else
            {
                setLabelTextBox(ui.warningSign, "Invalid User and Password", Qt::blue, Qt::red, 25,false,false, Qt::AlignCenter);
            }

        }
        else
        {
            //ui.warningSign->setText("Please enter BOTH email and password");
            setLabelTextBox(ui.warningSign, "Please enter BOTH email and password", Qt::yellow, Qt::red, 25, false, false, Qt::AlignCenter);

        }
    }
}
