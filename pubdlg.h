/************************************************************************************************************************
【文件名】                                  pubdlg.h
【模块功能和目的】                           PubDlg类声明，对应发布者的操作界面
【开发者及日期】                             门恺文 2019.7.26
【更改记录】
************************************************************************************************************************/

#ifndef PUBDLG_H
#define PUBDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class PubDlg;
}

/************************************************************************************************************************
【类名】                                   PubDlg
【功能】                                   封装发布者任务界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
                                          三个私有槽函数
                                          一个封装重复操作的函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
************************************************************************************************************************/

class PubDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit PubDlg(QWidget *parent = nullptr);
    ~PubDlg();

    //发布者用户编号设置函数
    void setPubCode(int value);

    //任务编号设置函数
    void setAssignId(int value);

private slots:
    //确认任务完成槽函数
    void on_confirmBtn_clicked();

    //支付酬金槽函数
    void on_payBtn_clicked();

    //进入审核负责人槽函数
    void enterPncp(const QModelIndex& index);

    void on_depositBtn_clicked();

private:
    Ui::PubDlg *ui;

    void init();
    int pubCode;
    int assignId;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // PUBDLG_H
