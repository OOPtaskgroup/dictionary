#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    activeList = ui->masteredList;
    this->controller = controller;
    this->setStyleSheet(controller->setTheme("user"));
    loadData();
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_detailBtn_clicked()
{
    if (activeList->currentRow() == -1)
    {
        return;
    }
    LookUpWindow *lookUpWindow = new LookUpWindow(controller, activeList->currentItem()->text(), this);
    lookUpWindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    lookUpWindow->show();
}

void UserWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->move(this->pos());
    this->parentWidget()->show();
    event->accept();
}

void UserWindow::on_masteredList_doubleClicked(const QModelIndex &index)
{
    ui->detailBtn->click();
}

void UserWindow::on_learningList_doubleClicked(const QModelIndex &index)
{
    ui->detailBtn->click();
}

void UserWindow::on_masteredList_clicked(const QModelIndex &index)
{
    activeList = ui->masteredList;
    auto wordDetail = controller->getDetail(controller->findWord(ui->masteredList->currentItem()->text().toStdString()));
    ui->transBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 1)));
    ui->relearnBtn->setEnabled(true);
    ui->relearnBtn->show();
}

void UserWindow::on_learningList_clicked(const QModelIndex &index)
{
    activeList = ui->learningList;
    auto wordDetail = controller->getDetail(controller->findWord(ui->learningList->currentItem()->text().toStdString()));
    ui->transBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 1)));
    ui->relearnBtn->setEnabled(false);
    ui->relearnBtn->hide();
}

void UserWindow::on_relearnBtn_clicked()
{
    controller->setLearn(controller->findWord(activeList->currentItem()->text().toStdString()));
    loadData();
}

void UserWindow::loadData()
{
    auto masteredWord = controller->getMasteredWord();
    ui->masteredLabel->setText(tr("已掌握（%1词）:").arg(masteredWord.size()));
    for (auto i = masteredWord.begin(); i != masteredWord.end(); ++i)
    {
        ui->masteredList->addItem(QString::fromStdString((*i)->Name()));
    }
    auto learningWord = controller->getLearningWord();
    ui->learningLabel->setText(tr("学习中（%1词）:").arg(learningWord.size()));
    for (auto i = learningWord.begin(); i!= learningWord.end(); ++i)
    {
        ui->learningList->addItem(QString::fromStdString((*i)->Name()));
    }
    ui->relearnBtn->setEnabled(false);
    ui->relearnBtn->hide();
}
