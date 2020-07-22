/**********************************************************************************************************************
【文件名】                                  msgbox.cpp
【功能模块和目的】                            MsgBox类中成员函数的实现
【开发者及日期】                             门恺文2019.7.23
【更改记录】
**********************************************************************************************************************/

#include "msgbox.h"

int MsgBox::g_iMsgNum = -1;

/***********************************************************************************************************************
【函数名称】                                 MsgBox()
【函数功能】                                 类MsgBox的构造函数，在创建对象时被调用
【参数】                                    int user, int sender, QString theme, QString msg, int id，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.23
【更改记录】
***********************************************************************************************************************/

MsgBox::MsgBox(int user, int sender, QString theme, QString msg, int id)
{
    m_iUserCode = user;
    m_iSenderCode = sender;
    m_sTheme = theme;
    m_sMessage = msg;
    if (id == -1)
    {
        g_iMsgNum++;
        m_iMsgId = g_iMsgNum;
    }
    else {
        m_iMsgId = id;
        if (id > g_iMsgNum)
        {
            g_iMsgNum = id;
        }
    }
}


/***********************************************************************************************************************
【函数名称】                                 ~MsgBox()
【函数功能】                                 类MsgBox的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

MsgBox::~MsgBox()
{
    //无特殊要求
}

/***********************************************************************************************************************
【函数名称】                                 sMessage()
【函数功能】                                 成员m_sMessage的获取函数
【参数】                                    m_sMessage, QString, 输出参数
【返回值】                                   m_sMessage，消息内容
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

QString MsgBox::sMessage() const
{
    return m_sMessage;
}

/***********************************************************************************************************************
【函数名称】                                 setSMessage()
【函数功能】                                 成员m_sMessage的设置函数
【参数】                                     sMessage, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MsgBox::setSMessage(const QString &sMessage)
{
    m_sMessage = sMessage;
}

/***********************************************************************************************************************
【函数名称】                                 sTheme()
【函数功能】                                 成员m_sTheme的获取函数
【参数】                                    m_sTheme, QString, 输出参数
【返回值】                                   m_sTheme，消息标题
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

QString MsgBox::sTheme() const
{
    return m_sTheme;
}

/***********************************************************************************************************************
【函数名称】                                 setSTheme()
【函数功能】                                 成员m_sTheme的设置函数
【参数】                                     sTheme, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MsgBox::setSTheme(const QString &sTheme)
{
    m_sTheme = sTheme;
}

/***********************************************************************************************************************
【函数名称】                                 getG_iMsgId()
【函数功能】                                 成员g_iMsgId的获取函数
【参数】                                    g_iMsgId, int, 输出参数
【返回值】                                   g_iMsgId，消息总数
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

int MsgBox::getG_iMsgId()
{
    return g_iMsgNum;
}

/***********************************************************************************************************************
【函数名称】                                 setG_iMsgId()
【函数功能】                                 成员g_iMsgId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MsgBox::setG_iMsgId(int value)
{
    g_iMsgNum = value;
}

/***********************************************************************************************************************
【函数名称】                                 getIMsgId()
【函数功能】                                 成员m_iMsgId的获取函数
【参数】                                    m_iMsgId, int, 输出参数
【返回值】                                   m_iMsgId，消息编号
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

int MsgBox::getIMsgId() const
{
    return m_iMsgId;
}

/***********************************************************************************************************************
【函数名称】                                 setIMsgId()
【函数功能】                                 成员m_iMsgId的设置函数
【参数】                                    iMsgId, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MsgBox::setIMsgId(int iMsgId)
{
    m_iMsgId = iMsgId;
}


/***********************************************************************************************************************
【函数名称】                                 iSenderCode()
【函数功能】                                 成员m_iSenderCode的获取函数
【参数】                                    m_iSenderCode, int, 输出参数
【返回值】                                   m_iSenderCode，发送者用户编号
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

int MsgBox::iSenderCode() const
{
    return m_iSenderCode;
}

/***********************************************************************************************************************
【函数名称】                                 setISenderCode()
【函数功能】                                 成员m_iSenderCode的设置函数
【参数】                                    iSenderCode, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MsgBox::setISenderCode(int iSenderCode)
{
    m_iSenderCode = iSenderCode;
}

/***********************************************************************************************************************
【函数名称】                                 iUserCode()
【函数功能】                                 成员m_iUserCode的获取函数
【参数】                                    m_iUserCode, int, 输出参数
【返回值】                                   m_iUserCode，接收者用户编号
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

int MsgBox::iUserCode() const
{
    return m_iUserCode;
}

/***********************************************************************************************************************
【函数名称】                                 setIUserCode()
【函数功能】                                 成员m_iUserCode的设置函数
【参数】                                    iUserCode, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MsgBox::setIUserCode(int iUserCode)
{
    m_iUserCode = iUserCode;
}
