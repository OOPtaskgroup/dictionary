#ifndef LOOKUPWINDOW_H
#define LOOKUPWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QCloseEvent>

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

private:
    explicit LookUpWindow(QWidget *parent = 0);
    QString lookUpWord;
    std::pair<WordData*, int> lookUpData;
    bool showWord(std::pair<WordData*, int>& word);
    Ui::LookUpWindow *ui;
    Controller *controller;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LOOKUPWINDOW_H
