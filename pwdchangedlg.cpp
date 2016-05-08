#include "pwdchangedlg.h"
#include "ui_pwdchangedlg.h"

PwdChangeDlg::PwdChangeDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PwdChangeDlg)
{
    ui->setupUi(this);
}

PwdChangeDlg::~PwdChangeDlg()
{
    delete ui;
}
