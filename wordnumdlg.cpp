#include "wordnumdlg.h"
#include "ui_wordnumdlg.h"

WordNumDlg::WordNumDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WordNumDlg)
{
    ui->setupUi(this);
}

WordNumDlg::~WordNumDlg()
{
    delete ui;
}
