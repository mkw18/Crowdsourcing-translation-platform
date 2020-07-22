/**********************************************************************************************************************
【文件名】                                  assignpublisher.cpp
【功能模块和目的】                            AssignPublisher类中成员函数的实现
【开发者及日期】                             门恺文2019.7.22
【更改记录】
**********************************************************************************************************************/

#include "assignpublisher.h"

/***********************************************************************************************************************
【函数名称】                                 AssignPublisher()
【函数功能】                                 类AssignPublisher的构造函数，在创建对象时被调用
【参数】                                    Translanguage trans, QString title, QString content, QString desc, QString startTime,
                                           QString endTime, int pncpNum,
                                           int transNum, QString pncpDDL, QString transDDL, QString trial, double reward,
                                           Status status, int id, QString Username, int PublisherCode, QString finish，均为输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.22
【更改记录】
***********************************************************************************************************************/

AssignPublisher::AssignPublisher(Translanguage trans, QString title, QString content, QString desc, QString startTime,
                                 QString endTime, int pncpNum, int transNum, QString pncpDDL, QString transDDL,
                                 QString trial, double reward, Status status, int id,
                                 QString Username, int PublisherCode, QString finish) :Assignment(trans, title, content, desc, startTime,
                                                                                      endTime, pncpNum, transNum, pncpDDL,
                                                                                      transDDL, trial, reward, status, id)
{
    m_sUserName = Username;
    m_iPublisherCode = PublisherCode;
    m_sFinish = finish;
}

/***********************************************************************************************************************
【函数名称】                                 ~AssignPublisher()
【函数功能】                                 类AssignPublisher的析构函数，在对象被销毁时调用
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

AssignPublisher::~AssignPublisher()
{
    //析构函数无特殊要求
}


/***********************************************************************************************************************
【函数名称】                                 sUserName()
【函数功能】                                 成员m_sUserName的获取函数
【参数】                                     m_sUserName, QString, 输出参数
【返回值】                                   m_sUserName，用户名
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

QString AssignPublisher::sUserName() const
{
    return m_sUserName;
}

/***********************************************************************************************************************
【函数名称】                                 setSUserName()
【函数功能】                                 成员m_sUserName的设置函数
【参数】                                     sUserName, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void AssignPublisher::setSUserName(const QString &sUserName)
{
    m_sUserName = sUserName;
}

/***********************************************************************************************************************
【函数名称】                                 getIPublisherCode()
【函数功能】                                 成员m_iPublisherCode的获取函数
【参数】                                    m_iPublisherCode, int, 输出参数
【返回值】                                   m_iPublisherCode，用户编号
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

int AssignPublisher::getIPublisherCode() const
{
    return m_iPublisherCode;
}

/***********************************************************************************************************************
【函数名称】                                 setIPublisherCode()
【函数功能】                                 成员m_iPublisherCode的设置函数
【参数】                                     iPublisherCode, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void AssignPublisher::setIPublisherCode(int iPublisherCode)
{
    m_iPublisherCode = iPublisherCode;
}

/***********************************************************************************************************************
【函数名称】                                 getSFinish()
【函数功能】                                 成员m_sFinish的获取函数
【参数】                                    m_sFinish, QString, 输出参数
【返回值】                                   m_sFinish，合并后的译文
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

QString AssignPublisher::getSFinish() const
{
    return m_sFinish;
}

/***********************************************************************************************************************
【函数名称】                                 setSFinish()
【函数功能】                                 成员m_sFinish的设置函数
【参数】                                     sFinish, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.22
【更改记录】
***********************************************************************************************************************/

void AssignPublisher::setSFinish(const QString &sFinish)
{
    m_sFinish = sFinish;
}
