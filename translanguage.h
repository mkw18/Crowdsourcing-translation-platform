/************************************************************************************************************************
【文件名】                                  translanguage
【功能模块和目的】                            Translanguage类声明，记录翻译语言
【开发者及日期】                              门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

#ifndef TRANSLANGUAGE_H
#define TRANSLANGUAGE_H
#include <QString>
#include <QVector>


/************************************************************************************************************************
【类名】                                   Translanguage
【功能】                                   封装翻译所涉及的语言，原文语言，多种译文语言，译文语言种类数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员的获取和设置函数
【开发者及日期】                             门恺文2019.7.22
【更改记录】
************************************************************************************************************************/

class Translanguage
{
public:
    //默认构造函数、构造函数、拷贝构造函数、虚析构函数、重载赋值运算符，构造函数对每个对象赋初值
    Translanguage();
    Translanguage(QVector<QString> goal, QString oril = "", int vari = 0);
    Translanguage(const Translanguage& trans);
    virtual ~Translanguage();
    Translanguage& operator=(const Translanguage& trans);

    //获取信息
    QString getOri() const;
    int getVar() const;
    QVector<QString> getGoal() const;

    //设置信息
    void setOri(const QString& oril);
    void setVar(const int& Vari);
    void addGoal(const QString Goal);
    void setPsGoalLanguage(const QVector<QString> &psGoalLanguage);

private:
    QString m_sOriLanguage;
    int m_iVariation;
    QVector<QString> m_psGoalLanguage;
};

#endif // TRANSLANGUAGE_H
