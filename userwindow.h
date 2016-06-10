#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "controller.h"
#include "lookupwindow.h"
#include <QCloseEvent>

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(Controller *controller, QWidget *parent = 0);
    ~UserWindow();

private slots:
    void on_detailBtn_clicked();

    void on_masteredList_doubleClicked(const QModelIndex &index);

    void on_learningList_doubleClicked(const QModelIndex &index);

    void on_masteredList_clicked(const QModelIndex &index);

    void on_learningList_clicked(const QModelIndex &index);

    void on_relearnBtn_clicked();

private:
    Ui::UserWindow *ui;
    Controller *controller;
    QListWidget *activeList;
    void loadData();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // USERWINDOW_H
