#include "textwindow.h"
#include "ui_textwindow.h"

TextWindow::TextWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TextWindow)
{
    ui->setupUi(this);
}

TextWindow::~TextWindow()
{
    delete ui;
}

void TextWindow::on_pushButton_3_clicked()
{

}
