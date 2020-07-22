/************************************************************************************************************************
【文件名】                                  assignpublisher.h
【模块功能和目的】                           AssignPublisher类声明，封装所有与发布者有关的数据和操作
【开发者及日期】                             门恺文 2019.7.22
【更改记录】
************************************************************************************************************************/

#ifndef ASSIGNPUBLISHER_H
#define ASSIGNPUBLISHER_H
#include "assignment.h"

/************************************************************************************************************************
【类名】                                   AssignPublisher
【功能】                                   发布者任务类，封装发布者的信息，如发布者用户名、发布者用户编号、发布者所获取的最终译文等
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class AssignPublisher :public Assignment
{
public:
    //构造函数，将每个成员都赋初值，更好实现多态
    AssignPublisher(Translanguage trans, QString title = "", QString content = "", QString desc = "",
                    QString startTime = QDate::currentDate().toString("yyyy-MM-dd"),
                    QString endTime = QDate::currentDate().toString("yyyy-MM-dd"), int pncpNum = 0, int transNum = 0,
                    QString pncpDDL = QDate::currentDate().toString("yyyy-MM-dd"),
                    QString transDDL = QDate::currentDate().toString("yyyy-MM-dd"),
                    QString trial = "", double reward = 0,
                    Status status = RECUITING_PRICIPAL, int id = -1,
                    QString Username = "",int PublisherCode = -1, QString finish = "");
    //虚析构函数
    virtual ~AssignPublisher();

    //发布者用户名的获取和得到函数
    QString sUserName() const;
    void setSUserName(const QString &sUserName);

    //发布者用户编号的获取和设置函数
    int getIPublisherCode() const;
    void setIPublisherCode(int iPublisherCode);

    //合并后译文的获取和设置函数
    QString getSFinish() const;
    void setSFinish(const QString &sFinish);

private:
    QString m_sUserName;
    int m_iPublisherCode;
    QString m_sFinish;
};

#endif // ASSIGNPUBLISHER_H
