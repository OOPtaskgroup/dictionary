#ifndef ADDEXDLG_H
#define ADDEXDLG_H

#include <QDialog>
#include "controller.h"

namespace Ui {
class AddExDlg;
}

class AddExDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AddExDlg(Controller *controller, WordData *word, QWidget *parent = 0);
    ~AddExDlg();

private slots:
    void on_confirmBtn_clicked();

private:
    Ui::AddExDlg *ui;
    Controller *controller;
    WordData *srcWord;
};

#endif // ADDEXDLG_H
