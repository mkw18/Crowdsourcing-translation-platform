/************************************************************************************************************************
【文件名】                                  pncpdlg.h
【模块功能和目的】                           PncpDlg类声明，对应负责人的任务界面
【开发者及日期】                             门恺文 2019.7.27
【更改记录】
************************************************************************************************************************/

#ifndef PNCPDLG_H
#define PNCPDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class PncpDlg;
}

/************************************************************************************************************************
【类名】                                   PncpDlg
【功能】                                   封装负责人任务界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
                                          六个私有槽函数
                                          三个封装重复操作的函数
【开发者及日期】                             门恺文2019.7.27
【更改记录】
************************************************************************************************************************/

class PncpDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit PncpDlg(QWidget *parent = nullptr);
    ~PncpDlg();

    //负责人任务编号设置函数
    void setPncpId(int value);

    //负责人用户编号设置函数
    void setPncpCode(int value);

    //任务编号设置函数
    void setAssignId(int value);

private slots:
    //显示译者报名详情槽函数
    void on_enrollBtn_clicked();

    //显示可分配子任务译者槽函数
    void on_assignBtn_clicked();

    //显示译文槽函数
    void on_transBtn_clicked();

    //进入设置译者报名截止日期槽函数
    void on_transDDLBtn_clicked();

    //提交任务槽函数
    void on_submitBtn_clicked();

    //领取酬金槽函数
    void on_getBtn_clicked();

    //进入译者报名详情槽函数
    void enterEnroll(const QModelIndex& index);

    //进入分配任务详情槽函数
    void enterAssign(const QModelIndex& index);

    //进入译者提交详情槽函数
    void enterTrans(const QModelIndex& index);

private:
    Ui::PncpDlg *ui;

    //封装译者报名槽函数内部较繁杂的步骤
    void inEnroll();
    //封装分配任务详情槽函数内部较繁杂的步骤
    void inAssign();
    //封装译者提交槽函数内部较繁杂的步骤
    void inTrans();

    int pncpCode;
    int pncpId;
    int assignId;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // PNCPDLG_H
