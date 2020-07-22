/************************************************************************************************************************
【文件名】                                  employmentdlg.h
【模块功能和目的】                           Employmentdlg类声明，封装应聘操作
【开发者及日期】                             门恺文 2019.7.26
【更改记录】
************************************************************************************************************************/

#ifndef EMPLOYMENTDLG_H
#define EMPLOYMENTDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class Employmentdlg;
}

/************************************************************************************************************************
【类名】                                   Employmentdlg
【功能】                                   封装应聘界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          一个私有槽函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
************************************************************************************************************************/

class Employmentdlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit Employmentdlg(QWidget *parent = nullptr);
    ~Employmentdlg();

private slots:
    //确认应聘按钮
    void on_confirmBtn_clicked();

private:
    Ui::Employmentdlg *ui;
    QList<Platform>& platformList = Database::platformList;
};

#endif // EMPLOYMENTDLG_H
