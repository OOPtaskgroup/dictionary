#ifndef RECITEWINDOW_H
#define RECITEWINDOW_H

#include <QMainWindow>
#include "controller.h"
#include <QCloseEvent>

namespace Ui {
class ReciteWindow;
}

class ReciteWindow : public QMainWindow
{
    Q_OBJECT
    typedef int WindowMode;
    typedef int ReciteStatus;
    static const ReciteStatus Vocabulary = 1;
    static const ReciteStatus Example = 2;
    static const ReciteStatus English = 3;
    static const ReciteStatus ChineseAcc = 4;
    static const ReciteStatus ChineseRej = 5;

public:
    static const WindowMode ReciteMode = 1;
    static const WindowMode LookUpMode = 2;
    explicit ReciteWindow(WindowMode windowMode, Controller *controller, QWidget *parent = 0);
    explicit ReciteWindow(WindowMode windowMode, Controller *controller, QString word, QWidget *parent = 0);
    ~ReciteWindow();

private slots:
    void on_cantRecBtn_clicked();

    void on_knownBtn_clicked();

    void on_returnBtn_clicked();

private:
    explicit ReciteWindow(QWidget *parent = 0);
    explicit ReciteWindow(Controller *controller, QWidget *parent = 0);
    QString lookUpWord;
    WordData* lookUpData;
    std::pair<WordData*, int>& findNextWord();
    bool showWord(std::pair<WordData*, int>& word);
    void doRecite();
    Ui::ReciteWindow *ui;
    Controller *controller;
    std::vector< std::pair<WordData*,int> >& recitingWords;
    WindowMode windowMode;
    ReciteStatus status;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // RECITEWINDOW_H
