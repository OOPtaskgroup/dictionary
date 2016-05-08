#ifndef PWDCHANGEDLG_H
#define PWDCHANGEDLG_H

#include <QDialog>

namespace Ui {
class PwdChangeDlg;
}

class PwdChangeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PwdChangeDlg(QWidget *parent = 0);
    ~PwdChangeDlg();

private:
    Ui::PwdChangeDlg *ui;
};

#endif // PWDCHANGEDLG_H
