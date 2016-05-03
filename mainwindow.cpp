#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configdlg.h"
#include "recitewindow.h"
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    MainWindow(parent),
    controller(controller)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_configBtn_clicked()
{
    ConfigDlg configDlg(controller, this);
    configDlg.exec();
}

void MainWindow::on_reciteBtn_clicked()
{
    ReciteWindow reciteWindow(ReciteWindow::ReciteMode, controller, this);
    this->hide();
    reciteWindow.show();
}

void MainWindow::on_lookUpBtn_clicked()
{
    if (controller->findWord(ui->wordEdit->text().toStdString()) == nullptr)
    {
        QMessageBox warningBox(QMessageBox::Warning, "����", "��Ǹ���鲻��������Ҫ�ĵ��ʣ�");
        warningBox.setStandardButtons(QMessageBox::Rejected);
        warningBox.setButtonText(QMessageBox::Rejected, "����");
        warningBox.exec();
        ui->wordEdit->clear();
        ui->wordEdit->setFocus();
    }
    else
    {
        ReciteWindow reciteWindow(ReciteWindow::LookUpMode, controller, this);
        this->hide();
        reciteWindow.show();
    }
}
