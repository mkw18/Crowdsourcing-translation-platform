/************************************************************************************************************************
【文件名】                                  pncpassigndlg.h
【模块功能和目的】                           PncpAssignDlg类声明，对应负责人分配子任务界面
【开发者及日期】                             门恺文 2019.7.27
【更改记录】
************************************************************************************************************************/

#ifndef PNCPASSIGNDLG_H
#define PNCPASSIGNDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class PncpAssignDlg;
}

/************************************************************************************************************************
【类名】                                   PncpAssignDlg
【功能】                                   封装负责人分配译者子任务界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
                                          一个私有槽函数
【开发者及日期】                             门恺文2019.7.27
【更改记录】
************************************************************************************************************************/

class PncpAssignDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit PncpAssignDlg(QWidget *parent = nullptr);
    ~PncpAssignDlg();

    //界面标题设置函数
    void setFront(const QString &value);

    //译者任务编号设置函数
    void setTransId(int value);

    //译者用户编号设置函数
    void setTransCode(int value);

    //负责人用户编号设置函数
    void setPncpCode(int value);

    //任务编号设置函数
    void setAssignId(int value);

private slots:
    //确认分配子任务槽函数
    void on_confirmBtn_clicked();

private:
    Ui::PncpAssignDlg *ui;

    QString front;
    int transId;
    int transCode;
    int pncpCode;
    int assignId;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // PNCPASSIGNDLG_H
