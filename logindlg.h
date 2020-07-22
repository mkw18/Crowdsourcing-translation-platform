/************************************************************************************************************************
【文件名】                                  logindlg.h
【模块功能和目的】                           Logindlg类声明，对应登录操作
【开发者及日期】                             门恺文 2019.7.24
【更改记录】
************************************************************************************************************************/

#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "signupdlg.h"
#include <QMessageBox>
#include "database.h"

namespace Ui {
class Logindlg;
}

/************************************************************************************************************************
【类名】                                   Logindlg
【功能】                                   封装登录界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          三个私有槽函数
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
************************************************************************************************************************/

class Logindlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit Logindlg(QWidget *parent = nullptr);
    ~Logindlg();

    //用户名获取函数
    QString getUsername() const;

    //用户编号的获取和设置函数
    int getUserCode() const;
    void setUserCode(int value);

private slots:
    //登录按钮槽函数
    void on_btnLogin_clicked();

    //注册按钮槽函数
    void on_btnRegister_clicked();

    //找回密码链接槽函数
    void on_commandLinkButton_clicked();

private:
    Ui::Logindlg *ui;

    QString Username;
    int userCode;
    QList<User>& userInfoList = Database::userList;

};

#endif // LOGINDLG_H
