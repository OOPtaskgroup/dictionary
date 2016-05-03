#ifndef CONFIGDLG_H
#define CONFIGDLG_H

#include <QDialog>
#include "controller.h"
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
    void on_pushButton_clicked();

private:
    Ui::ConfigDlg *ui;
    Controller *controller;
};

#endif // CONFIGDLG_H
