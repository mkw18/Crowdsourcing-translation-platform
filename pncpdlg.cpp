/**********************************************************************************************************************
【文件名】                                  pncpdlg.cpp
【功能模块和目的】                            PncpDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.27
【更改记录】
**********************************************************************************************************************/

#include "pncpdlg.h"
#include "ui_pncpdlg.h"
#include "auditdlg.h"
#include <QTableView>
#include <QStandardItemModel>
#include "pncpassigndlg.h"
#include "feedbackdlg.h"
#include "transddldlg.h"

/***********************************************************************************************************************
【函数名称】                                 PncpDlg()
【函数功能】                                 类PncpDlg的构造函数
【参数】                                     QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.27
【更改记录】
***********************************************************************************************************************/

PncpDlg::PncpDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PncpDlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~PncpDlg()
【函数功能】                                 类PncpDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

PncpDlg::~PncpDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 setPncpId()
【函数功能】                                 成员pncpId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::setPncpId(int value)
{
    pncpId = value;
}

/***********************************************************************************************************************
【函数名称】                                 setPncpCode()
【函数功能】                                 成员pncpCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::setPncpCode(int value)
{
    pncpCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId()
【函数功能】                                 成员assignId的设置函数，改变页面内容
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::setAssignId(int value)
{
    assignId = value;

    //获取任务编号后初始化
    ui->labFront->setText(tr("任务") + QString::number(assignId) + tr("：") + pubList[assignId].getSTitle());
    ui->plainTextEditContent->setPlainText(assignList[assignId].getDesc());
    //过了任务截止日期，负责人将不可设置译者报名截止日期，不可分配或提交任务
    if (QDate::currentDate().toString("yyyy-MM-dd") > pubList[assignId].getEndTime())
    {
        ui->transDDLBtn->setEnabled(false);
        ui->submitBtn->setEnabled(false);
        ui->assignBtn->setEnabled(false);
    }
    //任务状态为已上架时可领取酬金
    if (pubList[assignId].getStatus() != ON_SHELF)
    {
        ui->getBtn->setEnabled(false);
    }
}

/***********************************************************************************************************************
【函数名称】                                 inEnroll()
【函数功能】                                 较庞大而重复性高的函数，单独封装，提高代码可重用性，同时简化代码。置于查看译者报名槽函数内
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::inEnroll()
{
    //显示译者报名信息表格
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("译者用户编号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("真实姓名")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("常用邮箱")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("手机号码")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("简历")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("翻译者任务编号")));

    QList<AssignTranslator>::iterator i;
    int row = 0;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if (i->getAssignId() == assignId)
        {
            int transCode = i->getITransCode();
            int transId = i->iTransId();
            model->setItem(row, 0, new QStandardItem(QString::number(transCode)));
            model->setItem(row, 1, new QStandardItem(userInfoList[transCode].getName()));
            model->setItem(row, 2, new QStandardItem(userInfoList[transCode].getEmail()));
            model->setItem(row, 3, new QStandardItem(userInfoList[transCode].getMobilePhone()));
            model->setItem(row, 4, new QStandardItem(tr("查看")));
            model->setItem(row, 5, new QStandardItem(QString::number(transId)));
            row++;
        }
    }

    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

/***********************************************************************************************************************
【函数名称】                                 inAssign()
【函数功能】                                 较庞大而重复性高的函数，单独封装，提高代码可重用性，同时简化代码。置于分配子任务槽函数内
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::inAssign()
{
    //显示分配子任务表格
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("译者用户编号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("真实姓名")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("翻译者任务编号")));

    QList<AssignTranslator>::iterator i;
    int row = 0;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == assignId) && (i->getETransState() == CONFIRMED))
        {
            int transCode = i->getITransCode();
            int transId = i->iTransId();
            model->setItem(row, 0, new QStandardItem(QString::number(transCode)));
            model->setItem(row, 1, new QStandardItem(userInfoList[transCode].getName()));
            model->setItem(row, 2, new QStandardItem(QString::number(transId)));
            row++;
        }
    }

    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

/***********************************************************************************************************************
【函数名称】                                 inTrans()
【函数功能】                                 较庞大而重复性高的函数，单独封装，提高代码可重用性，同时简化代码。置于查看译者提交任务槽函数内
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::inTrans()
{
    //显示翻译者提交任务表格
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("译者用户编号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("真实姓名")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("翻译者任务编号")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("翻译者提交任务")));

    QList<AssignTranslator>::iterator i;
    int row = 0;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == assignId) && (i->getETransState() == SUBMITED))
        {
            int transCode = i->getITransCode();
            int transId = i->iTransId();
            model->setItem(row, 0, new QStandardItem(QString::number(transCode)));
            model->setItem(row, 1, new QStandardItem(userInfoList[transCode].getName()));
            model->setItem(row, 2, new QStandardItem(QString::number(transId)));
            model->setItem(row, 3, new QStandardItem(transList[transId].getSSubmit()));
            row++;
        }
    }

    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}

/***********************************************************************************************************************
【函数名称】                                 enterEnroll()
【函数功能】                                 进入查看译者报名情况页面
【参数】                                     QModelIndex &index, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::enterEnroll(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *enroll = const_cast<QAbstractItemModel *>(index.model());
    //获取译者用户编号
    int transCode = enroll->data(enroll->index(row, 0 ,QModelIndex())).toInt();
    //获取译者任务编号
    int transId = enroll->data(enroll->index(row, 5, QModelIndex())).toInt();
    AuditDlg dlg;
    dlg.setApplyCode(transCode);
    dlg.setApplyId(transId);
    dlg.setAssignId(assignId);
    dlg.setUserCode(pncpCode);
    dlg.setFront(tr("译者") + QString::number(transId));
    dlg.setType(1);//代表译者
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 enterAssign()
【函数功能】                                 进入分配译者子任务页面
【参数】                                     QModelIndex &index, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::enterAssign(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *assign = const_cast<QAbstractItemModel *>(index.model());
    int transCode = assign->data(assign->index(row, 0 ,QModelIndex())).toInt();
    int transId = assign->data(assign->index(row, 2, QModelIndex())).toInt();
    //设标头
    QString front = tr("译者")+QString::number(transId)+userInfoList[transCode].getName();
    PncpAssignDlg dlg;
    dlg.setTransId(transId);
    dlg.setTransCode(transCode);
    dlg.setAssignId(assignId);
    dlg.setPncpCode(pncpCode);
    dlg.setFront(front);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 enterTrans()
【函数功能】                                 进入查看译者提交任务页面
【参数】                                     QModelIndex &index, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::enterTrans(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *trans = const_cast<QAbstractItemModel *>(index.model());
    int transCode = trans->data(trans->index(row, 0 ,QModelIndex())).toInt();
    int transId = trans->data(trans->index(row, 2, QModelIndex())).toInt();
    QString front = tr("译者")+QString::number(transId)+userInfoList[transCode].getName()+tr("提交的任务");
    FeedBackDlg dlg;
    dlg.setAssignId(assignId);
    dlg.setPncpCode(pncpCode);
    dlg.setTransId(transId);
    dlg.setTransCode(transCode);
    dlg.setFront(front);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_enrollBtn_clicked()
【函数功能】                                 与tableView联系，显示译者报名情况
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::on_enrollBtn_clicked()
{
    inEnroll();
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterEnroll(const QModelIndex&)));
}

/***********************************************************************************************************************
【函数名称】                                 on_assignBtn_clicked()
【函数功能】                                 与tableView联系，显示进入任务分配
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::on_assignBtn_clicked()
{
    if (pncpList[pncpId].getStatus() != RECUITING_TRANSLATOR)
    {
        //分配过任务后不可重新分配
        QMessageBox::warning(this, "warning", tr("您已分配过任务，不得重新分配"), QMessageBox::Ok);
        return;
    }
    //分配任务后状态改变
    assignList[assignId].setEStatus(ON_TRANSLATING);
    pubList[assignId].setEStatus(ON_TRANSLATING);
    pncpList[pncpId].setEStatus(ON_TRANSLATING);
    QList<AssignTranslator>::iterator i;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == assignId) && (i->getETransState() == CONFIRMED))
        {
            i->setEStatus(ON_TRANSLATING);
            //提醒译者
            MsgBox msg(i->getITransCode(), pncpCode, tr("任务分配提醒"), tr("您所参与的任务")+
                       assignList[assignId].getSTitle()+tr("已分配任务"));
            msgList.push_back(msg);
        }
    }
    inAssign();
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterAssign(const QModelIndex&)));
}

/***********************************************************************************************************************
【函数名称】                                 on_transBtn_clicked()
【函数功能】                                 与tableView联系，显示译者完成情况
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::on_transBtn_clicked()
{
    //先检测
    if (pncpList[pncpId].getStatus() != ON_TRANSLATING)
    {
        QMessageBox::information(this, tr("提示"), tr("现在不是翻译阶段，无法查看译文"), QMessageBox::Ok);
        return;
    }
    inTrans();
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterTrans(const QModelIndex&)));
}

/***********************************************************************************************************************
【函数名称】                                 on_transDDLBtn_clicked()
【函数功能】                                 弹出设置译者报名截止时间日历
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::on_transDDLBtn_clicked()
{
    transDDLDlg dlg;
    dlg.setPncpId(pncpId);
    dlg.setAssignId(assignId);
    dlg.setPncpCode(pncpCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_submitBtn_clicked()
【函数功能】                                 负责人提交子任务前的确认工作
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::on_submitBtn_clicked()
{
    if (!pubList[assignId].getSFinish().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("本次提交会覆盖之前的提交"), QMessageBox::Yes);
    }
    QString finish = ui->plainTextEdit->toPlainText();
    if (finish.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("您还没有合并译文"), QMessageBox::Yes);
        return;
    }
    pubList[assignId].setSFinish(finish);
    int pubCode = pubList[assignId].getIPublisherCode();
    //向发布者发送消息
    MsgBox msg(pubCode, pncpCode, tr("任务合并提交通知"), tr("您发布的任务")+QString::number(assignId)
               +pubList[assignId].getSTitle()+tr("，已提交，请及时确认任务完成并支付酬金"));
    msgList.push_back(msg);
    QMessageBox::information(this, tr("提示"), tr("已成功提交"), QMessageBox::Yes);
}

/***********************************************************************************************************************
【函数名称】                                 on_getBtn_clicked()
【函数功能】                                 负责人获取酬金的槽函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void PncpDlg::on_getBtn_clicked()
{
    int sum = 1;//加上负责人的人数
    QList<AssignTranslator>::iterator i;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == assignId) && (i->getETransState() == SUBMITED))
        {
            sum++;
        }
    }
    double account = userInfoList[pncpCode].getBalance();
    account += pncpList[pncpId].getReward()/sum;
    userInfoList[pncpCode].setBalance(account);
    QMessageBox::information(this, tr("提示"), tr("您已成功领取酬金"), QMessageBox::Yes);
    return;
}
