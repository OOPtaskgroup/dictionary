#include "exmanagedlg.h"
#include "ui_exmanagedlg.h"

ExManageDlg::ExManageDlg(Controller* controller, WordData *word, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExManageDlg)
{
    ui->setupUi(this);
    this->controller = controller;
    this->setStyleSheet(controller->setTheme("example"));
    this->srcWord = word;
    setItem();
}

ExManageDlg::~ExManageDlg()
{
    delete ui;
}

void ExManageDlg::on_exList_clicked(const QModelIndex &index)
{
    ui->detailBrowser->setText(ui->exList->currentItem()->text());
}

void ExManageDlg::on_delBtn_clicked()
{
    controller->delExample(srcWord, ui->exList->currentItem()->text().toStdString());
    setItem();
}

void ExManageDlg::on_addBtn_clicked()
{
    AddExDlg addExDlg(controller, srcWord, this);
    addExDlg.exec();
    setItem();
}

void ExManageDlg::setItem()
{
    ui->exList->clear();
    auto examples = controller->getExample(srcWord);
    for (auto i = examples.begin(); i != examples.end(); ++i)
    {
        ui->exList->addItem(QString::fromStdString(*i));
    }
}
