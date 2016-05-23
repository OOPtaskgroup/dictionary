#include "textwindow.h"
#include "ui_textwindow.h"
#include <QMessageBox>

TextWindow::TextWindow(Controller* controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextWindow)
{
    ui->setupUi(this);
    this->controller = controller;
    this->move(this->parentWidget()->pos());
    this->setStyleSheet(controller->setTheme("text"));
}

TextWindow::~TextWindow()
{
    delete ui;
}

void TextWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("警告"), tr("无法读取文件 %1").arg(fileName));
        return;
    }
    ui->articleEdit->setText(QLatin1String(file.readAll()));
}

void TextWindow::closeEvent(QCloseEvent *event)
{
    this->parentWidget()->move(this->pos());
    this->parentWidget()->show();
    event->accept();
}

void TextWindow::on_importBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
    {
        loadFile(fileName);
    }
}

void TextWindow::on_analyseBtn_clicked()
{
    ui->wordList->clear();
    auto word = controller->getTextNewWords(ui->articleEdit->toPlainText().toStdString());
    for (auto i = word.begin(); i != word.end(); ++i)
    {
        ui->wordList->addItem(QString::fromStdString((*i)->Name()));
    }
}

void TextWindow::on_wordList_clicked(const QModelIndex &index)
{
    auto wordDetail = controller->getDetail(controller->findWord(ui->wordList->currentItem()->text().toStdString()));
    ui->transBrowser->setText(QString::fromStdString(*(wordDetail.begin() + wordDetail.size() - 1)));
    ui->articleEdit->find(ui->wordList->currentItem()->text(), QTextDocument::FindWholeWords);
}

void TextWindow::on_detailBtn_clicked()
{
    if (ui->wordList->currentRow() == -1)
    {
        return;
    }
    LookUpWindow *lookUpWindow = new LookUpWindow(controller, ui->wordList->currentItem()->text(), this);
    lookUpWindow->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    lookUpWindow->show();
}

void TextWindow::on_wordList_doubleClicked(const QModelIndex &index)
{
    ui->detailBtn->click();
}
