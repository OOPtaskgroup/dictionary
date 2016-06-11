#include "lookupwindow.h"
#include "ui_lookupwindow.h"
#include "exmanagedlg.h"

bool LookUpWindow::showWord(WordData* word)
{
    auto wordDetail = controller->getDetail(word);
    ui->wordLabel->setText(QString::fromStdString(word->Name()));
    ui->exampleBrowser->setVisible(true);
    auto example = controller->getExample(lookUpData);
    QString exampleText("");
    for (auto i : example)
    {
        exampleText += QString::fromStdString(i) + "\n";
    }
    ui->exampleBrowser->setText(exampleText);
    ui->exampleLabel->setVisible(true);
    ui->engBrowser->setVisible(true);
    ui->engBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 2)));
    ui->engLabel->setVisible(true);
    ui->chnBrowser->setVisible(true);
    ui->chnBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 1)));
    ui->chnLabel->setVisible(true);
    return true;
}

void LookUpWindow::setBtn()
{
    if (controller->isMastered(lookUpData))
    {
        ui->addBtn->setText("重 新 学 习");
        ui->addBtn->setEnabled(true);
    }
    else if (controller->isLearning(lookUpData))
    {
        ui->addBtn->setText("学 习 中");
        ui->addBtn->setEnabled(false);
    }
    else
    {
        ui->addBtn->setText("加 入 学 习");
        ui->addBtn->setEnabled(true);
    }
}

void LookUpWindow::refresh()
{
    showWord(lookUpData);
}

void LookUpWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->move(this->pos());
    this->parentWidget()->show();
    event->accept();
}

void LookUpWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
        ui->returnBtn->click();
}

LookUpWindow::LookUpWindow(Controller *controller, QString word, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LookUpWindow),
    controller(controller)
{
    ui->setupUi(this);
    this->move(this->parentWidget()->pos());
    this->setStyleSheet(controller->setTheme("lookup"));
    lookUpWord = word;
    lookUpData = this->controller->findWord(word.toStdString());
    setWindowTitle(tr("查单词:%1").arg(lookUpWord));
    ui->returnBtn->setDefault(true);
    showWord(lookUpData);
    setBtn();
}

LookUpWindow::~LookUpWindow()
{
    delete ui;
}

void LookUpWindow::on_returnBtn_clicked()
{
    this->close();
}

void LookUpWindow::on_addBtn_clicked()
{
    controller->setLearn(lookUpData);
    setBtn();
}

void LookUpWindow::on_manageBtn_clicked()
{
    ExManageDlg* exManageDlg = new ExManageDlg(controller, lookUpData, this);
    if (exManageDlg->exec() == QDialog::Accepted)
    {
        refresh();
    }
}
