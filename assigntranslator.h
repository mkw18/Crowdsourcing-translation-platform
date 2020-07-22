/************************************************************************************************************************
【文件名】                                  assigntranslator.h
【模块功能和目的】                           AssignTranslator类声明，封装所有与译者有关的数据和操作
【开发者及日期】                             门恺文 2019.7.22
【更改记录】
************************************************************************************************************************/

#ifndef ASSIGNTRANSLATOR_H
#define ASSIGNTRANSLATOR_H
#include <QString>
#include "assignment.h"

//对枚举类型State的定义
enum State{APPLYING, CONFIRMED, TRANSLATING, SUBMITED};

/************************************************************************************************************************
【类名】                                   AssignTranslator
【功能】                                   封装译者信息，如译者任务编号、译者用户名、用户编号、简历、译者状态、译者提交的译文、译者获得的反馈
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class AssignTranslator :public Assignment
{
public:
    //构造函数，将每个成员都赋初值，更好实现多态
    AssignTranslator(Translanguage trans, QString title = "", QString content = "", QString desc = "",
                     QString startTime = QDate::currentDate().toString("yyyy-MM-dd"),
                     QString endTime = QDate::currentDate().toString("yyyy-MM-dd"), int pncpNum = 0, int transNum = 0,
                     QString pncpDDL = QDate::currentDate().toString("yyyy-MM-dd"),
                     QString transDDL = QDate::currentDate().toString("yyyy-MM-dd"),
                     QString trial = "", double reward = 0,
                     Status status = RECUITING_PRICIPAL, int id = -1,
                     QString transName = "", int TransCode = -1, QString CV = "",
                     QString mission = "", int num = -1, State state = APPLYING, QString feedback = "", QString submit = "");
    //虚析构函数
    virtual ~AssignTranslator();

    //译者子任务和获取和设置函数
    QString sMission() const;
    void setSMission(const QString &sMission);

    //译者任务编号的获取和设置函数
    int iTransId() const;
    void setITransId(int iTransId);

    //译者总人数的获取和设置函数
    static int getG_iTransNum();
    static void setG_iTransNum(int value);

    //译者应户名的获取和设置函数
    QString getSTransName() const;
    void setSTransName(const QString &sTransName);

    //译者用户编号的获取和设置函数
    int getITransCode() const;
    void setITransCode(int iTransCode);

    //译者简历的获取和设置函数
    QString getSCV() const;
    void setSCV(const QString &sCV);

    //译者提交或暂存文件的获取和设置函数
    QString getSSubmit() const;
    void setSSubmit(const QString &sSubmit);

    //译者获得反馈的获取和设置函数
    QString getSFeedback() const;
    void setSFeedback(const QString &sFeedback);

    //译者状态的获取和设置函数
    State getETransState() const;
    void setETransState(const State &eTransState);

    //译者子任务的获取函数
    QString getSMission() const;

private:
    QString m_sMission;
    //译者编号
    int m_iTransId;
    //译者总人数
    static int g_iTransNum;
    QString m_sTransName;
    int m_iTransCode;
    QString m_sCV;
    QString m_sSubmit;
    QString m_sFeedback;
    //译者状态
    State m_eTransState;
};

#endif // ASSIGNTRANSLATOR_H
