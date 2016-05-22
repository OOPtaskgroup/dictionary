#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    MainWindow(parent)
{
    this->controller = controller;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_configBtn_clicked()
{
    ConfigDlg configDlg(controller, this);
    if (configDlg.exec() == QDialog::Accepted)
    {
        refresh();
    }
}

void MainWindow::on_reciteBtn_clicked()
{
    if (!checkReciteWords())
    {
        controller->setAdditionWords();
    }
    ReciteWindow *reciteWindow = new ReciteWindow(controller, this);
    reciteWindow->show();
    this->hide();
}

void MainWindow::on_lookUpBtn_clicked()
{
    if (controller->findWord(ui->wordEdit->text().toStdString()) == nullptr)
    {
        QMessageBox warningBox(QMessageBox::Warning, "警告", "抱歉，查不到您所需要的单词！");
        warningBox.setStandardButtons(QMessageBox::Ok);
        warningBox.setButtonText(QMessageBox::Ok, "返回");
        warningBox.exec();
        ui->wordEdit->clear();
        ui->wordEdit->setFocus();
    }
    else
    {
        LookUpWindow *lookUpWindow = new LookUpWindow(controller, ui->wordEdit->text(), this);
        this->hide();
        lookUpWindow->show();
        ui->wordEdit->clear();
        ui->wordEdit->setFocus();
    }
}


void MainWindow::on_logoutBtn_clicked()
{
    controller->Logout();
    this->hide();
    LoginDlg loginDlg(controller);
    if (loginDlg.exec() == QDialog::Accepted)
    {
        this->show();
    }
    else
        this->close();
}

void MainWindow::showEvent(QShowEvent *)
{
    refresh();
}

void MainWindow::on_wordEdit_returnPressed()
{
    ui->lookUpBtn->click();
}

bool MainWindow::checkReciteWords()
{
    auto recitingWords = controller->getRecitingWords();
    bool hasRecited = true;
    for (auto i : recitingWords)
    {
        if (i.second != 1)
        {
            hasRecited = false;
            break;
        }
    }
    return !hasRecited;
}

void MainWindow::refresh()
{
    ui->username->setText(tr("欢迎您！%1!").arg(QString::fromStdString(controller->getActiveUser()->Name())));
    if (checkReciteWords())
    {
        ui->reciteBtn->setText("背  单  词");
    }
    else
    {
        ui->reciteBtn->setText("再  来  一  组");
    }
    this->setStyleSheet(this->controller->setTheme("main"));
}

void MainWindow::on_testBtn_clicked()
{
    TestWindow *testWindow = new TestWindow(controller, this);
    testWindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    testWindow->show();
}
