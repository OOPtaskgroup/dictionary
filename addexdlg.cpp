#include "addexdlg.h"
#include "ui_addexdlg.h"

AddExDlg::AddExDlg(Controller *controller, WordData *word, QWidget *parent) :
    QDialog(parent),
    controller(controller),
    srcWord(word),
    ui(new Ui::AddExDlg)
{
    ui->setupUi(this);
    this->setStyleSheet(controller->setTheme("add"));
}

AddExDlg::~AddExDlg()
{
    delete ui;
}

void AddExDlg::on_confirmBtn_clicked()
{
    controller->addExample(srcWord, (ui->exEdit->toPlainText() + tr("    ") + ui->transEdit->toPlainText()).toStdString());
    accept();
}
