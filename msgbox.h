/************************************************************************************************************************
【文件名】                                  msgbox.h
【模块功能和目的】                           MsgBox类声明，封装与发送、接受消息有关的所有操作
【开发者及日期】                             门恺文 2019.7.23
【更改记录】
************************************************************************************************************************/

#ifndef MSGBOX_H
#define MSGBOX_H
#include "user.h"

/************************************************************************************************************************
【类名】                                   MsgBox
【功能】                                   封装消息盒子类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
************************************************************************************************************************/

class MsgBox
{
public:
    //构造函数，为每个变量赋初值
    MsgBox(int user = -1, int sender = -1, QString theme = "", QString msg = "", int id = -1);
    //析构函数
    virtual ~MsgBox();

    //消息内容获取函数
    QString sMessage() const;

    //发送者编号的获取和设置函数
    int iSenderCode() const;
    void setISenderCode(int iSenderCode);

    //接收者（用户）的获取和设置函数
    int iUserCode() const;
    void setIUserCode(int iUserCode);

    //消息内容设置函数
    void setSMessage(const QString &sMessage);

    //纤细标题的获取和设置函数
    QString sTheme() const;
    void setSTheme(const QString &sTheme);

    //消息总数的获取和设置函数
    static int getG_iMsgId();
    static void setG_iMsgId(int value);

    //消息编号的获取和设置函数
    int getIMsgId() const;
    void setIMsgId(int iMsgId);

private:
    int m_iSenderCode;
    int m_iUserCode;
    QString m_sTheme;
    QString m_sMessage;
    int m_iMsgId;
    static int g_iMsgNum;
};

#endif // MSGBOX_H
