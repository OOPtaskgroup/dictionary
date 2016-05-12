#include "logindlg.h"
#include "regdlg.h"
#include "ui_logindlg.h"
#include "controller.h"
#include <QMessageBox>
#include "itemnotfoundexception.h"
#include "passwordnotcorrectexception.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    ui->loginBtn->setDefault(true);
    ui->usrEdit->setFocus();
}

LoginDlg::LoginDlg(Controller *controller, QWidget *parent) :
    LoginDlg(parent)
{
    this->controller = controller;
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    try
    {
        controller->Login(ui->usrEdit->text().toStdString(), ui->pwdEdit->text().toStdString());
        accept();
    }
    catch(PasswordNotCorrectException exce)
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
