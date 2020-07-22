#include "endrecuitdlg.h"
#include "ui_endrecuitdlg.h"

endRecuitDlg::endRecuitDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endRecuitDlg)
{
    ui->setupUi(this);
}

endRecuitDlg::~endRecuitDlg()
{
    delete ui;
}
