#include "configdlg.h"
#include "ui_configdlg.h"

ConfigDlg::ConfigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDlg)
{
    ui->setupUi(this);
}

ConfigDlg::ConfigDlg(Controller *controller, QWidget *parent) :
    ConfigDlg(parent),
    controller(controller)
{

}

ConfigDlg::~ConfigDlg()
{
    delete ui;
}

void ConfigDlg::on_pushButton_clicked()
{
    controller->modifyConfig(ui->diffBox->currentData().toInt(), ui->wordsBox->currentData().toInt());
    accept();
}
