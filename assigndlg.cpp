/**********************************************************************************************************************
【文件名】                                  assigndlg.cpp
【功能模块和目的】                            assignDlg类中成员函数的实现
【开发者及日期】                             门恺文2019.7.27
【更改记录】
**********************************************************************************************************************/

#include "assigndlg.h"
#include "ui_assigndlg.h"
#include "enrolldlg.h"
#include <QDateTime>
#include <QStandardItem>

/***********************************************************************************************************************
【函数名称】                                 assignDlg(QWidget *parent)
【函数功能】                                 类assignDlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.27
【更改记录】
***********************************************************************************************************************/

assignDlg::assignDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::assignDlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~assignDlg()
【函数功能】                                 类assignDlg的析构函数，在对象被销毁时调用
【参数】                                    指向界面文件的指针
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

assignDlg::~assignDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 getAssignId()
【函数功能】                                 成员m_iAssignId的获取函数
【参数】                                     m_iAssignId, int, 输出参数
【返回值】                                   m_iAssignId，任务编号
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

int assignDlg::getAssignId() const
{
    return m_iAssignId;
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId
【函数功能】                                 成员m_iAssignId的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     m_iAssignId, int, 输出参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::setAssignId(int value)
{
    m_iAssignId = value;
    //在获取任务编号后设置界面内容
    ui->labTitle->setText(assignList[m_iAssignId].getSTitle());
    ui->plainTextEditDesc->setPlainText(assignList[m_iAssignId].getDesc());
    ui->plainTextEditContent->setPlainText(assignList[m_iAssignId].getContent());
    ui->lineEditStartDate->setText(assignList[m_iAssignId].getStartTime());
    ui->lineEditEndDate->setText(assignList[m_iAssignId].getEndTime());
    ui->lineEditReward->setText(QString::number(assignList[m_iAssignId].getReward()));
    ui->lineEditPncpDDL->setText(assignList[m_iAssignId].getPncpDDL());
    ui->lineEditTransDDL->setText(assignList[m_iAssignId].getTransDDL());
    ui->lineEditOri->setText(assignList[m_iAssignId].getTrans().Translanguage::getOri());
    //查找并显示任务负责人
    int pncpCode = -1;
    for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
    {
        if ((i->getAssignId() == m_iAssignId) && (i->getBIsConfirmed()))
        {
            //当负责人对应的任务编号与当前任务编号对应，且负责人状态为已指定时，则可确定是该负责人
            pncpCode = i->getIPncpCode();
            ui->lineEditPncp->setText(userInfoList[pncpCode].getUserName());
            break;
        }
    }
    //查找并显示任务译者
    QStandardItemModel* itemModel = new QStandardItemModel(this);
    for (QList<AssignTranslator>::iterator i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == m_iAssignId) && (i->getETransState() != APPLYING))
        {
            //译者状态不为APPLYING，说明参与该翻译任务
            int transCode = i->getITransCode();
            QString userName = userInfoList[transCode].getUserName();
            QStandardItem* item = new QStandardItem(userName);
            itemModel->appendRow(item);
        }
    }
    ui->listView->setModel(itemModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //显示任务译文种类
    QStandardItemModel* itemModel2 = new QStandardItemModel(this);
    QVector<QString> goal = assignList[m_iAssignId].getTrans().Translanguage::getGoal();
    for (int i = 0; i < goal.size(); i++)
    {
        QStandardItem* item = new QStandardItem(goal[i]);
        itemModel2->appendRow(item);
    }
    ui->listView_2->setModel(itemModel2);
    ui->listView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //负责人报名截止日期之后不可报名负责人
    if (pubList[m_iAssignId].getPncpDDL() < QDate::currentDate().toString("yyyy-MM-dd"))
    {
        ui->pncpBtn->setEnabled(false);
    }
    //负责人指定译者报名截止日期之前和截止日期之后均不可报名译者
    if (pubList[m_iAssignId].getTransDDL() < QDate::currentDate().toString("yyyy-MM-dd"))
    {
        ui->transBtn->setEnabled(false);
    }
}

