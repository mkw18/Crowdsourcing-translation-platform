/************************************************************************************************************************
【文件名】                                  signupdlg.h
【模块功能和目的】                           Signupdlg类声明，对应注册界面
【开发者及日期】                             门恺文 2019.7.23
【更改记录】
************************************************************************************************************************/

#ifndef SIGNUPDLG_H
#define SIGNUPDLG_H

#include <QDialog>
#include <QList>
#include <QString>
#include <QLabel>
#include "database.h"

namespace Ui {
class Signupdlg;
}

/************************************************************************************************************************
【类名】                                   Signupdlg
【功能】                                   封装注册界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          两个私有槽函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
************************************************************************************************************************/

class Signupdlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit Signupdlg(QWidget *parent = nullptr);
    ~Signupdlg();


private slots:
    //确认注册槽函数
    void on_btnSignup_clicked();

    //取消注册槽函数
    void on_btnQuit_clicked();

private:
    Ui::Signupdlg *ui;

    QLabel* errMsg = nullptr;
    QList<User>& userInfoList = Database::userList;
};

#endif // SIGNUPDLG_H
