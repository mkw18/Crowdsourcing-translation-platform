/************************************************************************************************************************
【文件名】                                  assignment.h
【模块功能和目的】                           Assignment类声明，可供未参与用户使用
【开发者及日期】                             门恺文 2019.7.22
【更改记录】
************************************************************************************************************************/

#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "translanguage.h"
#include <QString>
#include <QDateTime>

//对枚举类型Status的定义
enum Status {RECUITING_PRICIPAL, RECUITING_TRANSLATOR, ON_TRANSLATING, TRANSLATION_FINISHED, ON_SHELF};

/************************************************************************************************************************
【类名】                                   Assignment
【功能】                                   任务类，封装了任务的所有基本信息，如任务编号、任务标题、任务内容、任务简介、任务状态、任务周期、
                                          负责人和译者报名截止时间、任务金额、译者报名人数等。同时是一个重要的基类，有三个派生类
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class Assignment
{
public:
    //构造函数，将所有数据成员赋初值
    Assignment(Translanguage trans, QString title = "", QString content = "", QString desc = "",
               QString startTime = QDate::currentDate().toString("yyyy-MM-dd"),
               QString endTime = QDate::currentDate().toString("yyyy-MM-dd"), int pncpNum = 0, int transNum = 0,
               QString pncpDDL = QDate::currentDate().toString("yyyy-MM-dd"),
               QString transDDL = QDate::currentDate().toString("yyyy-MM-dd"),
               QString trial = "", double reward = 0,
               Status status = RECUITING_PRICIPAL, int id = -1);
    //赋值构造函数，保障对象在被赋值时的安全性
    Assignment(const Assignment& assign);
    //析构函数，由于是基类，所以析构函数为虚函数
    virtual ~Assignment();
    //重载赋值运算符，保证在赋值时的安全性
    Assignment& operator=(const Assignment& assign);

    //获取任务信息
    const QString& getContent();
    const QString& getDesc();
    const QString& getStartTime();
    const QString& getEndTime();
    const int& getPncpNum();
    const int& getTransNum();
    const QString& getPncpDDL();
    const QString& getTransDDL();
    const QString& getTrial();
    const double& getReward();
    const Translanguage& getTrans();
    const Status& getStatus();
    const int& getAssignId();
    static int& getAssignNum();

    //设置任务信息
    void setPncpDDL(const QString& pncpddl);
    void setTransDDL(const QString& transddl);
    void setReward(const double& reward);

    //起始日期的获取和设置函数
    QString getSStartTime() const;
    void setSStartTime(const QString &sStartTime);

    //截止日期的获取和设置函数
    QString getSEndTime() const;
    void setSEndTime(const QString &sEndTime);

    //负责人总人数设置，在AssignPrincipal类中被调用
    void setIPncpNum(int iPncpNum);

    //译者总人数设置，在AssignTranslator类中被调用，从而确定译者总人数
    void setITransNum(int iTransNum);

    //任务标题的获取和设置函数
    QString getSTitle() const;
    void setSTitle(const QString &sTitle);

    //任务状态的设置函数
    void setEStatus(const Status &eStatus);

private:
    //复制函数，供复制构造函数和重载=运算符使用
    void copy(const Assignment& assign);

    //数据成员
    QString m_sTitle;
    QString m_sContent;
    QString m_sDescription;
    QString m_sStartTime;
    QString m_sEndTime;
    int m_iPncpNum;
    int m_iTransNum;
    QString m_sPncpDDL;
    QString m_sTransDDL;
    QString m_sTrial;
    double m_dReward;
    //内嵌的Translanguage类，翻译的原文和译文
    Translanguage m_tTrans;
    //记录任务状态
    Status m_eStatus;
    //任务编号
    int m_iAssignId;
    //记录总任务数
    static int g_iAssignNum;
};

#endif // ASSIGNMENT_H
