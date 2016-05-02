#include "mainwindow.h"
#include "logindlg.h"
#include <QApplication>
#include <bits/stdc++.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(controller);
    LoginDlg loginDlg;
    if (loginDlg.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
        return 0;
    return a.exec();
}
