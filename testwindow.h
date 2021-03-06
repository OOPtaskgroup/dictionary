#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "controller.h"
#include <QCloseEvent>
#include <QKeyEvent>

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
    std::vector<std::pair<WordData*, bool>> result;

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // TESTWINDOW_H
