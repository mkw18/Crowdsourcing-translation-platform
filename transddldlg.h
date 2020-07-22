/************************************************************************************************************************
【文件名】                                  transddldlg.h
【模块功能和目的】                           transDDLDlg类声明，对应负责人设定译者报名截止日期界面
【开发者及日期】                             门恺文 2019.7.27
【更改记录】
************************************************************************************************************************/

#ifndef TRANSDDLDLG_H
#define TRANSDDLDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class transDDLDlg;
}

/************************************************************************************************************************
【类名】                                   transDDLDlg
【功能】                                   封装设置译者报名截止日期界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          两个私有槽函数
                                          数据成员的获取和设置函数
【开发者及日期】                             门恺文2019.7.27
【更改记录】
************************************************************************************************************************/

class transDDLDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit transDDLDlg(QWidget *parent = nullptr);
    ~transDDLDlg();

    //任务编号设置函数
    void setAssignId(int value);

    //负责人任务编号设置函数
    void setPncpId(int value);

    //负责人用户编号设置函数
    void setPncpCode(int value);

private slots:

    //确认设置截止日期槽函数
    void on_confirmBtn_clicked();

    //日历上日期改变槽函数
    void on_calendar_selectionChanged();

private:
    Ui::transDDLDlg *ui;

    int assignId;
    int pncpId;
    int pncpCode;
    QString DDL;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // TRANSDDLDLG_H
