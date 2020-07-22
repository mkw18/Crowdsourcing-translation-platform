/************************************************************************************************************************
【文件名】                  person.cpp
【功能模块和目的】           实现Person类成员函数，Person类为父类
【开发者及日期】             门恺文 2019.7.22
【更改记录】                2019.7.22增加获取信息函数实现
************************************************************************************************************************/

#include "person.h"


/***********************************************************************************************************************
【函数名称】                                 Person()
【函数功能】                                 类Person的构造函数，在创建对象时被调用
【参数】                                    QString name, QString mobilePhone, QString email, QString id，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Person::Person(QString name, QString mobilePhone, QString email, QString id)
{
    m_sName = name;
    m_sMobilePhone = mobilePhone;
    m_sEmail = email;
    m_sId = id;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 Person()
【函数功能】                                 类Person的拷贝构造函数，在对象复制时被调用
【参数】                                    const Person &person，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Person::Person(const Person &person)
{
    m_sName = person.m_sName;
    m_sMobilePhone = person.m_sMobilePhone;
    m_sEmail = person.m_sEmail;
    m_sId = person.m_sId;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 ~Person()
【函数功能】                                 类Person的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

Person::~Person()
{
    //析构时无特殊需求
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 operator=()
【函数功能】                                 类Person的重载赋值运算符
【参数】                                    const Person &person，输入参数
【返回值】                                   该对象
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

Person &Person::operator=(const Person &person)
{
    m_sName = person.m_sName;
    m_sMobilePhone = person.m_sMobilePhone;
    m_sEmail = person.m_sEmail;
    m_sId = person.m_sId;
    //将赋值后的对象返回
    return *this;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 setName()
【函数功能】                                 成员m_sName的设置函数
【参数】                                     Name, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Person::setName(const QString& Name)
{
    m_sName = Name;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 setMobilePhone()
【函数功能】                                 成员m_sMobilePhone的设置函数
【参数】                                     MobilePhone, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Person::setMobilePhone(const QString& MobilePhone)
{
    m_sMobilePhone = MobilePhone;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 setEmail()
【函数功能】                                 成员m_sEmail的设置函数
【参数】                                     Email, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Person::setEmail(const QString& Email)
{
    m_sEmail = Email;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 setId()
【函数功能】                                 成员m_sId的设置函数
【参数】                                     Id, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void Person::setId(const QString& Id)
{
    m_sId = Id;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 getName()
【函数功能】                                 成员m_sName的获取函数
【参数】                                    m_sName, QString, 输出参数
【返回值】                                   m_sName，姓名
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const QString &Person::getName()
{
    return m_sName;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 getMobilePhone()
【函数功能】                                 成员m_sMobilePhone的获取函数
【参数】                                    m_sMobilePhone, QString, 输出参数
【返回值】                                   m_sMobilePhone，电话
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const QString &Person::getMobilePhone()
{
    return m_sMobilePhone;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 getEmail()
【函数功能】                                 成员m_sEmail的获取函数
【参数】                                    m_sEmail, QString, 输出参数
【返回值】                                   m_sEmail，邮箱
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const QString &Person::getEmail()
{
    return m_sEmail;
}

//-----------------------------------------------------------------------------------------------------------------------

/***********************************************************************************************************************
【函数名称】                                 getId()
【函数功能】                                 成员m_sId的获取函数
【参数】                                    m_sId, QString, 输出参数
【返回值】                                   m_sId，身份证号
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

const QString &Person::getId()
{
    return m_sId;
}
