/**********************************************************************************************************************
【文件名】                                  database.cpp
【功能模块和目的】                            Database类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.30
【更改记录】
**********************************************************************************************************************/

#include "database.h"
#include <QObject>
#include <QString>
#include <QDebug>

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QString>
#include <QVariantList>
#include <QFile>
//可派生

QList<User> Database::userList;
QList<Platform> Database::platformList;
QList<Assignment> Database::assignList;
QList<AssignPrincipal> Database::pncpList;
QList<AssignPublisher> Database::pubList;
QList<AssignTranslator> Database::transList;
QList<MsgBox> Database::msgList;

/***********************************************************************************************************************
【函数名称】                                 creatConnection()
【函数功能】                                 创建表头
【参数】                                    QSqlQuery *q
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.30
【更改记录】
***********************************************************************************************************************/

void Database::creatConnection(QSqlQuery *q)
{
    QSqlQuery query = *q;
    //创建User表格
    query.exec("create table if not exists User ("
               "userCode int primary key, "
               "username varchar(20), "
               "password varchar(20),"
               "phone varchar(20), "
               "level text, "
               "name varchar(20), "
               "email varchar(30), "
               "id varchar(30), "
               "balance double, "
               "point int, "
               "avatar varchar(30))");
    //创建Platform表格
    query.exec("create table if not exists Platform("
               "jobCode int primary key,"
               "phone varchar(20),"
               "email varchar(30),"
               "id varchar(30),"
               "cv text,"
               "name varchar(20))");
    //创建assignment表格
    query.exec("create table if not exists assignment("
               "id int primary key,"
               "oril varchar(20),"
               "vari int,"
               "title varchar(40),"
               "content text,"
               "desc text,"
               "startTime varchar(20),"
               "endTime varchar(20),"
               "pncpNum int,"
               "transNum int,"
               "pncpDDL varchar(20),"
               "transDDL varchar(20),"
               "trial text,"
               "reward double,"
               "status int,"
               "goal text)");
    //创建assignPub表格
    query.exec("create table if not exists assignPub("
               "id int primary key,"
               "oril varchar(20),"
               "vari int,"
               "title varchar(40),"
               "content text,"
               "desc text,"
               "startTime varchar(20),"
               "endTime varchar(20),"
               "pncpNum int,"
               "transNum int,"
               "pncpDDL varchar(20),"
               "transDDL varchar(20),"
               "trial text,"
               "reward double,"
               "status int,"
               "goal text,"
               "username varchar(20),"
               "pubCode int,"
               "finish text)");
    //创建assignpncp表格
    query.exec("create table if not exists assignpncp("
               "num int primary key,"
               "oril varchar(20),"
               "vari int,"
               "title varchar(40),"
               "content text,"
               "desc text,"
               "startTime varchar(20),"
               "endTime varchar(20),"
               "pncpNum int,"
               "transNum int,"
               "pncpDDL varchar(20),"
               "transDDL varchar(20),"
               "trial text,"
               "reward double,"
               "status int,"
               "id int,"
               "pncpName varchar(20),"
               "pncpCode int,"
               "cv text,"
               "goal text,"
               "confirm tinyint)");
    //创建assignTrans表格
    query.exec("create table if not exists assignTrans("
               "num int,"
               "oril varchar(20),"
               "vari int,"
               "title varchar(40),"
               "content text,"
               "desc text,"
               "startTime varchar(20),"
               "endTime varchar(20),"
               "pncpNum int,"
               "transNum int,"
               "pncpDDL varchar(20),"
               "transDDL varchar(20),"
               "trial text,"
               "reward double,"
               "status int,"
               "id int,"
               "transName varchar(20),"
               "transCode int,"
               "cv text,"
               "mission text,"
               "goal text,"
               "state int,"
               "feedback text, "
               "submit text)");
    //创建msgBox表格
    if (!query.exec("create table if not exists msgBox("
               "id int,"
               "sender int,"
               "theme text,"
               "msg text,"
               "user int)"))
    {
        qDebug() << "msg create not successful";
        qDebug() << q->lastError();
    }
}

