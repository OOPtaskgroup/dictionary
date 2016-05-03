#ifndef REGDLG_H
#define REGDLG_H

#include <QDialog>
#include <QKeyEvent>
#include "controller.h"

namespace Ui {
class RegDlg;
}

class RegDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegDlg(QWidget *parent = 0);
    explicit RegDlg(Controller* controller, QWidget *parent = 0);
    ~RegDlg();

private:
    Ui::RegDlg *ui;
    bool checkInput();
    Controller* controller;

protected:
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_regBtn_clicked();
};

#endif // REGDLG_H
