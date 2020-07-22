/************************************************************************************************************************
【文件名】                                  book.h
【模块功能和目的】                           Book类声明，对应图书主页
【开发者及日期】                             门恺文 2019.7.23
【更改记录】
************************************************************************************************************************/

#ifndef BOOK_H
#define BOOK_H

#include <QMainWindow>
#include <QTextDocument>
#include <QFormLayout>
#include <QList>
#include <QTableWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include "database.h"

namespace Ui {
class Book;
}

/************************************************************************************************************************
【类名】                                   Book
【功能】                                   图书主页界面类，封装了在该界面上可进行的所有操作，如发布新任务、查询未参与的任务，进入其他页面等
【接口说明】                                包含一个构造函数和一个析构函数
                                          每一个数据成员都有一对Getter和Setter函数，以提高代码可移植性，并保证数据安全
                                          八个私有槽函数处理信号
【开发者及日期】                             门恺文2019.7.23
【更改记录】
************************************************************************************************************************/

class Book : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数和析构函数
    explicit Book(QWidget *parent = nullptr);
    ~Book();

    //用户名获取和设置函数
    QString getUsername() const;
    void setUsername(const QString &value);

    //任务编号获取和设置函数
    int getAssignId() const;
    void setAssignId(int value);

    //用户编号获取和设置函数
    int getUserCode() const;
    void setUserCode(int value);

private slots:
    //查询任务槽函数
    void on_findBtn_clicked();

    //发布新任务槽函数
    void on_publishBtn_clicked();

    //进入任务槽函数
    void enterAssignment(const QModelIndex &index);

    //进入个人主页槽函数
    void on_actionInfo_Maintaince_triggered();

    //进入首页槽函数
    void on_actionEnter_triggered();

    //应聘槽函数
    void on_actionEmployment_triggered();

    //信息维护槽函数
    void on_actionInfo_maintaince_triggered();

    //充值槽函数
    void on_actionDeposit_triggered();

private:
    Ui::Book *ui;
    int userCode;
    QList<Assignment>& assignList = Database::assignList;
    QList<AssignPublisher>& pubList = Database::pubList;
    QList<AssignPrincipal>& pncpList = Database::pncpList;
    QList<AssignTranslator>& transList = Database::transList;
    QList<User>& userInfoList = Database::userList;
    QString username;
    //进入的任务的标题和任务编号
    QString title;
    int assignId;
};

#endif // BOOK_H
