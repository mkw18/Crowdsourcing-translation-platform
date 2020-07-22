/************************************************************************************************************************
【文件名】                                  auditdlg.h
【模块功能和目的】                           AuditDlg类声明，与审核负责人和译者有关的界面
【开发者及日期】                             门恺文 2019.7.26
【更改记录】
************************************************************************************************************************/

#ifndef AUDITDLG_H
#define AUDITDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AuditDlg;
}

/************************************************************************************************************************
【类名】                                   AuditDlg
【功能】                                   审核对话框界面类，发布者指定负责人、负责人指定译者均通过此类
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
                                          一个私有槽函数处理信号
【开发者及日期】                             门恺文2019.7.26
【更改记录】
************************************************************************************************************************/

class AuditDlg : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit AuditDlg(QWidget *parent = nullptr);
    //析构函数
    ~AuditDlg();

    //申请者用户编号的设置函数
    void setApplyCode(int value);

    //申请者任务编号的设置函数
    void setApplyId(int value);

    //申请者类型的设置函数
    void setType(int value);

    //审核对话框标头的设置函数
    void setFront(const QString &value);

    //用户编号的设置函数
    void setUserCode(int value);

    //任务编号的设置函数
    void setAssignId(int value);

private slots:
    //审核通过按钮槽函数
    void on_passBtn_clicked();

private:
    Ui::AuditDlg *ui;

    int userCode;
    int applyCode;
    int applyId;
    int assignId;
    //申请者类型，0为申请负责人，1为申请译者
    int type;
    //在设置标头后界面打开会出现对应标题
    QString front;
    QList<User>& userInfoList = Database::userList;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // AUDITDLG_H
