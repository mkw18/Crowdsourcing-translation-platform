#ifndef ENDRECUITDLG_H
#define ENDRECUITDLG_H

#include <QDialog>

namespace Ui {
class endRecuitDlg;
}

class endRecuitDlg : public QDialog
{
    Q_OBJECT

public:
    explicit endRecuitDlg(QWidget *parent = nullptr);
    ~endRecuitDlg();

private:
    Ui::endRecuitDlg *ui;
};

#endif // ENDRECUITDLG_H
