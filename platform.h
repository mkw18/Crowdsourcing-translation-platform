/************************************************************************************************************************
【文件名】                                  platform.h
【功能模块和目的】                            Platform类声明，继承自person类
【开发者及日期】                             门恺文 2019.7.22
【更改记录】                                 2019.7.22-添加工号，将基类也有的函数设为虚函数
************************************************************************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H
#include "person.h"

/************************************************************************************************************************
【类名】                                   Platform
【功能】                                   封装工作人员类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class Platform :public Person
{
public:
    //默认构造函数、构造函数、拷贝构造函数、虚析构函数、重载赋值运算符，构造函数对每个对象赋初值
    Platform();
    Platform(const QString& name, const QString& mobilePhone, const QString& email,
             const QString& id = "", const QString& CV = "", const int& jobNum = -1);
    Platform(const Platform& platform);
    virtual ~Platform();
    Platform& operator=(const Platform& platform);

    //修改工作人员信息
    void setCV(QString CV);
    void setIJobNum(int uJobNum);
    static void setG_iJobTotal(int value);


    //获取工作人员信息

    const QString& getCV();
    const int& getJobNum();

    static const int& getJobTotal();



private:
    QString m_sCV;
    int m_iJobNum;
    static int g_iJobTotal;
};

#endif // PLATFORM_H
