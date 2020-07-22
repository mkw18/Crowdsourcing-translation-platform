/************************************************************************************************************************
【文件名】                                  feedbackdlg.h
【模块功能和目的】                           FeedBackDlg类声明，负责人对译者翻译的反馈
【开发者及日期】                             门恺文 2019.7.28
【更改记录】
************************************************************************************************************************/

#ifndef FEEDBACKDLG_H
#define FEEDBACKDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class FeedBackDlg;
}

/************************************************************************************************************************
【类名】                                   FeedBackDlg
【功能】                                   封装负责人给予反馈消息界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          一个私有槽函数
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.28
【更改记录】
************************************************************************************************************************/

class FeedBackDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit FeedBackDlg(QWidget *parent = nullptr);
    ~FeedBackDlg();

    //标题设置和获取函数
    void setFront(const QString &value);

    //译者任务编号的获取和设置函数
    void setTransId(int value);

    //任务编号的获取和设置函数
    void setAssignId(int value);

    //译者用户编号的获取和设置函数
    void setTransCode(int value);

    //负责人用户编号
    void setPncpCode(int value);

private slots:
    //反馈提交槽函数
    void on_feedbackBtn_clicked();

private:
    Ui::FeedBackDlg *ui;

    QString front;
    int transId;
    int assignId;
    int transCode;
    int pncpCode;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // FEEDBACKDLG_H
