#include "pwdchangedlg.h"
#include "ui_pwdchangedlg.h"

PwdChangeDlg::PwdChangeDlg(Controller *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwdChangeDlg)
{
    ui->setupUi(this);
    this->controller = controller;
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
    catch(int exec)
    {

    }
}


void PwdChangeDlg::on_oldPwdEdit_textChanged(const QString &arg1)
{
    setBtnStat();
}

void PwdChangeDlg::on_newPwdEdit_textChanged(const QString &arg1)
{
    setBtnStat();
}

void PwdChangeDlg::on_confirmNewPwdEdit_textChanged(const QString &arg1)
{
    setBtnStat();
}
