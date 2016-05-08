#include "lookupwindow.h"
#include "ui_lookupwindow.h"
#include <QMessageBox>

bool LookUpWindow::showWord(std::pair<WordData *, int> &word)
{
    auto wordDetail = word.first->getDetail();
    ui->cantRecBtn->setEnabled(false);
    ui->cantRecBtn->setVisible(false);
    ui->knownBtn->setEnabled(false);
    ui->knownBtn->setVisible(false);
    ui->wordLabel->setText(QString::fromStdString(word.first->Name()));
    ui->exampleBrowser->setVisible(true);
    ui->exampleBrowser->setText(QString::fromStdString(*wordDetail.begin()) + "\n" + QString::fromStdString(*(wordDetail.begin() + 1)));
    ui->exampleLabel->setVisible(true);
    ui->engBrowser->setVisible(true);
    ui->engBrowser->setText(QString::fromStdString(*(wordDetail.begin() + 2)));
    ui->engLabel->setVisible(true);
    ui->chnBrowser->setVisible(true);
    ui->chnBrowser->setText(QString::fromStdString(*(wordDetail.begin() + 3)));
    ui->chnLabel->setVisible(true);
    return true;
}

void LookUpWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
    event->accept();
}

LookUpWindow::LookUpWindow(Controller *controller, QString word, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LookUpWindow),
    controller(controller)
{
    ui->setupUi(this);
    lookUpWord = word;
    lookUpData = std::make_pair(this->controller->findWord(word.toStdString()), -1);
    setWindowTitle(tr("%1").arg(lookUpWord));
    showWord(lookUpData);
}

LookUpWindow::~LookUpWindow()
{
    delete ui;
}

void LookUpWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}
