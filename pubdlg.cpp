/**********************************************************************************************************************
【文件名】                                  pubdlg.cpp
【功能模块和目的】                            PubDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
**********************************************************************************************************************/

#include "pubdlg.h"
#include "ui_pubdlg.h"
#include <QTableView>
#include <QStandardItemModel>
#include "auditdlg.h"
#include "confirmdlg.h"
#include "depositdlg.h"

/***********************************************************************************************************************
【函数名称】                                 PubDlg()
【函数功能】                                 类PubDlg的构造函数
【参数】                                     QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.26
【更改记录】
***********************************************************************************************************************/

PubDlg::PubDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PubDlg)
{
    ui->setupUi(this);

    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterPncp(const QModelIndex&)));
}

/***********************************************************************************************************************
【函数名称】                                 ~PubDlg()
【函数功能】                                 类PubDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

PubDlg::~PubDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 setPubCode()
【函数功能】                                 成员pubCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::setPubCode(int value)
{
    pubCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId()
【函数功能】                                 成员assignId的设置函数，改变页面内容
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::setAssignId(int value)
{
    assignId = value;
    //设置页面数据
    ui->labFront->setText(tr("任务") + QString::number(assignId) + tr("：") + pubList[assignId].getSTitle());
    if (!pubList[assignId].getSFinish().isEmpty())
    {
        ui->plainTextEditTrans->setPlainText(pubList[assignId].getSFinish());
    }
    init();
}

/***********************************************************************************************************************
【函数名称】                                 enterPncp()
【函数功能】                                 进入查看负责人报名情况页面
【参数】                                     QModelIndex &index, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::enterPncp(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *assign = const_cast<QAbstractItemModel *>(index.model());
    int pncpCode = assign->data(assign->index(row, 0 ,QModelIndex())).toInt();
    int pncpId = assign->data(assign->index(row, 5, QModelIndex())).toInt();
    AuditDlg dlg;
    dlg.setApplyCode(pncpCode);
    dlg.setApplyId(pncpId);
    dlg.setAssignId(assignId);
    dlg.setUserCode(pubCode);
    dlg.setType(0);//代表负责人
    dlg.setFront(tr("负责人") + QString::number(pncpId));
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 init()
【函数功能】                                 较庞大而重复性高的函数，单独封装，提高代码可重用性，同时简化代码。置于查看负责嗯报名情况槽函数内
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::init()
{
    //显示负责人表格
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("编号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("真实姓名")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("常用邮箱")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("手机号码")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("简历")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("负责人任务编号")));

    QList<AssignPrincipal>::iterator i;
    int row = 0;
    for (i = pncpList.begin(); i < pncpList.end(); i++)
    {
        if (i->getAssignId() == assignId)
        {
            int pncpCode = i->getIPncpCode();
            int pncpId = i->getINum();
            model->setItem(row, 0, new QStandardItem(QString::number(pncpCode)));
            model->setItem(row, 1, new QStandardItem(userInfoList[pncpCode].getName()));
            model->setItem(row, 2, new QStandardItem(userInfoList[pncpCode].getEmail()));
            model->setItem(row, 3, new QStandardItem(userInfoList[pncpCode].getMobilePhone()));
            model->setItem(row, 4, new QStandardItem(tr("查看")));
            model->setItem(row, 5, new QStandardItem(QString::number(pncpId)));
        }
    }
    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}


/***********************************************************************************************************************
【函数名称】                                 on_confirmBtn_clicked()
【函数功能】                                 发布者确认任务完成前的确认槽函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::on_confirmBtn_clicked()
{
    QString front = tr("是否确定任务完成？");
    ConfirmDlg dlg;
    dlg.setContent(front);
    if (dlg.exec() == QDialog::Accepted)
    {
        assignList[assignId].setEStatus(TRANSLATION_FINISHED);
        pubList[assignId].setEStatus(TRANSLATION_FINISHED);
        QMessageBox::information(this, tr("通知"), tr("您已确认任务完成，请及时支付酬金"), QMessageBox::Yes);
        QList<AssignPrincipal>::iterator i;
        for (i = pncpList.begin(); i < pncpList.end(); i++)
        {
            if ((i->getAssignId() == assignId) && (i->getBIsConfirmed() == true))
            {
                i->setEStatus(TRANSLATION_FINISHED);
                MsgBox msg(i->getIPncpCode(), pubCode, tr("任务确认通知"),
                           tr("您所负责的任务")+QString::number(i->getAssignId())+i->getSTitle()+tr("已确认完成"), -1);
            }
        }
        QList<AssignTranslator>::iterator j;
        for (j = transList.begin(); j < transList.end(); j++)
        {
            if ((j->getAssignId() == assignId) && (j->getETransState() == SUBMITED))
            {
                j->setEStatus(TRANSLATION_FINISHED);
                int transCode = j->getITransCode();
                int points = userInfoList[transCode].getPoint();
                points++;
                userInfoList[transCode].setPoint(points);
                MsgBox msg(j->getITransCode(), pubCode, tr("任务确认通知"),
                           tr("您所参与翻译的任务")+QString::number(j->getAssignId())+j->getSTitle()+tr("已确认完成"));
            }
        }
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_payBtn_clicked()
【函数功能】                                 发布者支付前的确认槽函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::on_payBtn_clicked()
{
    if (pubList[assignId].getStatus() != TRANSLATION_FINISHED)
    {
        if (pubList[assignId].getStatus() == ON_SHELF)
        {
            QMessageBox::information(this, tr("提示"), tr("您已完成支付"), QMessageBox::Yes);
            return;
        }
        else {
            QMessageBox::information(this, tr("提示"), tr("请先确认完成"), QMessageBox::Ok);
            return;
        }
    }
    ConfirmDlg dlg;
    QString content = tr("该任务金额为")+QString::number(pubList[assignId].getReward())+tr("，是否确认支付？");
    dlg.setContent(content);
    if (dlg.exec() == QDialog::Accepted)
    {
        assignList[assignId].setEStatus(ON_SHELF);
        pubList[assignId].setEStatus(ON_SHELF);
        double account = userInfoList[pubCode].getBalance();
        if (account < pubList[assignId].getReward())
        {
            QMessageBox::information(this, tr("提示"), tr("余额不足，请先充值"), QMessageBox::Ok);
            return;
        }
        account -= pubList[assignId].getReward();
        userInfoList[pubCode].setBalance(account);
        QMessageBox::information(this, tr("通知"), tr("您已完成支付"), QMessageBox::Yes);
        MsgBox Msg(pubCode, -1, tr("支付提醒"), tr("您已支付任务")+QString::number(assignId)+tr("：")+
                   pubList[assignId].getSTitle()+QString::number(pubList[assignId].getReward())
                   +tr("元，请确认是否为本人操作"));
        msgList.push_back(Msg);
        QList<AssignPrincipal>::iterator i;
        for (i = pncpList.begin(); i < pncpList.end(); i++)
        {
            if ((i->getAssignId() == assignId) && (i->getBIsConfirmed() == true))
            {
                i->setEStatus(ON_SHELF);
                MsgBox msg(i->getIPncpCode(), pubCode, tr("酬金到账通知"),
                           tr("您所负责的任务")+QString::number(i->getAssignId())+tr("：")+i->getSTitle()
                           +tr("已完成支付，请及时领取"));
                msgList.push_back(msg);
            }
        }
        QList<AssignTranslator>::iterator j;
        for (j = transList.begin(); j < transList.end(); j++)
        {
            if ((j->getAssignId() == assignId) && (j->getETransState() == SUBMITED))
            {
                j->setEStatus(ON_SHELF);
                MsgBox msg(j->getITransCode(), pubCode, tr("酬金到账通知"),
                           tr("您所参与翻译的任务")+QString::number(j->getAssignId())+j->getSTitle()
                           +tr("已完成支付，请及时领取"));
                msgList.push_back(msg);
            }
        }
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_depositBtn_clicked()
【函数功能】                                 用户进入充值的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void PubDlg::on_depositBtn_clicked()
{
    Depositdlg dlg;
    dlg.setUserCode(pubCode);
    dlg.exec();
}
