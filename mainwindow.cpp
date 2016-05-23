#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wordEdit->installEventFilter(this);
    ui->bgImg->installEventFilter(this);
}

MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    MainWindow(parent)
{
    this->controller = controller;
    ui->historyList->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        if (watched == ui->wordEdit && ui->wordEdit->text() == "")
        {
            ui->historyList->show();
        }
        if (watched == ui->bgImg)
        {
            ui->historyList->hide();
        }
    }
    if (event->type() == QEvent::FocusOut)
    {
        if (watched == ui->wordEdit)
        {
            ui->historyList->hide();
        }
    }
    return QMainWindow::eventFilter(watched, event);
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
    if (controller->findWord(ui->wordEdit->text().toStdString(), true) == nullptr)
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

void MainWindow::setHistoryList()
{
    ui->historyList->clear();
    auto historyWords = controller->getSearchHistory(controller->getActiveUser());
    if (historyWords.size() <= 4)
    {
        ui->historyList->setGeometry(20, 380, 171, historyWords.size() * 24);
        for (auto i = 1; i <= historyWords.size(); ++i)
        {
            ui->historyList->addItem(QString::fromStdString(*(historyWords.end() - i)));
        }
    }
    else if (historyWords.size() >= 5)
    {
        ui->historyList->setGeometry(20, 380, 171, 120);
        for (auto i = 1; i <= 5; ++i)
        {
            ui->historyList->addItem(QString::fromStdString(*(historyWords.end() - i)));
        }
    }
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
    setHistoryList();
    this->setStyleSheet(this->controller->setTheme("main"));
}

void MainWindow::on_testBtn_clicked()
{
    TestWindow *testWindow = new TestWindow(controller, this);
    testWindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    testWindow->show();
}

void MainWindow::on_historyList_clicked(const QModelIndex &index)
{
    ui->wordEdit->setText(ui->historyList->currentItem()->text());
    ui->wordEdit->setFocus();
}

void MainWindow::on_wordEdit_textChanged(const QString &arg1)
{
    if (ui->wordEdit->text() == "")
    {
        ui->historyList->show();
    }
    else
    {
        ui->historyList->hide();
    }
}

void MainWindow::on_textBtn_clicked()
{
    TextWindow *textWindow = new TextWindow(controller, this);
    textWindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    textWindow->show();
}
