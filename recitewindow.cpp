#include "recitewindow.h"
#include "ui_recitewindow.h"
#include <QMessageBox>


std::pair<WordData*, int>& ReciteWindow::findNextWord()
{
    for (auto i : recitingWords)
    {
        if (i.second != 1)
        {
            return i;
        }
    }
    return (*recitingWords.begin());
}

bool ReciteWindow::showWord(std::pair<WordData *, int> &word)
{
    if (word.second == 1)
        return false;
    auto wordDetail = word.first->getDetail();
    ui->cantRecBtn->setText("没  印  象");
    ui->cantRecBtn->setEnabled(true);
    ui->cantRecBtn->setVisible(true);
    ui->wordLabel->setText(QString::fromStdString(word.first->Name()));
    ui->exampleBrowser->setVisible(false);
    ui->exampleBrowser->setText(QString::fromStdString(*wordDetail.begin()) + "\n" + QString::fromStdString(*(wordDetail.begin() + 1)));
    ui->exampleLabel->setVisible(false);
    ui->engBrowser->setVisible(false);
    ui->engBrowser->setText(QString::fromStdString(*(wordDetail.begin() + 2)));
    ui->engLabel->setVisible(false);
    ui->chnBrowser->setVisible(false);
    ui->chnBrowser->setText(QString::fromStdString(*(wordDetail.begin() + 3)));
    ui->chnLabel->setVisible(false);
    status = Vocabulary;
    return true;
}

void ReciteWindow::doRecite()
{
    if (!showWord(findNextWord()))
    {
        QMessageBox infoBox(QMessageBox::Information, "提示", "您已背完了今天要背的所有单词！");
        infoBox.setStandardButtons(QMessageBox::Ok);
        infoBox.setButtonText(QMessageBox::Ok, "好的");
        infoBox.exec();
        this->close();
    }
}

void ReciteWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
    event->accept();
}

ReciteWindow::ReciteWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReciteWindow),
    controller(controller),
    recitingWords(controller->getRecitingWords())
{
    ui->setupUi(this);
    setWindowTitle("背单词");
    doRecite();
}

ReciteWindow::~ReciteWindow()
{
    delete ui;
}

void ReciteWindow::on_cantRecBtn_clicked()
{
    if (status == ChineseAcc)
    {
        controller->answerAccepted(findNextWord());
        doRecite();
    }
    if (status == English)
    {
        ui->chnBrowser->setVisible(true);
        ui->chnLabel->setVisible(true);
        ui->cantRecBtn->setEnabled(false);
        ui->cantRecBtn->setVisible(false);
        status = ChineseRej;
    }
    if (status == Example)
    {
        ui->engBrowser->setVisible(true);
        ui->engLabel->setVisible(true);
        status = English;
    }
    if (status == Vocabulary)
    {
        ui->exampleBrowser->setVisible(true);
        ui->exampleLabel->setVisible(true);
        status = Example;
    }
}

void ReciteWindow::on_knownBtn_clicked()
{
    if (status == English || status == Example || status == Vocabulary)
    {
        ui->exampleBrowser->setVisible(true);
        ui->exampleLabel->setVisible(true);
        ui->engBrowser->setVisible(true);
        ui->engLabel->setVisible(true);
        ui->chnBrowser->setVisible(true);
        ui->chnLabel->setVisible(true);
        ui->cantRecBtn->setText("记  错  了");
        status = ChineseAcc;
    }
    if (status == ChineseAcc)
    {
        controller->answerAccepted(findNextWord());
        doRecite();
    }
    if (status == ChineseRej)
    {
        controller->answerWrong(findNextWord());
        doRecite();
    }
}

void ReciteWindow::on_returnBtn_clicked()
{
    this->parentWidget()->show();
    this->close();
}
