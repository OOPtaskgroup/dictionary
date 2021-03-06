#ifndef TEXTWINDOW_H
#define TEXTWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "controller.h"
#include <QCloseEvent>
#include "lookupwindow.h"
#include <QKeyEvent>

namespace Ui {
class TextWindow;
}

class TextWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TextWindow(Controller* controller, QWidget *parent = 0);
    ~TextWindow();

private slots:
    void on_importBtn_clicked();

    void on_analyseBtn_clicked();

    void on_wordList_clicked(const QModelIndex &);

    void on_detailBtn_clicked();

    void on_wordList_doubleClicked(const QModelIndex &);

private:
    Ui::TextWindow *ui;
    void loadFile(const QString &fileName);
    Controller *controller;

protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // TEXTWINDOW_H
