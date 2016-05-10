#include "configdlg.h"
#include "ui_configdlg.h"

ConfigDlg::ConfigDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDlg)
{
    ui->setupUi(this);
}

ConfigDlg::ConfigDlg(Controller *controller, QWidget *parent) :
    ConfigDlg(parent)
{
    this->controller = controller;
    ui->diffBox->setCurrentText(QString::number(controller->getConfig().Difficulty()));
    ui->wordsBox->setCurrentText(QString::number(controller->getConfig().DailyNumber()));
}

ConfigDlg::~ConfigDlg()
{
    delete ui;
}

void ConfigDlg::on_pwdChangeBtn_clicked()
{
    PwdChangeDlg pwdChangeDlg(controller, this);
    pwdChangeDlg.exec();
    ui->confirmBtn->setDefault(true);
}

void ConfigDlg::on_confirmBtn_clicked()
{
    controller->modifyConfig(ui->diffBox->currentText().toInt(), ui->wordsBox->currentText().toInt());
    accept();
}

