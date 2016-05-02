#ifndef REGDLG_H
#define REGDLG_H

#include <QDialog>

namespace Ui {
class RegDlg;
}

class RegDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RegDlg(QWidget *parent = 0);
    ~RegDlg();

private:
    Ui::RegDlg *ui;
};

#endif // REGDLG_H
