/************************************************************************************************************************
【文件名】                                  msgboxdlg.h
【模块功能和目的】                           MsgBoxDlg类声明，对应消息盒子界面
【开发者及日期】                             门恺文 2019.7.26
【更改记录】
************************************************************************************************************************/

#ifndef MSGBOXDLG_H
#define MSGBOXDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class MsgBoxDlg;
}

/************************************************************************************************************************
【类名】                                   MsgBoxDlg
【功能】                                   封装消息盒子类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员获取和设置函数
                                          一个私有槽函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
************************************************************************************************************************/

class MsgBoxDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit MsgBoxDlg(QWidget *parent = nullptr);
    ~MsgBoxDlg();

    //用户编号获取和设置函数
    void setUserCode(int value);

private slots:
    //进入消息详情槽函数
    void enterDetail(const QModelIndex &index);

private:
    Ui::MsgBoxDlg *ui;
    QList<MsgBox>& msgList = Database::msgList;
    QList<User>& userInfoList = Database::userList;
    int userCode;
    int msgId;
    int senderCode;
};

#endif // MSGBOXDLG_H
