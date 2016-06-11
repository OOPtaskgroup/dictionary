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
}

LoginDlg::LoginDlg(Controller *controller, QWidget *parent) :
    LoginDlg(parent)
{
    this->controller = controller;
    ui->loginBtn->setDefault(true);
    auto defaultUser = controller->getDefaultUser();
    ui->usrEdit->setText(QString::fromStdString(defaultUser.first));
    ui->pwdEdit->setText(QString::fromStdString(defaultUser.second));
    if (defaultUser.first == "")
    {
        ui->usrEdit->setFocus();
    }
    else if (defaultUser.second == "")
    {
        ui->pwdEdit->setFocus();
        ui->remCheck->setChecked(false);
    }
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_loginBtn_clicked()
{
    try
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        controller->Login(ui->usrEdit->text().toStdString(), ui->pwdEdit->text().toStdString(), ui->remCheck->isChecked());
        QApplication::restoreOverrideCursor();
        accept();
    }
    catch(PasswordNotCorrectException exce)
    {
        QApplication::restoreOverrideCursor();
        QMessageBox warningBox(QMessageBox::Warning, "出错啦！", "密码错误！");
        warningBox.setStandardButtons(QMessageBox::Retry);
        warningBox.setButtonText(QMessageBox::Retry, "重试");
        warningBox.exec();
        ui->pwdEdit->clear();
        ui->pwdEdit->setFocus();
    }
    catch(ItemNotFoundException exce)
    {
        QApplication::restoreOverrideCursor();
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

void LoginDlg::on_usrEdit_textChanged(const QString &)
{
    ui->pwdEdit->clear();
}
