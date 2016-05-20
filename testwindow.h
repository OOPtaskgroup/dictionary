#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "controller.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT
    typedef int TestStatus;
    static const TestStatus Testing = 1;
    static const TestStatus Known = 2;
    static const TestStatus Unknown = 3;

public:
    explicit TestWindow(Controller *controller, QWidget *parent = 0);
    ~TestWindow();

private slots:
    void on_cantRecBtn_clicked();

    void on_knownBtn_clicked();

private:
    Ui::TestWindow *ui;
    Controller *controller;
    std::vector< WordData* > testWords;
    bool showWord(WordData *word);
    void doTest();
    bool testOver();
    WordData* findNextWord();
    TestStatus status;
};

#endif // TESTWINDOW_H
