#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::MainWindow(Controller *controller, QWidget *parent) :
    MainWindow(parent),
    controller(controller)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
