/************************************************************************************************************************
【文件名】                                  person.h
【功能模块和目的】                            person类的声明
【开发者及日期】                             门恺文 2019.7.22
【更改记录】                                 2019.7.22-增加获取信息函数
************************************************************************************************************************/

#ifndef PERSON_H
#define PERSON_H
#include <QString>

/************************************************************************************************************************
【类名】                                   Person
【功能】                                   封装人员基本信息和接口函数，是本系统另一大重要基类
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class Person
{
public:
    //更改信息
    virtual void setName(const QString& Name);
    virtual void setMobilePhone(const QString& MobilePhone);
    virtual void setEmail(const QString& Email);
    virtual void setId(const QString& Id);

    //获取信息
    virtual const QString& getName();
    virtual const QString& getMobilePhone();
    virtual const QString& getEmail();
    virtual const QString& getId();

protected:
    //构造函数、拷贝构造函数、虚析构函数、重载赋值运算符，构造函数对每个对象赋初值
    Person(QString name = "", QString mobilePhone = "", QString email = "", QString id = "");
    Person(const Person& person);
    virtual ~Person();
    Person& operator=(const Person& person);

private:
    QString m_sName;
    QString m_sMobilePhone;
    QString m_sEmail;
    QString m_sId;
};

#endif // PERSON_H
