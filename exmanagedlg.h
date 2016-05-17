#ifndef EXMANAGEDLG_H
#define EXMANAGEDLG_H

#include <QDialog>
#include "controller.h"
#include "addexdlg.h"

namespace Ui {
class ExManageDlg;
}

class ExManageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ExManageDlg(Controller* controller, WordData *word, QWidget *parent = 0);
    ~ExManageDlg();

private slots:
    void on_exList_clicked(const QModelIndex &index);

    void on_delBtn_clicked();

    void on_addBtn_clicked();

private:
    Ui::ExManageDlg *ui;
    Controller *controller;
    WordData *srcWord;
    void setItem();
};

#endif // EXMANAGEDLG_H
