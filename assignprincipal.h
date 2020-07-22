/************************************************************************************************************************
【文件名】                                  assignprincipal.h
【模块功能和目的】                           AssignPrincipal类声明，封装所有与负责人有关的数据和操作
【开发者及日期】                             门恺文 2019.7.22
【更改记录】
************************************************************************************************************************/

#ifndef ASSIGNPRINCIPAL_H
#define ASSIGNPRINCIPAL_H
#include "assignment.h"

/************************************************************************************************************************
【类名】                                   AssignPrincipal
【功能】                                   负责人任务类，封装负责人的信息，如负责人任务编号、负责人用户名、用户编号、简历、是否被指定为该任务
                                          的负责人等
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class AssignPrincipal :public Assignment
{
public:
    //构造函数
    AssignPrincipal(Translanguage trans, QString title = "", QString content = "", QString desc = "",
                    QString startTime = QDate::currentDate().toString("yyyy-MM-dd"),
                    QString endTime = QDate::currentDate().toString("yyyy-MM-dd"), int pncpNum = 0, int transNum = 0,
                    QString pncpDDL = QDate::currentDate().toString("yyyy-MM-dd"),
                    QString transDDL = QDate::currentDate().toString("yyyy-MM-dd"),
                    QString trial = "", double reward = 0,
                    Status status = RECUITING_PRICIPAL, int id = -1,
                    QString pncpName = "", int pncpCode = -1, QString CV = "",
                    int num = -1, bool confirm = false);

    //析构函数
    virtual ~AssignPrincipal();

    //负责人任务编号的获取和设置函数
    int getINum() const;
    void setINum(int iNum);

    //总负责人人数的获取函数
    static int getG_iPncpNum();

    //负责人姓名的获取和设置函数
    QString getSPncpName() const;
    void setSPncpName(const QString &sPncpName);

    //负责人简历的获取和设置函数
    QString getSCV() const;
    void setSCV(const QString &sCV);

    //负责人用户编号的获取和设置函数
    int getIPncpCode() const;
    void setIPncpCode(int iPncpCode);

    //负责人是否被指定的获取和设置函数
    bool getBIsConfirmed() const;
    void setBIsConfirmed(bool bIsConfirmed);

private:
    void copy(AssignPrincipal& assign);
    //负责人任务编号
    int m_iNum;
    //负责人总人数
    static int g_iPncpNum;
    QString m_sPncpName;
    int m_iPncpCode;
    QString m_sCV;
    //当负责人被指定为项目负责人时，该属性变为true, 此前默认为false
    bool m_bIsConfirmed;
};

#endif // ASSIGNPRINCIPAL_H
