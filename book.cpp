/**********************************************************************************************************************
【文件名】                                  book.cpp
【功能模块和目的】                            Book类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
**********************************************************************************************************************/

#include "book.h"
#include "ui_book.h"
#include "newmissiondlg.h"
#include "assigndlg.h"
#include <QMetaEnum>
#include "personalmainwindow.h"
#include "infomaintaindlg.h"
#include "mainwindow.h"
#include "employmentdlg.h"
#include "depositdlg.h"

/***********************************************************************************************************************
【函数名称】                                 Book()
【函数功能】                                 类Book的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.24
【更改记录】
***********************************************************************************************************************/

Book::Book(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Book)
{
    ui->setupUi(this);

    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterAssignment(const QModelIndex&)));
}

/***********************************************************************************************************************
【函数名称】                                 ~Book()
【函数功能】                                 类Book的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

Book::~Book()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_findBtn_clicked()
【函数功能】                                 用户查看任务详情前点击按钮的槽函数，显示任务列表
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_findBtn_clicked()
{
    int row = 0;

    //设置列标题
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("序号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("标题")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("发布者")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("原文")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("译文")));
    model->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("任务状态")));
    model->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("任务酬金")));

    QList<AssignPublisher>::iterator i;

    switch (ui->stateBox->currentIndex())
    {
    case 0:
    {
        for (i = pubList.begin(); i < pubList.end(); i++)
        {
            //只可查看自己未参与的任务，自己参与的任务可在个人中心查看
            int assign = i->getAssignId();
            //以发布者角色参与的情况
            if (i->getIPublisherCode() == userCode)
            {
                continue;
            }
            bool isCommitted = false;
            //以负责人角色参与的情况
            for (QList<AssignPrincipal>::iterator j = pncpList.begin(); j < pncpList.end(); j++)
            {
                if ((j->getBIsConfirmed()) && (j->getIPncpCode() == userCode) && (j->getAssignId() == assign))
                {
                    isCommitted = true;
                }
            }
            //以译者角色参与的情况
            for (QList<AssignTranslator>::iterator j = transList.begin(); j < transList.end(); j++)
            {
                if ((j->getITransCode() == userCode) && (j->getETransState() != APPLYING)
                        && (j->getAssignId() == assign))
                {
                    isCommitted = true;
                }
            }
            if (isCommitted)
            {
                continue;
            }
            //将任务状态反映为文字
            QString status;
            switch (i->getStatus())
            {
            case RECUITING_PRICIPAL:
            {
                status = tr("正在招募负责人");
                break;
            }
            case RECUITING_TRANSLATOR:
            {
                status = tr("正在招募译者");
                break;
            }
            case ON_TRANSLATING:
            {
                status = tr("正在翻译");
                break;
            }
            case TRANSLATION_FINISHED:
            {
                status = tr("翻译完成");
                break;
            }
            case ON_SHELF:
            {
                status= tr("已上架");
                break;
            }
            }
            //显示翻译语言
            QString goal;
            QVector<QString> goalLang = i->getTrans().Translanguage::getGoal();
            int vari = i->getTrans().Translanguage::getVar();
            if (vari <= 2)
            {
                for (int i = 0; i < vari; i++)
                {
                    //不同语言之间以逗号隔开
                    goal += goalLang[i] + tr(",");
                }
            }
            else {//多于两种语言则只显示两种
                goal = goalLang[0] + tr(",") + goalLang[1] + tr("...");
            }
            //填入表格
            model->setItem(row, 0, new QStandardItem(QString::number(i->getAssignId())));
            model->setItem(row, 1, new QStandardItem(i->getSTitle()));
            model->setItem(row, 2, new QStandardItem(i->sUserName()));
            model->setItem(row, 3, new QStandardItem(i->getTrans().Translanguage::getOri()));
            model->setItem(row, 4, new QStandardItem(goal));
            model->setItem(row, 5, new QStandardItem(status));
            model->setItem(row, 6, new QStandardItem(QString::number(i->getReward(), 'f', 2)));
            row++;
        }
        break;
    }
    case 1:
    {
        //只显示正在招募负责人的任务
        for (i = pubList.begin(); i < pubList.end(); i++)
        {
            if (i->getIPublisherCode() == userCode)
            {
                continue;
            }
            bool isCommitted = false;
            for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
            {
                if (i->getBIsConfirmed())
                {
                    isCommitted = true;
                }
            }
            for (QList<AssignTranslator>::iterator j = transList.begin(); j < transList.end(); j++)
            {
                if ((j->getITransCode() == userCode) && (j->getETransState() != APPLYING)
                        && (j->getAssignId() == assignId))
                {
                    isCommitted = true;
                }
            }
            if (isCommitted)
            {
                continue;
            }
            if (i->getStatus() == RECUITING_PRICIPAL)
            {
                QString goal;
                QVector<QString> goalLang = i->getTrans().Translanguage::getGoal();
                int vari = i->getTrans().Translanguage::getVar();
                if (vari <= 2)
                {
                    for (int i = 0; i < vari; i++)
                    {
                        goal += goalLang[i];
                    }
                }
                else {//多于两种语言则只显示两种
                    goal = goalLang[0] + tr(",") + goalLang[1] + tr("...");
                }

                model->setItem(row, 0, new QStandardItem(i->getAssignId()));
                model->setItem(row, 1, new QStandardItem(i->getSTitle()));
                model->setItem(row, 2, new QStandardItem(i->sUserName()));
                model->setItem(row, 3, new QStandardItem(i->getTrans().Translanguage::getOri()));
                model->setItem(row, 4, new QStandardItem(goal));
                model->setItem(row, 5, new QStandardItem(tr("正在招募负责人")));
                model->setItem(row, 6, new QStandardItem(QString::number(i->getReward(), 'f', 2)));
                row++;
            }
        }
        break;
    }
    case 2:
    {
        //只显示正在招募译者的任务
        for (i = pubList.begin(); i < pubList.end(); i++)
        {
            if (i->getIPublisherCode() == userCode)
            {
                continue;
            }
            bool isCommitted = false;
            for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
            {
                if (i->getBIsConfirmed())
                {
                    isCommitted = true;
                }
            }
            for (QList<AssignTranslator>::iterator j = transList.begin(); j < transList.end(); j++)
            {
                if ((j->getITransCode() == userCode) && (j->getETransState() != APPLYING)
                        && (j->getAssignId() == assignId))
                {
                    isCommitted = true;
                }
            }
            if (isCommitted)
            {
                continue;
            }
            if (i->getStatus() == RECUITING_TRANSLATOR)
            {
                QString goal;
                QVector<QString> goalLang = i->getTrans().Translanguage::getGoal();
                int vari = i->getTrans().Translanguage::getVar();
                if (vari <= 2)
                {
                    for (int i = 0; i < vari; i++)
                    {
                        goal += goalLang[i];
                    }
                }
                else {//多于两种语言则只显示两种
                    goal = goalLang[0] + tr(",") + goalLang[1] + tr("...");
                }
                model->setItem(row, 0, new QStandardItem(i->getAssignId()));
                model->setItem(row, 1, new QStandardItem(i->getSTitle()));
                model->setItem(row, 2, new QStandardItem(i->sUserName()));
                model->setItem(row, 3, new QStandardItem(i->getTrans().Translanguage::getOri()));
                model->setItem(row, 4, new QStandardItem(goal));
                model->setItem(row, 5, new QStandardItem(tr("正在招募译者")));
                model->setItem(row, 6, new QStandardItem(QString::number(i->getReward(), 'f', 2)));
                row++;
            }
        }
        break;
    }
    case 3:
    {
        //只显示正在翻译的任务
        for (i = pubList.begin(); i < pubList.end(); i++)
        {
            if (i->getIPublisherCode() == userCode)
            {
                continue;
            }
            bool isCommitted = false;
            for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
            {
                if (i->getBIsConfirmed())
                {
                    isCommitted = true;
                }
            }
            for (QList<AssignTranslator>::iterator j = transList.begin(); j < transList.end(); j++)
            {
                if ((j->getITransCode() == userCode) && (j->getETransState() != APPLYING)
                        && (j->getAssignId() == assignId))
                {
                    isCommitted = true;
                }
            }
            if (isCommitted)
            {
                continue;
            }
            if (i->getStatus() == ON_TRANSLATING)
            {
                QString goal;
                QVector<QString> goalLang = i->getTrans().Translanguage::getGoal();
                int vari = i->getTrans().Translanguage::getVar();
                if (vari <= 2)
                {
                    for (int i = 0; i < vari; i++)
                    {
                        goal += goalLang[i];
                    }
                }
                else {//多于两种语言则只显示两种
                    goal = goalLang[0] + tr(",") + goalLang[1] + tr("...");
                }
                model->setItem(row, 0, new QStandardItem(i->getAssignId()));
                model->setItem(row, 1, new QStandardItem(i->getSTitle()));
                model->setItem(row, 2, new QStandardItem(i->sUserName()));
                model->setItem(row, 3, new QStandardItem(i->getTrans().Translanguage::getOri()));
                model->setItem(row, 4, new QStandardItem(goal));
                model->setItem(row, 5, new QStandardItem(tr("正在翻译")));
                model->setItem(row, 6, new QStandardItem(QString::number(i->getReward(), 'f', 2)));
                row++;
            }
        }
        break;
    }
    case 4:
    {
        //只显示翻译完成的任务
        for (i = pubList.begin(); i < pubList.end(); i++)
        {
            if (i->getIPublisherCode() == userCode)
            {
                continue;
            }
            bool isCommitted = false;
            for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
            {
                if (i->getBIsConfirmed())
                {
                    isCommitted = true;
                }
            }
            for (QList<AssignTranslator>::iterator j = transList.begin(); j < transList.end(); j++)
            {
                if ((j->getITransCode() == userCode) && (j->getETransState() != APPLYING)
                        && (j->getAssignId() == assignId))
                {
                    isCommitted = true;
                }
            }
            if (isCommitted)
            {
                continue;
            }
            if (i->getStatus() == TRANSLATION_FINISHED)
            {
                QString goal;
                QVector<QString> goalLang = i->getTrans().Translanguage::getGoal();
                int vari = i->getTrans().Translanguage::getVar();
                if (vari <= 2)
                {
                    for (int i = 0; i < vari; i++)
                    {
                        goal += goalLang[i];
                    }
                }
                else {//多于两种语言则只显示两种
                    goal = goalLang[0] + tr(",") + goalLang[1] + tr("...");
                }

                model->setItem(row, 0, new QStandardItem(i->getAssignId()));
                model->setItem(row, 1, new QStandardItem(i->getSTitle()));
                model->setItem(row, 2, new QStandardItem(i->sUserName()));
                model->setItem(row, 3, new QStandardItem(i->getTrans().Translanguage::getOri()));
                model->setItem(row, 4, new QStandardItem(goal));
                model->setItem(row, 5, new QStandardItem(tr("翻译完成")));
                model->setItem(row, 6, new QStandardItem(QString::number(i->getReward(), 'f', 2)));
                row++;
            }
        }
        break;
    }
    case 5:
    {
        //只显示已上架的任务
        for (i = pubList.begin(); i < pubList.end(); i++)
        {
            if (i->getIPublisherCode() == userCode)
            {
                continue;
            }
            bool isCommitted = false;
            for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
            {
                if (i->getBIsConfirmed())
                {
                    isCommitted = true;
                }
            }
            for (QList<AssignTranslator>::iterator j = transList.begin(); j < transList.end(); j++)
            {
                if ((j->getITransCode() == userCode) && (j->getETransState() != APPLYING)
                        && (j->getAssignId() == assignId))
                {
                    isCommitted = true;
                }
            }
            if (isCommitted)
            {
                continue;
            }
            if (i->getStatus() == ON_SHELF)
            {
                QString goal;
                QVector<QString> goalLang = i->getTrans().Translanguage::getGoal();
                int vari = i->getTrans().Translanguage::getVar();
                if (vari <= 2)
                {
                    for (int i = 0; i < vari; i++)
                    {
                        goal += goalLang[i];
                        if (i != vari - 1)
                        {
                            //两种时中间用逗号分隔
                            goal += tr(",");
                        }
                    }
                }
                else {
                    //多于两种语言则只显示两种
                    goal = goalLang[0] + tr(",") + goalLang[1] + tr("...");
                }

                model->setItem(row, 0, new QStandardItem(i->getAssignId()));
                model->setItem(row, 1, new QStandardItem(i->getSTitle()));
                model->setItem(row, 2, new QStandardItem(i->sUserName()));
                model->setItem(row, 3, new QStandardItem(i->getTrans().Translanguage::getOri()));
                model->setItem(row, 4, new QStandardItem(goal));
                model->setItem(row, 5, new QStandardItem(tr("已上架")));
                model->setItem(row, 6, new QStandardItem(QString::number(i->getReward(), 'f', 2)));
                row++;
            }
        }
        break;
    }
    }

    //将表格显示在tableView上
    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

/***********************************************************************************************************************
【函数名称】                                 on_publishBtn_clicked()
【函数功能】                                 用户发布新任务点击按钮的槽函数，可使界面跳转至任务发布界面
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_publishBtn_clicked()
{
    if (userCode == -1)
    {
        //用户只有在登录后才可发布任务
        QMessageBox::information(this, tr("提示"), tr("您需先登录才可发布任务"), QMessageBox::Yes);
        return;
    }
    newMissionDlg dlg;
    dlg.setUserCode(userCode);
    dlg.setUserName(username);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 enterAssignment()
【函数功能】                                 用户进入任务详情的槽函数，可使界面跳转至任务详情
【参数】                                    const QModelIndex &index
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::enterAssignment(const QModelIndex &index)
{
    if (userCode == -1)
    {
        //登录后才可进入任务
        QMessageBox::information(this, tr("提示"), tr("您需先登录才可进入任务详情"), QMessageBox::Yes);
        return;
    }
    int row = index.row();
    QAbstractItemModel *assign = const_cast<QAbstractItemModel *>(index.model());
    //从表格中获取对应的任务编号
    int assignId = assign->data(assign->index(row, 0, QModelIndex())).toInt();
    title = pubList[assignId].getSTitle();
    //进入任务界面
    assignDlg dlg;
    dlg.setPublisherCode(pubList[assignId].getIPublisherCode());
    dlg.setTitle(title);
    dlg.setAssignId(assignId);
    dlg.setUsername(username);
    dlg.setDesc(pubList[assignId].getDesc());
    dlg.setUserCode(userCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::setUserCode(int value)
{
    userCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId()
【函数功能】                                 成员assignId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::setAssignId(int value)
{
    assignId = value;
}

/***********************************************************************************************************************
【函数名称】                                 setUsername()
【函数功能】                                 成员Username的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     Username, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::setUsername(const QString &value)//shan
{
    username = value;
}

/***********************************************************************************************************************
【函数名称】                                 on_actionInfo_Maintaince_triggered()
【函数功能】                                 用户进入个人中心的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_actionInfo_Maintaince_triggered()
{
    if (userCode == -1)
    {
        //用户需先登录才可进入个人中心
        QMessageBox::information(this, tr("提示"), tr("您尚未登录，无法进入个人中心"), QMessageBox::Ok);
        return;
    }
    PersonalMainWindow* personal = new PersonalMainWindow;
    personal->setUserCode(userCode);
    personal->show();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEnter_triggered()
【函数功能】                                 用户进入首页的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_actionEnter_triggered()
{
    //进入首页
    MainWindow* mainwindow = new MainWindow;
    mainwindow->setUserCode(userCode);
    mainwindow->show();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEmployment_triggered()
【函数功能】                                 用户进入应聘的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_actionEmployment_triggered()
{
    //进入应聘界面
    Employmentdlg* employee = new Employmentdlg(this);
    employee->exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionInfo_maintaince_triggered()
【函数功能】                                 用户进入信息维护的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_actionInfo_maintaince_triggered()
{

    if (userCode == -1)
    {
        //用户需先登录才可进行信息维护
        QMessageBox::information(this, tr("提示"), tr("您尚未登录，无法进行信息维护"), QMessageBox::Ok);
        return;
    }
    InfoMaintaindlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionDeposit_triggered()
【函数功能】                                 用户进入充值的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Book::on_actionDeposit_triggered()
{

    if (userCode == -1)
    {
        //用户需先登录才可充值
        QMessageBox::information(this, tr("提示"), tr("您尚未登录，无法进行充值"), QMessageBox::Ok);
        return;
    }
    Depositdlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
}
