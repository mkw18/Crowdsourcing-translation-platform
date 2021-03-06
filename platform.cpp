/***********************************************************************************************************************
【文件名】                                  platform.cpp
【功能模块和目的】                           Platform类成员函数实现
【开发者及日期】                             门恺文 2019.7.22
【更改记录】                                2019.7.23-完善构造函数，拷贝构造函数添加CV
***********************************************************************************************************************/

#include "platform.h"

int Platform::g_iJobTotal = -1;

/***********************************************************************************************************************
【函数名称】                                 Platform()
【函数功能】                                 类Platform的默认构造函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Platform::Platform()
{
    //默认构造函数
    g_iJobTotal++;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 Platform()
【函数功能】                                 类Platform的构造函数
【参数】                                     const QString& name, const QString& mobilePhone, const QString& email,
                                            const QString& id, const QString& CV, const int &jobNum输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Platform::Platform(const QString& name, const QString& mobilePhone, const QString& email, const QString& id,
                   const QString& CV, const int &jobNum) :Person (name, mobilePhone, email, id)
{
    m_sCV = CV;
    if(jobNum == -1)
    {
        g_iJobTotal++;
        m_iJobNum = g_iJobTotal;
    }
    else
    {
        m_iJobNum = jobNum;
        if (jobNum > g_iJobTotal)
        {
            g_iJobTotal = jobNum;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 Platform()
【函数功能】                                 类Platform的拷贝构造函数
【参数】                                    const Platform &platform输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Platform::Platform(const Platform &platform) :Person (platform)
{
    m_sCV = platform.m_sCV;
    m_iJobNum = platform.m_iJobNum;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 ~Platform()
【函数功能】                                 类Platform的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

Platform::~Platform()
{
    //析构函数无特别定义
}

/***********************************************************************************************************************
【函数名称】                                 operator=()
【函数功能】                                 类Platform的重载赋值运算符
【参数】                                    const Platform &platform，输入参数
【返回值】                                   该对象
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Platform &Platform::operator=(const Platform &platform)
{
    m_sCV = platform.m_sCV;
    m_iJobNum = platform.m_iJobNum;
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 setCV()
【函数功能】                                 成员m_sCV的设置函数
【参数】                                     CV, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Platform::setCV(QString CV)
{
    m_sCV = CV;
}

//----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 getCV()
【函数功能】                                 成员m_sCV的获取函数
【参数】                                    m_sCV, QString, 输出参数
【返回值】                                   m_sCV，工作人员简历
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const QString &Platform::getCV()
{
    return m_sCV;
}

/***********************************************************************************************************************
【函数名称】                                 getJobNum()
【函数功能】                                 成员m_iJobNum的获取函数
【参数】                                    m_iJobNum, int, 输出参数
【返回值】                                   m_iJobNum，工作人员工号
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const int &Platform::getJobNum()
{
    return m_iJobNum;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 getJobTotal()
【函数功能】                                 成员g_iJobTotal的获取函数
【参数】                                    g_iJobTotal, int, 输出参数
【返回值】                                   g_iJobTotal，工作人员总数
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const int &Platform::getJobTotal()
{
    return g_iJobTotal;
}

/***********************************************************************************************************************
【函数名称】                                 setG_iJobTotal()
【函数功能】                                 成员g_iJobTotal的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Platform::setG_iJobTotal(int value)
{
    g_iJobTotal = value;
}

/***********************************************************************************************************************
【函数名称】                                 setIJobNum()
【函数功能】                                 成员m_iJobNum的设置函数
【参数】                                    iJobNum, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Platform::setIJobNum(int uJobNum)
{
    m_iJobNum = uJobNum;
}
