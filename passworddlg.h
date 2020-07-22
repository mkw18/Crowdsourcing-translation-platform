/************************************************************************************************************************
【文件名】                                  passworddlg.h
【模块功能和目的】                           PasswordDlg类声明，对应找回密码界面
【开发者及日期】                             门恺文 2019.7.23
【更改记录】
************************************************************************************************************************/

#ifndef PASSWORDDLG_H
#define PASSWORDDLG_H

#include <QDialog>
#include <QTimer>
#include <QTime>
#include "database.h"
#include <QList>

namespace Ui {
class PasswordDlg;
}

/************************************************************************************************************************
【类名】                                   PasswordDlg
【功能】                                   封装找回密码界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          两个私有槽函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
************************************************************************************************************************/

class PasswordDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit PasswordDlg(QWidget *parent = nullptr);
    ~PasswordDlg();


private slots:
    //发送验证码槽函数
    void on_sendBtn_clicked();

    //确定修改槽函数
    void on_confirmBtn_clicked();

private:
    Ui::PasswordDlg *ui;
    int userCode;
    QList<User>& userInfoList = Database::userList;
};

#endif // PASSWORDDLG_H
