/************************************************************************************************************************
【文件名】                                  newmission.h
【模块功能和目的】                           newMissionDlg类声明，对应新任务发布界面
【开发者及日期】                             门恺文 2019.7.24
【更改记录】
************************************************************************************************************************/

#ifndef NEWMISSIONDLG_H
#define NEWMISSIONDLG_H

#include <QDialog>
#include <QList>
#include "system.h"
#include <QVector>
#include "database.h"

namespace Ui {
class newMissionDlg;
}

/************************************************************************************************************************
【类名】                                   newMissionDlg
【功能】                                   封装发布新任务界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员获取和设置函数
                                          五个私有槽函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
************************************************************************************************************************/

class newMissionDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit newMissionDlg(QWidget *parent = nullptr);
    ~newMissionDlg();

    //用户名设置函数
    void setUserName(const QString &value);


    //用户编号设置函数
    void setUserCode(int value);

private slots:
    //添加译文语言槽函数
    void on_addBtn_clicked();

    //选择起始日期槽函数
    void on_calendarFrom_selectionChanged();

    //选择截止日期槽函数
    void on_calendarTo_selectionChanged();

    //确定发布槽函数
    void on_finishBtn_clicked();

    //选择负责人报名截止时间槽函数
    void on_calendarPncp_selectionChanged();

private:
    Ui::newMissionDlg *ui;

    QString userName;
    int userCode;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
    QVector<QString> goal;
    int vari;
};

#endif // NEWMISSIONDLG_H