/***********************************************************************************************************************
【函数名称】                                 getUsername()
【函数功能】                                 成员Username的获取函数
【参数】                                     Username, QString, 输出参数
【返回值】                                   Username，用户名
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

QString assignDlg::getUsername() const
{
    return Username;
}

/***********************************************************************************************************************
【函数名称】                                 setUsername()
【函数功能】                                 成员Username的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     Username, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::setUsername(const QString &value)
{
    Username = value;
}

/***********************************************************************************************************************
【函数名称】                                 getTitle()
【函数功能】                                 成员title的获取函数
【参数】                                     title, QString, 输出参数
【返回值】                                   title，任务标题
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

QString assignDlg::getTitle() const
{
    return title;
}

/***********************************************************************************************************************
【函数名称】                                 setTitle()
【函数功能】                                 成员title的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     title, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::setTitle(const QString &value)
{
    title = value;
}

/***********************************************************************************************************************
【函数名称】                                 getDesc()
【函数功能】                                 成员Desc的获取函数
【参数】                                     Desc, QString, 输出参数
【返回值】                                   Desc，任务简介
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

QString assignDlg::getDesc() const
{
    return Desc;
}

/***********************************************************************************************************************
【函数名称】                                 setDesc()
【函数功能】                                 成员Desc的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     Desc, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::setDesc(const QString &value)
{
    Desc = value;
}

/***********************************************************************************************************************
【函数名称】                                 on_pncpBtn_clicked()
【函数功能】                                 pncpBtn的槽函数，响应负责人报名操作
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::on_pncpBtn_clicked()
{
    //3为界限
    if (userInfoList[userCode].getPoint() < 3)
    {
        QMessageBox::warning(this, tr("warning"), tr("积分不足，无法报名负责人"), QMessageBox::Ok);
        return;
    }
    //报名过负责人则不可重复报名
    QList<AssignPrincipal>::iterator i;
    for (i = pncpList.begin(); i < pncpList.end(); i++)
    {
        if ((i->getAssignId() == m_iAssignId) &&(i->getSPncpName() == Username))
        {
            QMessageBox::information(this, tr("提示"), tr("您已报名负责人，不得重复报名"), QMessageBox::Ok);
            return;
        }
    }
    //进入报名界面，初识类型0表示负责人
    EnrollDlg dlg;
    dlg.setType(0);
    QString Front = tr("欢迎报名") + assignList[m_iAssignId].getSTitle() + tr("负责人");
    dlg.setFront(Front);
    dlg.setUserName(Username);
    dlg.setAssignId(m_iAssignId);
    dlg.setPublisherCode(publisherCode);
    dlg.setSenderCode(userCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_transBtn_clicked()
【函数功能】                                 transBtn的槽函数，响应译者报名操作
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::on_transBtn_clicked()
{
    //判断是否重复报名
    QList<AssignTranslator>::iterator i;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == m_iAssignId) && (i->getSTransName() == Username))
        {
            QMessageBox::information(this, tr("提示"), tr("您已报名译者，不得重复报名"), QMessageBox::Ok);
            return;
        }
    }

    //进入报名界面，初始任务为1代表译者
    EnrollDlg dlg;
    dlg.setType(1);
    QString Front = tr("欢迎报名") + title + tr("译者");
    dlg.setFront(Front);
    dlg.setUserName(Username);
    dlg.setAssignId(m_iAssignId);
    dlg.setPublisherCode(publisherCode);
    dlg.setSenderCode(userCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 getPublisherCode()
【函数功能】                                 成员publisherCode的获取函数
【参数】                                     publisherCode, int, 输出参数
【返回值】                                   publisherCode，发布者用户编号
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

int assignDlg::getPublisherCode() const
{
    return publisherCode;
}

/***********************************************************************************************************************
【函数名称】                                 setPublisherCode()
【函数功能】                                 成员publisherCode的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     publisherCode, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::setPublisherCode(int value)
{
    publisherCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 getUserCode()
【函数功能】                                 成员userCode的获取函数
【参数】                                     userCode, int, 输出参数
【返回值】                                   userCode，发布者用户编号
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

int assignDlg::getUserCode() const
{
    return userCode;
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员UserCode的设置函数，并在设置之后设置页面打开前的内容
【参数】                                     UserCode, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void assignDlg::setUserCode(int value)
{
    userCode = value;
}
