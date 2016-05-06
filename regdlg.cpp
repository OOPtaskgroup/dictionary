#include "regdlg.h"
#include "configdlg.h"
#include "ui_regdlg.h"
#include "controller.h"
#include <QMessageBox>
#include "itemalreadyexistexception.h"

RegDlg::RegDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDlg)
{
    ui->setupUi(this);
}

RegDlg::RegDlg(Controller *controller, QWidget *parent) :
    RegDlg(parent)
{
    this->controller = controller;
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
        if (!i.isLetterOrNumber())
            return false;
    for (auto i : ui->pwdEdit->text())
        if (!i.isLetterOrNumber())
            return false;
    for (auto i : ui->pwdConfirmEdit->text())
        if (!i.isLetterOrNumber())
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
        controller->userRegister(ui->usrEdit->text().toStdString(), ui->pwdEdit->text().toStdString());
        ConfigDlg configDlg(controller, this);
        configDlg.exec();
        accept();
    }
    catch(ItemAlreadyExistException exce)
    {
        QMessageBox warningBox(QMessageBox::Warning, "��������", "�û��Ѵ��ڣ�");
        warningBox.setStandardButtons(QMessageBox::Retry);
        warningBox.setButtonText(QMessageBox::Retry, "����");
        warningBox.exec();
        return;
    }
}