/***********************************************************************************************************************
【函数名称】                                 loadData()
【函数功能】                                 从数据库中导出数据
【参数】                                    无
【返回值】                                   QSqlDatabase，db
【开发者及日期】                              门恺文2019.7.30
【更改记录】
***********************************************************************************************************************/

QSqlDatabase Database::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("system.db");
    if (!db.open())
    {//对于无法打开数据库的异常
        QMessageBox::critical(nullptr, "无法打开system.db", "无法连接数据库", QMessageBox::Cancel);
        qDebug() << "Database failed";
    }
    QSqlQuery query;
    //如果没有表则创建表
    creatConnection(&query);

    //从User中读取数据
    query.exec("Select * from User");
    while (query.next())
    {
        int userCode = query.value(0).toInt();
        QString username = query.value(1).toString();
        QString password = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString level = query.value(4).toString();
        QString name = query.value(5).toString();
        QString email = query.value(6).toString();
        QString id = query.value(7).toString();
        double balance = query.value(8).toDouble();
        int point = query.value(9).toInt();
        QString avatar = query.value(10).toString();
        User userItem(userCode, username, password, phone, level, name, email, id, balance, point, avatar);
        userList.push_back(userItem);

        //检测是否成功读取
        qDebug() << query.lastQuery();
        qDebug() << userCode;
        qDebug() << username;
        qDebug() << password;
        qDebug() << phone;
        qDebug() << level;
        qDebug() << name;
        qDebug() << email;
        qDebug() << id;
        qDebug() << balance;
        qDebug() << point;
        qDebug() << avatar;
    }

    //从Platform中读取数据
    query.exec("Select * from Platform");
    while (query.next())
    {
        int jobCode = query.value(0).toInt();
        QString phone = query.value(1).toString();
        QString email = query.value(2).toString();
        QString id = query.value(3).toString();
        QString cv = query.value(4).toString();
        QString name = query.value(5).toString();
        Platform platformItem(name, phone, email, id, cv, jobCode);
        platformList.push_back(platformItem);

        //检测
        qDebug() << query.lastQuery();
        qDebug() << name;
        qDebug() << phone;
        qDebug() << email;
        qDebug() << id;
        qDebug() << cv;
        qDebug() << jobCode;
    }

    //从assignment中读取数据
    query.exec("Select * from assignment");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString oril = query.value(1).toString();
        int vari = query.value(2).toInt();
        QString title = query.value(3).toString();
        QString content = query.value(4).toString();
        QString desc = query.value(5).toString();
        QString startTime = query.value(6).toString();
        QString endTime = query.value(7).toString();
        int pncpNum = query.value(8).toInt();
        int transNum = query.value(9).toInt();
        QString pncpDDL = query.value(10).toString();
        QString transDDL = query.value(11).toString();
        QString trial = query.value(12).toString();
        double reward = query.value(13).toDouble();
        Status status = (Status)query.value(14).toInt();
        QString goal = query.value(15).toString();
        //需要拆解为字符串并分别放入容器
        QVector<QString> goalLang;
        int len = goal.size();
        while (len != 0)
        {
            if (!goal.contains("。"))
            {
                goalLang.push_back(goal);
                break;
            }
            int N = goal.indexOf("。");
            goalLang.push_back(goal.left(N));
            len -= N + 1;
            goal = goal.right(len);
        }
        Translanguage trans(goalLang, oril, vari);
        Assignment assign(trans, title, content, desc, startTime, endTime, pncpNum, transNum, pncpDDL, transDDL, trial, reward, status, id);
        assignList.push_back(assign);

        //检测
        qDebug() << query.lastQuery();
        qDebug() << goal;
        qDebug() << oril;
        qDebug() << vari;
        qDebug() << title;
        qDebug() << content;
        qDebug() << desc;
        qDebug() << startTime;
        qDebug() << endTime;
        qDebug() << pncpNum;
        qDebug() << transNum;
        qDebug() << pncpDDL;
        qDebug() << transDDL;
        qDebug() << trial;
        qDebug() << reward;
        qDebug() << status;
        qDebug() << id;
    }

    //从assignPub中读取数据
    query.exec("Select * from assignPub");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString oril = query.value(1).toString();
        int vari = query.value(2).toInt();
        QString title = query.value(3).toString();
        QString content = query.value(4).toString();
        QString desc = query.value(5).toString();
        QString startTime = query.value(6).toString();
        QString endTime = query.value(7).toString();
        int pncpNum = query.value(8).toInt();
        int transNum = query.value(9).toInt();
        QString pncpDDL = query.value(10).toString();
        QString transDDL = query.value(11).toString();
        QString trial = query.value(12).toString();
        double reward = query.value(13).toDouble();
        Status status = (Status)query.value(14).toInt();
        QString goal = query.value(15).toString();
        QVector<QString> goalLang;
        int len = goal.size();
        while (len != 0)
        {
            if (!goal.contains("。"))
            {
                goalLang.push_back(goal);
                break;
            }
            int N = goal.indexOf("。");
            goalLang.push_back(goal.left(N));
            len -= N + 1;
            goal = goal.right(len);
        }
        QString username = query.value(16).toString();
        int pubCode = query.value(17).toInt();
        QString finish = query.value(18).toString();
        Translanguage trans(goalLang, oril, vari);
        AssignPublisher pub(trans, title, content, desc, startTime, endTime, pncpNum, transNum, pncpDDL, transDDL, trial, reward, status, id, username, pubCode, finish);
        pubList.push_back(pub);

        //检测
        qDebug() << query.lastQuery();
        qDebug() << goal;
        qDebug() << oril;
        qDebug() << vari;
        qDebug() << title;
        qDebug() << content;
        qDebug() << desc;
        qDebug() << startTime;
        qDebug() << endTime;
        qDebug() << pncpNum;
        qDebug() << transNum;
        qDebug() << pncpDDL;
        qDebug() << transDDL;
        qDebug() << trial;
        qDebug() << reward;
        qDebug() << status;
        qDebug() << id;
        qDebug() << username;
        qDebug() << pubCode;
        qDebug() << finish;
    }

    //从assignpncp中读取数据
    query.exec("Select * from assignpncp");
    while (query.next())
    {
        int num = query.value(0).toInt();
        QString oril = query.value(1).toString();
        int vari = query.value(2).toInt();
        QString title = query.value(3).toString();
        QString content = query.value(4).toString();
        QString desc = query.value(5).toString();
        QString startTime = query.value(6).toString();
        QString endTime = query.value(7).toString();
        int pncpNum = query.value(8).toInt();
        int transNum = query.value(9).toInt();
        QString pncpDDL = query.value(10).toString();
        QString transDDL = query.value(11).toString();
        QString trial = query.value(12).toString();
        double reward = query.value(13).toDouble();
        Status status = (Status)query.value(14).toInt();
        int id = query.value(15).toInt();
        QString pncpName = query.value(16).toString();
        int pncpCode = query.value(17).toInt();
        QString CV = query.value(18).toString();
        QString goal = query.value(19).toString();
        QVector<QString> goalLang;
        int len = goal.size();
        while (len != 0)
        {
            if (!goal.contains("。"))
            {
                goalLang.push_back(goal);
                break;
            }
            int N = goal.indexOf("。");
            goalLang.push_back(goal.left(N));
            len -= N + 1;
            goal = goal.right(len);
        }
        bool confirm = query.value(20).toBool();
        Translanguage trans(goalLang, oril, vari);
        AssignPrincipal pncp(trans, title, content, desc, startTime, endTime, pncpNum, transNum, pncpDDL, transDDL, trial, reward, status, id, pncpName, pncpCode, CV, num, confirm);
        pncpList.push_back(pncp);

        //检测
        qDebug() << query.lastQuery();
        qDebug() << goal;
        qDebug() << oril;
        qDebug() << vari;
        qDebug() << title;
        qDebug() << content;
        qDebug() << desc;
        qDebug() << startTime;
        qDebug() << endTime;
        qDebug() << pncpNum;
        qDebug() << transNum;
        qDebug() << pncpDDL;
        qDebug() << transDDL;
        qDebug() << trial;
        qDebug() << reward;
        qDebug() << status;
        qDebug() << id;
        qDebug() << pncpName;
        qDebug() << pncpCode;
        qDebug() << CV;
        qDebug() << num;
        qDebug() << confirm;
    }

    //从assignTrans中读取数据
    query.exec("Select * from assignTrans");
    while (query.next())
    {
        int num = query.value(0).toInt();
        QString oril = query.value(1).toString();
        int vari = query.value(2).toInt();
        QString title = query.value(3).toString();
        QString content = query.value(4).toString();
        QString desc = query.value(5).toString();
        QString startTime = query.value(6).toString();
        QString endTime = query.value(7).toString();
        int pncpNum = query.value(8).toInt();
        int transNum = query.value(9).toInt();
        QString pncpDDL = query.value(10).toString();
        QString transDDL = query.value(11).toString();
        QString trial = query.value(12).toString();
        double reward = query.value(13).toDouble();
        Status status = (Status)query.value(14).toInt();
        int id = query.value(15).toInt();
        QString transName = query.value(16).toString();
        int transCode = query.value(17).toInt();
        QString CV = query.value(18).toString();
        QString mission = query.value(19).toString();
        QString goal = query.value(20).toString();
        QVector<QString> goalLang;
        int len = goal.size();
        while (len != 0)
        {
            if (!goal.contains("。"))
            {
                goalLang.push_back(goal);
                break;
            }
            int N = goal.indexOf("。");
            goalLang.push_back(goal.left(N));
            len -= N + 1;
            goal = goal.right(len);
        }
        State state = (State)query.value(21).toInt();
        QString feedback = query.value(22).toString();
        QString submit = query.value(23).toString();
        Translanguage trans(goalLang, oril, vari);
        AssignTranslator translator(trans, title, content, desc, startTime, endTime, pncpNum, transNum, pncpDDL, transDDL, trial, reward, status, id, transName, transCode, CV, mission, num, state, feedback, submit);
        transList.push_back(translator);

        //检测
        qDebug() << query.lastQuery();
        qDebug() << goal;
        qDebug() << oril;
        qDebug() << vari;
        qDebug() << title;
        qDebug() << content;
        qDebug() << desc;
        qDebug() << startTime;
        qDebug() << endTime;
        qDebug() << pncpNum;
        qDebug() << transNum;
        qDebug() << pncpDDL;
        qDebug() << transDDL;
        qDebug() << trial;
        qDebug() << reward;
        qDebug() << status;
        qDebug() << id;
        qDebug() << transName;
        qDebug() << transCode;
        qDebug() << CV;
        qDebug() << mission;
        qDebug() << num;
        qDebug() << state;
        qDebug() << feedback;
    }

    //从msgBox中读取数据
    query.exec("Select * from msgBox");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int sender = query.value(1).toInt();
        QString theme = query.value(2).toString();
        QString msg = query.value(3).toString();
        int user = query.value(4).toInt();
        MsgBox msgbox(user, sender, theme, msg, id);
        msgList.push_back(msgbox);

        //检测
        qDebug() << user;
        qDebug() << sender;
        qDebug() << theme;
        qDebug() << msg;
        qDebug() << id;
    }

    return db;
}

