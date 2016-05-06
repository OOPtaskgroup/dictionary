#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller *controller;
    MainWindow w(controller);
    LoginDlg loginDlg(controller);
    if (loginDlg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
        return 0;
    return a.exec();
}
