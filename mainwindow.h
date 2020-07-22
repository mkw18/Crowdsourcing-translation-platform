/************************************************************************************************************************
【文件名】                                  mainwindow.h
【模块功能和目的】                           MainWindow类声明，对应首页
【开发者及日期】                             门恺文 2019.7.24
【更改记录】
************************************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "database.h"

namespace Ui {
class MainWindow;
class QlineEdit;
class QDialog;
}

/************************************************************************************************************************
【类名】                                   MainWindow
【功能】                                   封装首页类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          九个私有槽函数
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
************************************************************************************************************************/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //用户编号获取和设置函数
    void setUserCode(int value);

private slots:
    //登录槽函数
    void on_btnLogin_clicked();

    //注册槽函数
    void on_btnRegister_clicked();

    //应聘槽函数
    void on_actionemployment_triggered();

    //进入图书主页槽函数
    void on_actionEnter_triggered();

    //进入个人主页槽函数
    void on_actionEnter_3_triggered();

    //进入信息维护槽函数
    void on_actionInfomation_triggered();

    //充值槽函数
    void on_actionDeposit_triggered();

    //发布新任务槽函数
    void on_assignBtn_clicked();

    //登出槽函数
    void on_signoutBtn_clicked();

private:
    Ui::MainWindow *ui;

    QLabel* loginMsg = nullptr;
    QString Username;
    int userCode;
    QList<User>& userList = Database::userList;
};

#endif // MAINWINDOW_H
