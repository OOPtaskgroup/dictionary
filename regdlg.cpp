#include "regdlg.h"
#include "ui_regdlg.h"

RegDlg::RegDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDlg)
{
    ui->setupUi(this);
}

RegDlg::~RegDlg()
{
    delete ui;
}
