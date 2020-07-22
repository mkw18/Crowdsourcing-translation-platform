/************************************************************************************************************************
【文件名】                                  enrolldlg.h
【模块功能和目的】                           EnrollDlg类声明，对应负责人和译者的报名界面，不同的角色对应界面的初始化不同
【开发者及日期】                             门恺文 2019.7.25
【更改记录】
************************************************************************************************************************/

#ifndef ENROLLDLG_H
#define ENROLLDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class EnrollDlg;
}

/************************************************************************************************************************
【类名】                                   EnrollDlg
【功能】                                   封装报名负责人或译者界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          两个私有槽函数
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.25
【更改记录】
************************************************************************************************************************/

class EnrollDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit EnrollDlg(QWidget *parent = nullptr);
    ~EnrollDlg();

    //根据报名者角色不同设置标题
    void setFront(const QString &value);

    //用户名设置函数
    void setUserName(const QString &value);

    //报名者类型设置函数
    void setType(int value);

    //任务编号设置函数
    void setAssignId(int value);

    //发布者（接受信息者）编号获取和设置函数
    void setPublisherCode(int value);

    //发送信息者（报名者）编号获取和设置函数
    void setSenderCode(int value);

private slots:
    //确认提交前必须同意的译者协议槽函数
    void on_checkBox_clicked();

    //提交按钮槽函数
    void on_admitBtn_clicked();

private:
    Ui::EnrollDlg *ui;
    QString front;
    QString userName;
    int publisherCode;
    int senderCode;
    int assignId;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
    int type;
};

#endif // ENROLLDLG_H
