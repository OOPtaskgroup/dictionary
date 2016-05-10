#ifndef PWDCHANGEDLG_H
#define PWDCHANGEDLG_H

#include <QDialog>
#include "controller.h"

namespace Ui {
class PwdChangeDlg;
}

class PwdChangeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PwdChangeDlg(Controller *controller, QWidget *parent = 0);
    ~PwdChangeDlg();

private slots:
    void on_confirmBtn_clicked();

    void on_oldPwdEdit_textChanged(const QString &arg1);

    void on_newPwdEdit_textChanged(const QString &arg1);

    void on_confirmNewPwdEdit_textChanged(const QString &arg1);

private:
    Ui::PwdChangeDlg *ui;
    Controller *controller;
    bool checkInput();
    void setBtnStat();
};

#endif // PWDCHANGEDLG_H
