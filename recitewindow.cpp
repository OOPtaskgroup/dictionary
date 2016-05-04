#include "recitewindow.h"
#include "ui_recitewindow.h"
#include <QMessageBox>

ReciteWindow::ReciteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReciteWindow)
{
    ui->setupUi(this);
}

ReciteWindow::ReciteWindow(Controller *controller, QWidget *parent) :
    ReciteWindow(parent),
    controller(controller)
{

}

std::pair<WordData*, int>& ReciteWindow::findNextWord()
{
    for (auto i : recitingWords)
    {
        if ((*i).second != 1)
        {
            return (*i);
        }
    }
    return (*recitingWords.begin());
}

bool ReciteWindow::showWord(std::pair<WordData *, int> &word)
{
    if (windowMode == ReciteMode)
    {
        if (word.second == 1)
            return false;
        auto wordDetail = word.first->getDetail();
        ui->cantRecBtn->setText("û  ӡ  ��");
        ui->cantRecBtn->setEnabled(true);
        ui->cantRecBtn->setVisible(true);
        ui->wordLabel->setText(word.first->Name());
        ui->exampleBrowser->setVisible(false);
        ui->exampleBrowser->setText(*wordDetail.begin() + "\n" + *(wordDetail.begin() + 1));
        ui->exampleLabel->setVisible(false);
        ui->engBrowser->setVisible(false);
        ui->engBrowser->setText(*(wordDetail.begin() + 2));
        ui->engLabel->setVisible(false);
        ui->chnBrowser->setVisible(false);
        ui->chnBrowser->setText(*(wordDetail.begin() + 3));
        ui->chnLabel->setVisible(false);
        status = Vocabulary;
        return true;
    }
    if (windowMode == LookUpMode)
    {
        auto wordDetail = word.first->getDetail();
        ui->cantRecBtn->setEnabled(false);
        ui->cantRecBtn->setVisible(false);
        ui->knownBtn->setEnabled(false);
        ui->knownBtn->setVisible(false);
        ui->wordLabel->setText(word.first->Name());
        ui->exampleBrowser->setVisible(true);
        ui->exampleBrowser->setText(*wordDetail.begin() + "\n" + *(wordDetail.begin() + 1));
        ui->exampleLabel->setVisible(true);
        ui->engBrowser->setVisible(true);
        ui->engBrowser->setText(*(wordDetail.begin() + 2));
        ui->engLabel->setVisible(true);
        ui->chnBrowser->setVisible(true);
        ui->chnBrowser->setText(*(wordDetail.begin() + 3));
        ui->chnLabel->setVisible(true);
        return true;
    }
}

void ReciteWindow::doRecite()
{
    if (!showWord(findNextWord()))
    {
        QMessageBox infoBox(QMessageBox::Information, "��ʾ", "���ѱ����˽���Ҫ�������е��ʣ�");
        infoBox.setStandardButtons(QMessageBox::Ok);
        infoBox.setButtonText(QMessageBox::Ok, "�õ�");
        infoBox.exec();
        this->close();
    }
}

void ReciteWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
    event->accept();
}

ReciteWindow::ReciteWindow(ReciteWindow::WindowMode windowMode, Controller *controller, QWidget *parent) :
    ReciteWindow(controller, parent),
    windowMode(windowMode),
    recitingWords(controller->getRecitingWords())
{
    if (windowMode = ReciteMode)
    {
        doRecite();
    }
}

ReciteWindow::ReciteWindow(ReciteWindow::WindowMode windowMode, Controller *controller, QString word, QWidget *parent) :
    ReciteWindow(controller, parent),
    windowMode(windowMode),
    lookUpWord(word),
    lookUpData(controller->findWord(word.toStdString()))
{
    if (windowMode = LookUpMode)
    {
        ui->cantRecBtn->setVisible(false);
        ui->cantRecBtn->setEnabled(false);
        ui->knownBtn->setVisible(false);
        ui->knownBtn->setEnabled(false);
        showWord(std::make_pair(lookUpData, -1));
    }
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
        ui->cantRecBtn->setText("��  ��  ��");
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
