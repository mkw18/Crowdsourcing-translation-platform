/************************************************************************************************************************
【文件名】                                  personalmainwindow.h
【模块功能和目的】                           PersonalMainWindow类声明，对应个人中心界面
【开发者及日期】                             门恺文 2019.7.23
【更改记录】
************************************************************************************************************************/

#ifndef PERSONALMAINWINDOW_H
#define PERSONALMAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "database.h"

namespace Ui {
class PersonalMainWindow;
}

/************************************************************************************************************************
【类名】                                   PersonalMainWindow
【功能】                                   封装个人中心界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
                                          七个私有槽函数
                                          一个封装了一些重复操作的函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
************************************************************************************************************************/

class PersonalMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit PersonalMainWindow(QWidget *parent = nullptr);
    ~PersonalMainWindow();

    //用户编号获取和设置函数
    void setUserCode(int value);

private slots:
    //进入信息维护槽函数
    void on_infoBtn_clicked();

    //进入充值槽函数
    void on_depositBtn_clicked();

    //进入消息盒子槽函数
    void on_messageBtn_clicked();

    //进入任务详情槽函数
    void enterAssignment(const QModelIndex&);

    //进入首页槽函数
    void on_actionEnter_triggered();

    //进入图书主页槽函数
    void on_actionEnter_2_triggered();

    //应聘槽函数
    void on_actionEmployment_triggered();

private:
    Ui::PersonalMainWindow *ui;

    void init();

    QList<User>& userInfoList = Database::userList;
    QList<AssignPublisher>& publisherList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    int userCode;
};

#endif // PERSONALMAINWINDOW_H
