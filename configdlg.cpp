#include "configdlg.h"
#include "ui_configdlg.h"
#include "logging.h"

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
    this->setStyleSheet(controller->setTheme("config"));
    ui->diffBox->setCurrentText(QString::number(controller->getConfig().Difficulty()));
    ui->wordsBox->setCurrentText(QString::number(controller->getConfig().DailyNumber()));
    for (int i = 0; i < __themeNumber; ++i)
    {
        if (__themeList[i] == controller->getNowTheme())
        {
            ui->themeBox->setCurrentIndex(i);
            break;
        }
    }
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
    Logging log("Config :: on_confirmBtn_clicked",true);
    log << "INFO modify config" << (ui->diffBox->currentText().toInt()) << " " << (ui->wordsBox->currentText().toInt()) << std::endl;
    controller->modifyConfig(ui->diffBox->currentText().toInt(), ui->wordsBox->currentText().toInt());
    controller->modifyTheme(__themeList[ui->themeBox->currentIndex()]);
    accept();
}

