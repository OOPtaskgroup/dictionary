#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "controller.h"

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    explicit LoginDlg(Controller *controller, QWidget *parent = 0);
    ~LoginDlg();

private slots:

    void on_loginBtn_clicked();

    void on_regBtn_clicked();

    void on_usrEdit_textChanged(const QString &);

private:
    Ui::LoginDlg *ui;
    Controller *controller;
};

#endif // LOGINDLG_H
