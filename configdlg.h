#ifndef CONFIGDLG_H
#define CONFIGDLG_H

#include <QDialog>
#include "controller.h"
#include "pwdchangedlg.h"

namespace Ui {
class ConfigDlg;
}

class ConfigDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDlg(QWidget *parent = 0);
    explicit ConfigDlg(Controller *controller, QWidget *parent = 0);
    ~ConfigDlg();

private slots:
    void on_pwdChangeBtn_clicked();

    void on_confirmBtn_clicked();

private:
    Ui::ConfigDlg *ui;
    Controller *controller;
};

#endif // CONFIGDLG_H
