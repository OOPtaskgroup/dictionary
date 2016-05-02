#include "logindlg.h"
#include "ui_logindlg.h"
#include "controller.h"
#include <QMessageBox>
LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    if (Login(ui->usrEdit->text(), ui->pwdEdit->text()))
    {
        accept();
    }
    else
    {
        QMessageBox
    }
}
