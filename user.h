/************************************************************************************************************************
【文件名】                                  user.h
【模块功能和目的】                           User类声明，对应用户模块
【开发者及日期】                             门恺文 2019.7.22
【更改记录】
************************************************************************************************************************/

#ifndef USER_H
#define USER_H
#include "person.h"
#include "assignment.h"
#include "platform.h"
#include <QString>
#include <QVector>


/************************************************************************************************************************
【类名】                                   User
【功能】                                   封装用户所需要的数据和其函数，是Person类的派生类
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class User :public Person
{
public:
    //构造函数、拷贝构造函数、虚析构函数、重载赋值运算符，构造函数对每个对象赋初值
    User( int code = -1, QString username = "", QString password = "", QString mobilePhone = "",
          QString languageLevel = "", QString name = "", QString email = "", QString id = "",
          double balance = 0, int point = -1, QString avatar = ":/myImages/Images/DefaultAvatar.png");
    User(const User& user);
    virtual ~User();
    User& operator=(const User& user);
    //更改信息
    void addLevel(const QString& level);
    void setUserName(const QString& username);
    void setPassword(const QString& password);
    void setBalance(const double& balance);
    void setPoint(const int& point);

    //获取信息
    QString& getUserName();
    QString& getPassword();
    double& getBalance();
    int& getPoint();

    //用户语言水平获取和设置函数
    QString getSLanguageLevel() const;
    void setSLanguageLevel(const QString &sLanguageLevel);

    //用户头像获取和设置函数
    QString getSAvatar() const;
    void setSAvatar(const QString &sAvatar);

    //用户密码获取和设置函数
    QString getSPassword() const;
    void setSPassword(const QString &sPassword);

    //用户总人数获取和设置函数
    static int getUserNum();
    static void setUserNum(int value);

    //用户编号获取和设置函数
    int getICode() const;
    void setICode(int iCode);

private:
    QString m_sUsername;
    QString m_sPassword;
    QString m_sLanguageLevel;
    double m_dBalance;
    int m_iPoints;
    QString m_sAvatar;
    static int g_iUserNum;
    int m_iCode;
};

#endif // USER_H