/***********************************************************************************************************************
【函数名称】                                 saveData()
【函数功能】                                 向数据库存入数据
【参数】                                    QSqlDatabase db
【返回值】                                   bool
【开发者及日期】                              门恺文2019.7.30
【更改记录】
***********************************************************************************************************************/

bool Database::saveData(QSqlDatabase db)
{
    QSqlQuery q(db);
    //先清理数据库，以防干扰
    cleanData(&q);

    //向User表插入
    q.exec("Select * from User");
    for (QList<User>::iterator i = userList.begin(); i < userList.end(); i++)
    {
        q.prepare("insert into User values (?,?,?,?,?,?,?,?,?,?,?)");
        q.addBindValue(i->getICode());
        q.addBindValue(i->getUserName());
        q.addBindValue(i->getPassword());
        q.addBindValue(i->getMobilePhone());
        q.addBindValue(i->getSLanguageLevel());
        q.addBindValue(i->getName());
        q.addBindValue(i->getEmail());
        q.addBindValue(i->getId());
        q.addBindValue(i->getBalance());
        q.addBindValue(i->getPoint());
        q.addBindValue(i->getSAvatar());

        //检测是否成功
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
        db.commit();
    }

    //向Platform表插入
    q.exec("Select * from Platform");
    for (QList<Platform>::iterator i = platformList.begin(); i < platformList.end(); i++)
    {
        q.prepare("insert into Platform values (?,?,?,?,?,?)");
        q.addBindValue(i->getJobNum());
        q.addBindValue(i->getMobilePhone());
        q.addBindValue(i->getEmail());
        q.addBindValue(i->getId());
        q.addBindValue(i->getCV());
        q.addBindValue(i->getName());

        //检测是否成功
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"1success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
    }

    //向assignment表插入
    q.exec("Select * from assignment");
    for (QList<Assignment>::iterator i = assignList.begin(); i < assignList.end(); i++)
    {
        q.prepare("insert into assignment values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        Translanguage trans = i->getTrans();
        QVector<QString> goalLang = trans.getGoal();
        QString goal;
        for (int j = 0; j < goalLang.size(); j++)
        {
            goal += goalLang[j] + "。";
        }
        QString ori = trans.getOri();
        int vari = trans.getVar();
        q.addBindValue(i->getAssignId());
        q.addBindValue(ori);
        q.addBindValue(vari);
        q.addBindValue(i->getSTitle());
        q.addBindValue(i->getContent());
        q.addBindValue(i->getDesc());
        q.addBindValue(i->getStartTime());
        q.addBindValue(i->getEndTime());
        q.addBindValue(i->getPncpNum());
        q.addBindValue(i->getTransNum());
        q.addBindValue(i->getPncpDDL());
        q.addBindValue(i->getTransDDL());
        q.addBindValue(i->getTrial());
        q.addBindValue(i->getReward());
        q.addBindValue(i->getStatus());
        q.addBindValue(goal);

        //检测
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"2success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
    }

    //向assignPub表插入
    q.exec("Select * from assignPub");
    for (QList<AssignPublisher>::iterator i = pubList.begin(); i < pubList.end(); i++)
    {
        q.prepare("insert into assignPub values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        Translanguage trans = i->getTrans();
        QVector<QString> goalLang = trans.getGoal();
        QString goal;
        for (int j = 0; j < goalLang.size(); j++)
        {
            goal += goalLang[j] + "。";
        }
        QString ori = trans.getOri();
        int vari = trans.getVar();
        q.addBindValue(i->getAssignId());
        q.addBindValue(ori);
        q.addBindValue(vari);
        q.addBindValue(i->getSTitle());
        q.addBindValue(i->getContent());
        q.addBindValue(i->getDesc());
        q.addBindValue(i->getStartTime());
        q.addBindValue(i->getEndTime());
        q.addBindValue(i->getPncpNum());
        q.addBindValue(i->getTransNum());
        q.addBindValue(i->getPncpDDL());
        q.addBindValue(i->getTransDDL());
        q.addBindValue(i->getTrial());
        q.addBindValue(i->getReward());
        q.addBindValue(i->getStatus());
        q.addBindValue(goal);
        q.addBindValue(i->sUserName());
        q.addBindValue(i->getIPublisherCode());
        q.addBindValue(i->getSFinish());

        //检测
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"3success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
    }

    //向assignpncp表插入
    q.exec("Select * from assignpncp");
    for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
    {
        q.prepare("insert into assignpncp values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        Translanguage trans = i->getTrans();
        QVector<QString> goalLang = trans.getGoal();
        QString goal;
        for (int j = 0; j < goalLang.size(); j++)
        {
            goal += goalLang[j] + "。";
        }
        QString ori = trans.getOri();
        int vari = trans.getVar();
        q.addBindValue(i->getINum());
        q.addBindValue(ori);
        q.addBindValue(vari);
        q.addBindValue(i->getSTitle());
        q.addBindValue(i->getContent());
        q.addBindValue(i->getDesc());
        q.addBindValue(i->getStartTime());
        q.addBindValue(i->getEndTime());
        q.addBindValue(i->getPncpNum());
        q.addBindValue(i->getTransNum());
        q.addBindValue(i->getPncpDDL());
        q.addBindValue(i->getTransDDL());
        q.addBindValue(i->getTrial());
        q.addBindValue(i->getReward());
        q.addBindValue(i->getStatus());
        q.addBindValue(i->getAssignId());
        q.addBindValue(i->getSPncpName());
        q.addBindValue(i->getIPncpCode());
        q.addBindValue(i->getSCV());
        q.addBindValue(goal);
        q.addBindValue(i->getBIsConfirmed());

        //检测
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"4success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
    }

    //向assignTrans表中插入
    q.exec("Select * from assignTrans");
    for (QList<AssignTranslator>::iterator i = transList.begin(); i < transList.end(); i++)
    {
        q.prepare("insert into assignTrans values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        Translanguage trans = i->getTrans();
        QVector<QString> goalLang = trans.getGoal();
        QString goal;
        for (int j = 0; j < goalLang.size(); j++)
        {
            goal += goalLang[j] + "。";
        }
        QString ori = trans.getOri();
        int vari = trans.getVar();
        q.addBindValue(i->iTransId());
        q.addBindValue(ori);
        q.addBindValue(vari);
        q.addBindValue(i->getSTitle());
        q.addBindValue(i->getContent());
        q.addBindValue(i->getDesc());
        q.addBindValue(i->getStartTime());
        q.addBindValue(i->getEndTime());
        q.addBindValue(i->getPncpNum());
        q.addBindValue(i->getTransNum());
        q.addBindValue(i->getPncpDDL());
        q.addBindValue(i->getTransDDL());
        q.addBindValue(i->getTrial());
        q.addBindValue(i->getReward());
        q.addBindValue(i->getStatus());
        q.addBindValue(i->getAssignId());
        q.addBindValue(i->getSTransName());
        q.addBindValue(i->getITransCode());
        q.addBindValue(i->getSCV());
        q.addBindValue(i->getSMission());
        q.addBindValue(goal);
        q.addBindValue(i->getETransState());
        q.addBindValue(i->getSFeedback());
        q.addBindValue(i->getSSubmit());

        //检测
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"5success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
    }

    //向msgBox表中插入
    q.exec("Select * from msgBox");
    for (QList<MsgBox>::iterator i = msgList.begin(); i < msgList.end(); i++)
    {
        q.prepare("insert into msgBox values (?,?,?,?,?)");
        q.addBindValue(i->getIMsgId());
        q.addBindValue(i->iSenderCode());
        q.addBindValue(i->sTheme());
        q.addBindValue(i->sMessage());
        q.addBindValue(i->iUserCode());

        //检测
        qDebug() << q.executedQuery();
        if(q.exec())
        {
            qDebug()<<"6success";
            qDebug() << q.lastQuery();
        }
        else
        {
            qDebug() << q.lastError();
            QMessageBox::warning(nullptr, "warning", "false", QMessageBox::Ok);
        }
    }

    return 0;
}


/***********************************************************************************************************************
【函数名称】                                 cleanData()
【函数功能】                                 向数据库导入之前先清理数据库
【参数】                                    QSqlQuery *q
【返回值】                                   bool
【开发者及日期】                              门恺文2019.7.30
【更改记录】
***********************************************************************************************************************/

bool Database::cleanData(QSqlQuery *q)
{
    q->exec("delete from User");
    q->exec("delete from Platform");
    q->exec("delete from assignment");
    q->exec("delete from assignPub");
    q->exec("delete from assignpncp");
    q->exec("delete from assignTrans");
    q->exec("delete from msgBox");
    return 0;
}

