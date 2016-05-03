#ifndef WORDNUMDLG_H
#define WORDNUMDLG_H

#include <QDialog>

namespace Ui {
class WordNumDlg;
}

class WordNumDlg : public QDialog
{
    Q_OBJECT

public:
    explicit WordNumDlg(QWidget *parent = 0);
    ~WordNumDlg();

private:
    Ui::WordNumDlg *ui;
};

#endif // WORDNUMDLG_H
