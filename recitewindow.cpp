#include "recitewindow.h"
#include "ui_recitewindow.h"
#include <QMessageBox>


std::pair<WordData*, int>& ReciteWindow::findNextWord()
{
    for (auto& i : recitingWords)
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
    auto wordDetail = controller->getDetail(word.first);
    ui->cantRecBtn->setText("没  印  象");
    ui->cantRecBtn->setEnabled(true);
    ui->cantRecBtn->setVisible(true);
    ui->wordLabel->setText(QString::fromStdString(word.first->Name()));
    ui->exampleBrowser->setVisible(false);
    auto example = controller->getExample(word.first);
    QString exampleText("");
    for (auto i : example)
    {
        exampleText += QString::fromStdString(i) + "\n";
    }
    ui->exampleBrowser->setText(exampleText);
    ui->exampleLabel->setVisible(false);
    ui->engBrowser->setVisible(false);
    ui->engBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 2)));
    ui->engLabel->setVisible(false);
    ui->chnBrowser->setVisible(false);
    ui->chnBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 1)));
    ui->chnLabel->setVisible(false);
    status = Vocabulary;
    return true;
}

bool ReciteWindow::doRecite()
{
    std::random_shuffle(recitingWords.begin(), recitingWords.end());
    if (!showWord(findNextWord()))
    {
        QMessageBox infoBox(QMessageBox::Information, "提示", "您已背完了今天要背的所有单词！");
        infoBox.setStandardButtons(QMessageBox::Ok);
        infoBox.setButtonText(QMessageBox::Ok, "好的");
        infoBox.exec();
        this->parentWidget()->show();
        return false;
    }
    return true;
}

void ReciteWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->show();
    event->accept();
}

void ReciteWindow::showEvent(QShowEvent *event)
{
    if (!doRecite())
    {
        throw WordsHaveBeenRecitedException("you have recited all the words");
    }
}

ReciteWindow::ReciteWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReciteWindow),
    controller(controller),
    recitingWords(controller->getRecitingWords())
{
    ui->setupUi(this);
    setWindowTitle("背单词");
    this->setStyleSheet(controller->setTheme("recite"));
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
        if (!doRecite())
        {
            this->close();
        };
    }
    else if (status == English)
    {
        ui->chnBrowser->setVisible(true);
        ui->chnLabel->setVisible(true);
        ui->cantRecBtn->setEnabled(false);
        ui->cantRecBtn->setVisible(false);
        status = ChineseRej;
    }
    else if (status == Example)
    {
        ui->engBrowser->setVisible(true);
        ui->engLabel->setVisible(true);
        status = English;
    }
    else if (status == Vocabulary)
    {
        ui->exampleBrowser->setVisible(true);
        ui->exampleLabel->setVisible(true);
        status = Example;
    }
}

void ReciteWindow::on_knownBtn_clicked()
{
    if (status == Vocabulary)
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
    else if (status == English || status == Example)
    {
        ui->exampleBrowser->setVisible(true);
        ui->exampleLabel->setVisible(true);
        ui->engBrowser->setVisible(true);
        ui->engLabel->setVisible(true);
        ui->chnBrowser->setVisible(true);
        ui->chnLabel->setVisible(true);
        ui->cantRecBtn->setEnabled(false);
        ui->cantRecBtn->setVisible(false);
        status = ChineseRej;
    }
    else if (status == ChineseAcc)
    {
        controller->answerAccepted(findNextWord());
        if (!doRecite())
        {
            this->close();
        }

    }
    else if (status == ChineseRej)
    {
        controller->answerWrong(findNextWord());
        if (!doRecite())
        {
            this->close();
        }
    }
}

void ReciteWindow::on_returnBtn_clicked()
{
    this->close();
}
