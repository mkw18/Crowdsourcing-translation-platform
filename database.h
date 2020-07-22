/************************************************************************************************************************
【文件名】                                  database.h
【模块功能和目的】                           Database类声明，封装容器
【开发者及日期】                             门恺文 2019.7.30
【更改记录】
************************************************************************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <QApplication>
#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QList>
#include "system.h"

/************************************************************************************************************************
【类名】                                   Database
【功能】                                   封装在数据库中创建表、从数据库导入数据、向数据库导入数据、导入数据库前先清理数据库的四个函数
                                          以及需要与数据库发生联系的容器
【接口说明】                                四个函数实现系统与数据库之间的信息交流
【开发者及日期】                             门恺文2019.7.30
【更改记录】                                2019.7.31及2019.8.1由于原来的Qt没有导入数据库的组件，改变了多次导入方法，最后问题在重装了一次
                                          Qt后解决
************************************************************************************************************************/

class Database
{
public:
    //创建表头
    static void creatConnection(QSqlQuery* q);

    //将数据从数据库中导入容器
    static QSqlDatabase loadData();

    //保存数据，系统运行结束后将数据存入数据库
    static bool saveData(QSqlDatabase db);

    //清理数据库，在重新放入数据之前先清理，保证信息的有效更新
    static bool cleanData(QSqlQuery* q);

    //需要存储的类的容器
    static QList<User> userList;
    static QList<Platform> platformList;
    static QList<Assignment> assignList;
    static QList<AssignPrincipal> pncpList;
    static QList<AssignPublisher> pubList;
    static QList<AssignTranslator> transList;
    static QList<MsgBox> msgList;
};

#endif // DATABASE_H
