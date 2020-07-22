/************************************************************************************************************************
【文件名】                                  deposit.h
【模块功能和目的】                           Deposit类声明，封装充值的操作
【开发者及日期】                             门恺文 2019.7.24
【更改记录】
************************************************************************************************************************/

#ifndef DEPOSITDLG_H
#define DEPOSITDLG_H

#include <QDialog>
#include "database.h"
#include <QList>

namespace Ui {
class Depositdlg;
}

/************************************************************************************************************************
【类名】                                   Depositdlg
【功能】                                   封装充值操作所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
                                          一个私有槽函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
************************************************************************************************************************/

class Depositdlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit Depositdlg(QWidget *parent = nullptr);
    ~Depositdlg();

    //用户编号设置函数
    void setUserCode(int value);

private slots:
    //充值确认按钮槽函数
    void on_confirmBtn_clicked();

private:
    Ui::Depositdlg *ui;

    int userCode;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // DEPOSITDLG_H
