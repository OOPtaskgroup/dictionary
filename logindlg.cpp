#include "logindlg.h"
#include "regdlg.h"
#include "ui_logindlg.h"
#include "controller.h"
#include <QMessageBox>
#include "itemnotfoundexception.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::LoginDlg(QWidget *parent, Controller *controller) :
    LoginDlg(parent),
    controller(controller)
{
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    try
    {
        Login(ui->usrEdit->text(), ui->pwdEdit->text());
        accept();
    }
    catch(passwordNotCorrectException exce)
    {
        QMessageBox warningBox(QMessageBox::Warning, "出错啦！", "用户名或密码错误！");
        warningBox.setStandardButtons(QMessageBox::Retry);
        warningBox.setButtonText(QMessageBox::Retry, "重试");
        warningBox.exec();
        ui->pwdEdit->clear();
        ui->pwdEdit->setFocus();
    }
    catch(ItemNotFoundException exce)
    {
        QMessageBox warningBox(QMessageBox::Warning, "出错啦！", "该用户不存在！");
        warningBox.setStandardButtons(QMessageBox::Retry);
        warningBox.setButtonText(QMessageBox::Retry, "重试");
        warningBox.exec();
        ui->usrEdit->clear();
        ui->pwdEdit->clear();
        ui->usrEdit->setFocus();
    }
}

void LoginDlg::on_regBtn_clicked()
{
    RegDlg regDlg(controller, this);
    if (regDlg.exec() == QDialog::Accepted)
    {
        accept();
    }
    else
    {
        ui->usrEdit->clear();
        ui->pwdEdit->clear();
        ui->usrEdit->setFocus();
    }
}
