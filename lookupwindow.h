#ifndef LOOKUPWINDOW_H
#define LOOKUPWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QCloseEvent>
#include "exmanagedlg.h"

namespace Ui {
class LookUpWindow;
}

class LookUpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LookUpWindow(Controller *controller, QString word, QWidget *parent = 0);
    ~LookUpWindow();

private slots:
    void on_returnBtn_clicked();

    void on_addBtn_clicked();

    void on_manageBtn_clicked();

private:
    explicit LookUpWindow(QWidget *parent = 0);
    QString lookUpWord;
    WordData* lookUpData;
    bool showWord(WordData* word);
    Ui::LookUpWindow *ui;
    Controller *controller;
    void setBtn();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LOOKUPWINDOW_H
