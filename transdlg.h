/************************************************************************************************************************
【文件名】                                  transdlg.h
【模块功能和目的】                           TransDlg类声明，对应译者任务界面
【开发者及日期】                             门恺文 2019.7.28
【更改记录】
************************************************************************************************************************/

#ifndef TRANSDLG_H
#define TRANSDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class TransDlg;
}

/************************************************************************************************************************
【类名】                                   TransDlg
【功能】                                   封装译者任务界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          三个私有槽函数
                                          数据成员的获取和设置函数
【开发者及日期】                             门恺文2019.7.28
【更改记录】
************************************************************************************************************************/

class TransDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit TransDlg(QWidget *parent = nullptr);
    ~TransDlg();

    //译者用户编号设置函数
    void setTransCode(int value);

    //译者任务编号设置函数
    void setTransId(int value);

    //任务编号设置函数
    void setAssignId(int value);

private slots:
    //暂存槽函数
    void on_saveBtn_clicked();

    //提交槽函数
    void on_submitBtn_clicked();

    //领取酬金槽函数
    void on_getBtn_clicked();

private:
    Ui::TransDlg *ui;

    int transCode;
    int transId;
    int assignId;

    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // TRANSDLG_H
