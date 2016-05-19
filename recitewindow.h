#ifndef RECITEWINDOW_H
#define RECITEWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QCloseEvent>
#include <QShowEvent>

namespace Ui {
class ReciteWindow;
}

class ReciteWindow : public QMainWindow
{
    Q_OBJECT
    typedef int ReciteStatus;
    static const ReciteStatus Vocabulary = 1;
    static const ReciteStatus Example = 2;
    static const ReciteStatus English = 3;
    static const ReciteStatus ChineseAcc = 4;
    static const ReciteStatus ChineseRej = 5;

public:
    explicit ReciteWindow(Controller *controller, QWidget *parent = 0);
    ~ReciteWindow();

private slots:
    void on_cantRecBtn_clicked();

    void on_knownBtn_clicked();

    void on_returnBtn_clicked();

private:
    bool doRecite();
    std::vector<std::pair<WordData *, int> >& recitingWords;
    std::pair<WordData*, int>& findNextWord();
    bool showWord(std::pair<WordData*, int>& word);
    Ui::ReciteWindow *ui;
    Controller *controller;
    ReciteStatus status;

protected:
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // RECITEWINDOW_H
