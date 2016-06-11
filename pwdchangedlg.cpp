#include "pwdchangedlg.h"
#include "ui_pwdchangedlg.h"

PwdChangeDlg::PwdChangeDlg(Controller *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwdChangeDlg)
{
    ui->setupUi(this);
    this->controller = controller;
    this->setStyleSheet(controller->setTheme("pwdchange"));
}

PwdChangeDlg::~PwdChangeDlg()
{
    delete ui;
}

bool PwdChangeDlg::checkInput()
{
    if (ui->oldPwdEdit->text().size() < 6)
        return false;
    if (ui->newPwdEdit->text().size() < 6)
        return false;
    if (ui->confirmNewPwdEdit->text() != ui->newPwdEdit->text())
        return false;
    for (auto i : ui->oldPwdEdit->text())
        if (!i.isLetterOrNumber())
            return false;
    for (auto i : ui->newPwdEdit->text())
        if (!i.isLetterOrNumber())
            return false;
    for (auto i : ui->confirmNewPwdEdit->text())
        if (!i.isLetterOrNumber())
            return false;
    return true;
}

void PwdChangeDlg::setBtnStat()
{
    if (checkInput())
    {
        ui->confirmBtn->setEnabled(true);
    }
    else
    {
        ui->confirmBtn->setEnabled(false);
    }
}

void PwdChangeDlg::on_confirmBtn_clicked()
{
    try
    {
        controller->userModifyPassword(controller->getActiveUser(), ui->oldPwdEdit->text().toStdString(), ui->newPwdEdit->text().toStdString());
        accept();
    }
    catch(PasswordNotCorrectException exec)
    {
        QMessageBox warningBox(QMessageBox::Warning, "出错啦！", "原密码错误！");
        warningBox.setStandardButtons(QMessageBox::Retry);
        warningBox.setButtonText(QMessageBox::Retry, "重试");
        warningBox.exec();
        ui->oldPwdEdit->clear();
        ui->oldPwdEdit->setFocus();
        ui->newPwdEdit->clear();
        ui->confirmNewPwdEdit->clear();
    }
}

void PwdChangeDlg::on_oldPwdEdit_textChanged(const QString &)
{
    setBtnStat();
}

void PwdChangeDlg::on_newPwdEdit_textChanged(const QString &)
{
    setBtnStat();
}

void PwdChangeDlg::on_confirmNewPwdEdit_textChanged(const QString &)
{
    setBtnStat();
}
