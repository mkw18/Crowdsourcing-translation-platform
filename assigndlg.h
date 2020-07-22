/************************************************************************************************************************
【文件名】                                  assigndlg.h
【功能模块和目的】                            assignDlg类声明
【开发者及日期】                             门恺文2019.7.27
【更改记录】
*************************************************************************************************************************/

#ifndef ASSIGNDLG_H
#define ASSIGNDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class assignDlg;
}

/************************************************************************************************************************
【类名】                                   assgnDlg
【功能】                                   进入任务详情，获取任务详细信息，在负责人报名截止日期之前可报名负责人，在负责人指定译者报名截止日期
                                          之后和译者报名截止之前可报名译者。可查看的任务信息包括任务编号、标题、内容、简介、负责人报名截止日
                                          期、译者报名截止日期，任务金额，原文语言、译文语言（以List View形式呈现）、负责人报名情况、
                                          译者报名情况。
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
                                          两个私有槽函数，处理信号
                                          对"database.h"中的列表引用，以实时更新列表信息
【开发者及日期】                             门恺文2019.7.27
【更改记录】
************************************************************************************************************************/

class assignDlg : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit assignDlg(QWidget *parent = nullptr);
    //析构函数
    ~assignDlg();

    //任务编号的获取和设置
    int getAssignId() const;
    void setAssignId(int value);

    //用户名的获取和设置
    QString getUsername() const;
    void setUsername(const QString &value);

    //任务标题的获取和设置
    QString getTitle() const;
    void setTitle(const QString &value);

    //任务简介的获取和设置
    QString getDesc() const;
    void setDesc(const QString &value);

    //进入任务的用户编号的获取和设置
    int getUserCode() const;
    void setUserCode(int value);

    //任务发布者编号的获取和设置
    int getPublisherCode() const;
    void setPublisherCode(int value);

private slots:
    //报名负责人按钮的槽函数，进入负责人报名界面
    void on_pncpBtn_clicked();

    //报名译者按钮的槽函数，进入译者报名界面
    void on_transBtn_clicked();

private:
    Ui::assignDlg *ui;

    int userCode;
    int publisherCode;
    int m_iAssignId;
    QString title;
    QString Username;
    QString Desc;
    //以引用"database.h"中全局变量的方式，实现对列表的实时更改
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
};

#endif // ASSIGNDLG_H
