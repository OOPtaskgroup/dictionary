#include "regdlg.h"
#include "wordnumdlg.h"
#include "ui_regdlg.h"
#include "controller.h"
#include <QMessageBox>

RegDlg::RegDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDlg)
{
    ui->setupUi(this);
}

RegDlg::RegDlg(QWidget *parent, Controller *controller) :
    RegDlg(parent),
    controller(controller)
{

}

RegDlg::~RegDlg()
{
    delete ui;
}

bool RegDlg::checkInput()
{
    if (ui->usrEdit->text().size() == 0)
        return false;
    if (ui->pwdEdit->text().size() < 6)
        return false;
    if (ui->pwdEdit->text() != ui->pwdConfirmEdit->text())
        return false;
    for (auto i : ui->usrEdit->text())
        if (!(*i).isLetterOrNumber())
            return false;
    for (auto i : ui->pwdEdit->text())
        if (!(*i).isLetterOrNumber())
            return false;
    for (auto i : ui->pwdConfirmEdit->text())
        if (!(*i).isLetterOrNumber())
            return false;
    return true;
}

void RegDlg::keyPressEvent(QKeyEvent *)
{
    if (checkInput())
    {
        ui->regBtn->setEnabled(true);
    }
    else
    {
        ui->regBtn->setEnabled(false);
    }
}

void RegDlg::on_regBtn_clicked()
{
    try
    {
        controller->userRegister();
    }
    catch(RegException err)
    {
        QMessageBox warningBox(QMessageBox::Warning, "≥ˆ¥Ì¿≤£°", err.info);
        warningBox.setStandardButtons(QMessageBox::Retry);
        warningBox.setButtonText(QMessageBox::Retry, "÷ÿ ‘");
        warningBox.exec();
        return;
    }
    WordNumDlg wordNumDlg;
    wordNumDlg.exec();
    accept();
}
