#ifndef REGDLG_H
#define REGDLG_H

#include <QDialog>
#include "controller.h"
#include <QMessageBox>
#include "exceptions.h"

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
    void setBtnStat();

private slots:
    void on_regBtn_clicked();
    void on_pwdConfirmEdit_textChanged(const QString &);
    void on_pwdEdit_textChanged(const QString &);
    void on_usrEdit_textChanged(const QString &);
};

#endif // REGDLG_H
