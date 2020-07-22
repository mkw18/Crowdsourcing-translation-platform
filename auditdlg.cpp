/**********************************************************************************************************************
【文件名】                                  auditdlg.cpp
【功能模块和目的】                            AuditDlg类中成员函数的实现，包括槽函数、接口函数等
【开发者及日期】                             门恺文2019.7.28
【更改记录】
**********************************************************************************************************************/

#include "auditdlg.h"
#include "ui_auditdlg.h"
#include <QDateTime>
#include "confirmdlg.h"
#include "msgbox.h"

/***********************************************************************************************************************
【函数名称】                                 AuditDlg()
【函数功能】                                 类AuditDlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，均为输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.28
【更改记录】
***********************************************************************************************************************/

AuditDlg::AuditDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuditDlg)
{
    ui->setupUi(this);

    //审核报名信息均以只读的方式
    ui->LineEditCode->setReadOnly(true);
    ui->LineEditName->setReadOnly(true);
    ui->LineEditEmail->setReadOnly(true);
    ui->LineEditPhone->setReadOnly(true);
    ui->plainTextEditCV->setReadOnly(true);
}

/***********************************************************************************************************************
【函数名称】                                 ~AssignTranslator()
【函数功能】                                 类AssignTranslator的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

AuditDlg::~AuditDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 setApplyCode()
【函数功能】                                 成员applyCode的设置函数，applyCode获值后可进行初始化
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::setApplyCode(int value)
{
    applyCode = value;
    //设置界面信息
    ui->LineEditCode->setText(QString::number(applyCode));
    ui->LineEditName->setText(userInfoList[applyCode].getName());
    ui->LineEditEmail->setText(userInfoList[applyCode].getEmail());
    ui->LineEditPhone->setText(userInfoList[applyCode].getMobilePhone());
}

/***********************************************************************************************************************
【函数名称】                                 setApplyId()
【函数功能】                                 成员applyId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::setApplyId(int value)
{
    applyId = value;
}

/***********************************************************************************************************************
【函数名称】                                 setType()
【函数功能】                                 成员type的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::setType(int value)
{
    type = value;

    //报名者为负责人的情况
    if (type == 0)
    {
        ui->plainTextEditCV->setPlainText(pncpList[applyId].getSCV());
        //必须在过了负责人报名截止日期后才可指定负责人
        if (QDate::currentDate().toString("yyyy-MM-dd") < pncpList[applyId].getPncpDDL())
        {
            ui->passBtn->setEnabled(false);
        }
    }
    //报名者为译者的情况
    else if (type == 1)
    {
        ui->plainTextEditCV->setPlainText(transList[applyId].getSCV());
        //过了译者报名截止日期才可报名译者
        if (QDate::currentDate().toString("yyyy-MM-dd") < transList[applyId].getTransDDL())
        {
            ui->passBtn->setEnabled(false);
        }
    }
}

/***********************************************************************************************************************
【函数名称】                                 setFront()
【函数功能】                                 成员front的设置函数
【参数】                                     value, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::setFront(const QString &value)
{
    front = value;
    ui->labFront->setText(front);
}

/***********************************************************************************************************************
【函数名称】                                 on_passBtn_clicked()
【函数功能】                                 槽函数，指定负责人或译者前的确认函数
【参数】                                     value, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::on_passBtn_clicked()
{
    ConfirmDlg dlg;
    if (type == 0)
    {
        if (pubList[assignId].getStatus() != RECUITING_PRICIPAL)
        {
            //只能指定一个负责人
            QMessageBox::warning(this, "warning", tr("您已指定负责人，不可指定多于一人"), QMessageBox::Ok);
            return;
        }
        //防止误点
        dlg.setContent(tr("是否确定指定") + userInfoList[applyCode].getName() + tr("为负责人？"));
        //确认指定的情况下
        if (dlg.exec() == QDialog::Accepted)
        {
            //首先负责人状态、任务状态、负责人人数改变
            pncpList[applyId].setBIsConfirmed(true);
            pncpList[applyId].setEStatus(RECUITING_TRANSLATOR);
            assignList[assignId].setEStatus(RECUITING_TRANSLATOR);
            pubList[assignId].setEStatus(RECUITING_TRANSLATOR);
            assignList[assignId].setIPncpNum(1);
            pubList[assignId].setIPncpNum(1);
            pncpList[applyId].setIPncpNum(1);

            QMessageBox::information(this, tr("提示"), tr("您已成功指定负责人"), QMessageBox::Yes);
            //发布者收到消息
            MsgBox msg0(userCode, -1, tr("指定负责人操作通知"), tr("您已指定")
                        + userInfoList[applyCode].getUserName()+tr("为负责人"));
            msgList.push_back(msg0);
            //被指定负责人收到消息
            MsgBox msg(applyCode, userCode, tr("报名成功通知"), tr("恭喜，您已成功报名")
                       +QString::number(pncpList[applyId].getAssignId())+pncpList[applyId].getSTitle()+tr("负责人"));
            msgList.push_back(msg);
        }
    }
    else if (type == 1)
    {
        //对于同一译者，不可重复指定
        if (transList[applyId].getETransState() != APPLYING)
        {
            QMessageBox::warning(this, "warning", tr("您已指定此译者，不可重复指定"), QMessageBox::Ok);
            return;
        }
        //再次确认
        dlg.setContent(tr("是否确定指定") + userInfoList[applyCode].getName() + tr("为译者？"));
        if (dlg.exec() == QDialog::Accepted)
        {
            transList[applyId].setETransState(CONFIRMED);
            int transNum = assignList[assignId].getTransNum() + 1;
            assignList[assignId].setITransNum(transNum);
            pubList[assignId].setITransNum(transNum);
            for (QList<AssignPrincipal>::iterator i = pncpList.begin(); i < pncpList.end(); i++)
            {
                if ((i->getIPncpCode() == userCode) && (i->getBIsConfirmed()))
                {
                    i->setITransNum(transNum);
                }
            }
            QMessageBox::information(this, tr("提示"), tr("您已成功指定译者"), QMessageBox::Yes);
            //向负责人发消息
            MsgBox msg0(userCode, -1, tr("指定译者操作通知"), tr("您已指定")
                        + userInfoList[applyCode].getUserName()+tr("为译者"));
            msgList.push_back(msg0);
            //向译者发消息
            MsgBox msg(applyCode, userCode, tr("报名成功通知"), tr("恭喜，您已成功报名")
                       +QString::number(transList[applyId].getAssignId())+transList[applyId].getSTitle()+tr("译者"));
            msgList.push_back(msg);
        }
    }
    close();
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId()
【函数功能】                                 成员assignId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::setAssignId(int value)
{
    assignId = value;
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void AuditDlg::setUserCode(int value)
{
    userCode = value;
}
