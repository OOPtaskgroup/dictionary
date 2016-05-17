#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include "controller.h"
#include "configdlg.h"
#include "recitewindow.h"
#include "lookupwindow.h"
#include <qmessagebox.h>
#include "logindlg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(Controller* controller, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_configBtn_clicked();

    void on_reciteBtn_clicked();

    void on_lookUpBtn_clicked();

    void on_logoutBtn_clicked();

    void on_wordEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    Controller* controller;

protected:
    void showEvent(QShowEvent *);
};

#endif // MAINWINDOW_H
