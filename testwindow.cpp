#include "testwindow.h"
#include "ui_testwindow.h"

bool TestWindow::showWord(WordData* word)
{
    auto wordDetail = controller->getDetail(word);
    ui->wordLabel->setText(QString::fromStdString(word->Name()));
    ui->exampleBrowser->setVisible(false);
    auto example = controller->getExample(word);
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
    return true;
}

TestWindow::TestWindow(Controller *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    this->controller = controller;
    this->move(this->parentWidget()->pos());
    this->setStyleSheet(controller->setTheme("test"));
    testWords = controller->getTestWords();
    result.clear();
    doTest();
}

bool TestWindow::testOver()
{
    return (testWords.empty());
}

WordData *TestWindow::findNextWord()
{
    return *testWords.begin();
}

void TestWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->move(this->pos());
    if (testOver())
    {
        this->parentWidget()->show();
        event->accept();
    }
    else
    {
        QMessageBox infoBox(QMessageBox::Warning, "提示", tr("您还未完成测试，确认要退出吗？"),
                            QMessageBox::NoButton, this);
        QPushButton *yesBtn = infoBox.addButton("是 的", QMessageBox::YesRole);
        infoBox.addButton("取 消", QMessageBox::RejectRole);
        infoBox.exec();
        if (infoBox.clickedButton() == yesBtn)
        {
            this->parentWidget()->show();
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::doTest()
{
    if (testOver())
    {
        QMessageBox infoBox(QMessageBox::Information, "提示", tr("你已经完成了测试！\n你的单词量为：%1").arg(controller->getVocabulary(result)));
        infoBox.setStandardButtons(QMessageBox::Ok);
        infoBox.setButtonText(QMessageBox::Ok, "我知道了");
        infoBox.exec();
        this->close();
    }
    else
    {
        showWord(findNextWord());
        ui->cantRecBtn->setText("不 认 识");
        ui->cantRecBtn->setEnabled(true);
        ui->cantRecBtn->setVisible(true);
        ui->knownBtn->setText("认  识");
        status = Testing;
    }
}

void TestWindow::on_cantRecBtn_clicked()
{
    if (status == Testing)
    {
        ui->exampleBrowser->setVisible(true);
        ui->exampleLabel->setVisible(true);
        ui->engBrowser->setVisible(true);
        ui->engLabel->setVisible(true);
        ui->chnBrowser->setVisible(true);
        ui->chnLabel->setVisible(true);
        ui->cantRecBtn->setEnabled(false);
        ui->cantRecBtn->setVisible(false);
        ui->knownBtn->setText("下 一 个");
        status = Unknown;
    }
    else if (status == Known)
    {
        result.push_back(std::make_pair(findNextWord(), false));
        testWords.erase(testWords.begin());
        doTest();
    }
}

void TestWindow::on_knownBtn_clicked()
{
    if (status == Testing)
    {
        ui->exampleBrowser->setVisible(true);
        ui->exampleLabel->setVisible(true);
        ui->engBrowser->setVisible(true);
        ui->engLabel->setVisible(true);
        ui->chnBrowser->setVisible(true);
        ui->chnLabel->setVisible(true);
        ui->cantRecBtn->setText("记 错 了");
        ui->knownBtn->setText("对 了");
        status = Known;
    }
    else if (status == Known)
    {
        result.push_back(std::make_pair(findNextWord(), true));
        testWords.erase(testWords.begin());
        doTest();
    }
    else if (status == Unknown)
    {
        result.push_back(std::make_pair(findNextWord(), false));
        testWords.erase(testWords.begin());
        doTest();
    }
}
