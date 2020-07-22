/************************************************************************************************************************
【文件名】                                  infomaintaindlg.h
【模块功能和目的】                           InfoMaintaindlg类声明，对应用户维护信息
【开发者及日期】                             门恺文 2019.7.24
【更改记录】
************************************************************************************************************************/

#ifndef INFOMAINTAINDLG_H
#define INFOMAINTAINDLG_H

#include <QDialog>
#include <QList>
#include "database.h"

namespace Ui {
class InfoMaintaindlg;
}

/************************************************************************************************************************
【类名】                                   InfoMaintaindlg
【功能】                                   封装维护信息界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          三个私有槽函数
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
************************************************************************************************************************/

class InfoMaintaindlg : public QDialog
{
    Q_OBJECT

public:
    //构造函数和析构函数
    explicit InfoMaintaindlg(QWidget *parent = nullptr);
    ~InfoMaintaindlg();

    //用户编号设置函数
    void setUserCode(int value);

private slots:
    //提交更改信息槽函数
    void on_acceptBtn_clicked();

    //充值槽函数
    void on_depositBtn_clicked();

    //更改头像槽函数
    void on_avatarBtn_clicked();

private:
    Ui::InfoMaintaindlg *ui;

    QList<User>& userInfoList = Database::userList;
    QList<MsgBox>& msgList = Database::msgList;
    int userCode;
};

#endif // INFOMAINTAINDLG_H
