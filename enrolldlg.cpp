/**********************************************************************************************************************
【文件名】                                  enrolldlg.cpp
【功能模块和目的】                            EnrollDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.25
【更改记录】
**********************************************************************************************************************/

#include "enrolldlg.h"
#include "ui_enrolldlg.h"
#include "contrastdlg.h"
#include <QDateTime>

/***********************************************************************************************************************
【函数名称】                                 EnrollDlg()
【函数功能】                                 类EnrollDlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.25
【更改记录】
***********************************************************************************************************************/

EnrollDlg::EnrollDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnrollDlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~EnrollDlg()
【函数功能】                                 类EnrollDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.25
【更改记录】
***********************************************************************************************************************/

EnrollDlg::~EnrollDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_checkBox_clicked()
【函数功能】                                 弹出译者协议的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.25
【更改记录】
***********************************************************************************************************************/

void EnrollDlg::on_checkBox_clicked()
{
    //勾选同时弹出译者协议，需要阅读
    ContrastDlg dlg;
    dlg.exec();
}


void EnrollDlg::setAssignId(int value)
{
    assignId = value;
}

void EnrollDlg::setType(int value)
{
    type = value;
}

void EnrollDlg::setUserName(const QString &value)
{
    userName = value;
}

void EnrollDlg::setFront(const QString &value)
{
    front = value;
    ui->labFront->setText(front);
}

/***********************************************************************************************************************
【函数名称】                                 on_admitBtn_clicked()
【函数功能】                                 报名前确认槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.25
【更改记录】
***********************************************************************************************************************/

void EnrollDlg::on_admitBtn_clicked()
{
    //核对姓名
    if ((!userInfoList[senderCode].getName().isEmpty()) && (userInfoList[senderCode].getName() != ui->lineEditName->text()))
    {
        QMessageBox::warning(this, tr("warning"), tr("请填写真实姓名"), QMessageBox::Ok);
        ui->lineEditName->clear();
        ui->lineEditName->setFocus();
        return;
    }
    //姓名为必填项
    if (ui->lineEditName->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("真实姓名不得为空"), QMessageBox::Ok);
        ui->lineEditName->setFocus();
        return;
    }
    //核对邮箱
    if ((!userInfoList[senderCode].getEmail().isEmpty()) && (userInfoList[senderCode].getEmail() != ui->LineEditEmail->text()))
    {
        QMessageBox::warning(this, tr("warning"), tr("请填写真实邮箱"), QMessageBox::Ok);
        ui->LineEditEmail->clear();
        ui->LineEditEmail->setFocus();
        return;
    }
    //邮箱为必填项
    if (ui->LineEditEmail->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("邮箱不得为空"), QMessageBox::Ok);
        ui->LineEditEmail->setFocus();
        return;
    }
    //核对电话
    if (userInfoList[senderCode].getMobilePhone() != ui->LineEditPhone->text())
    {
        QMessageBox::warning(this, tr("warning"), tr("请填写真实手机号码"), QMessageBox::Ok);
        ui->LineEditPhone->clear();
        ui->LineEditPhone->setFocus();
        return;
    }
    //电话为必填项
    if (ui->LineEditPhone->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("手机号码不得为空"), QMessageBox::Ok);
        ui->LineEditPhone->setFocus();
        return;
    }
    //checkBox必须勾选
    if (!ui->checkBox->isChecked())
    {
        QMessageBox::warning(this, "warning", tr("请先阅读并同意译者协议"));
        return;
    }
    //实时更新用户信息
    userInfoList[senderCode].setName(ui->lineEditName->text());
    userInfoList[senderCode].setEmail(ui->LineEditEmail->text());
    userInfoList[senderCode].setMobilePhone(ui->LineEditPhone->text());
    QString CV = ui->plainTextEditCV->toPlainText();
    //报名负责人的情况
    if (type == 0)
    {
        AssignPrincipal pncp(pubList[assignId].getTrans(), pubList[assignId].getSTitle(), pubList[assignId].getContent(),
                             pubList[assignId].getDesc(), pubList[assignId].getStartTime(), pubList[assignId].getEndTime(),
                             pubList[assignId].getPncpNum(), pubList[assignId].getTransNum(), pubList[assignId].getPncpDDL(),
                             pubList[assignId].getTransDDL(), pubList[assignId].getTrial(), pubList[assignId].getReward(),
                             pubList[assignId].getStatus(), pubList[assignId].getAssignId(),
                             userName, senderCode, CV);
        pncpList.push_back(pncp);
        //向该负责人发消息
        MsgBox msg0(senderCode, -1,tr("负责人报名通知"), tr("您已报名")+QString::number(assignId) + tr("负责人"));
        msgList.push_back(msg0);
        QMessageBox::information(this, tr("提示"), tr("您已成功报名负责人"), QMessageBox::Yes);
        //给发布者发消息
        MsgBox msg(publisherCode, senderCode, tr("负责人报名通知"), userName + tr("已报名负责人"));
        msgList.push_back(msg);
    }
    //报名者为译者的情况
    else if (type == 1)
    {
        AssignTranslator trans(pubList[assignId].getTrans(), pubList[assignId].getSTitle(), pubList[assignId].getContent(),
                               pubList[assignId].getDesc(), pubList[assignId].getStartTime(), pubList[assignId].getEndTime(),
                               pubList[assignId].getPncpNum(), pubList[assignId].getTransNum(), pubList[assignId].getPncpDDL(),
                               pubList[assignId].getTransDDL(), pubList[assignId].getTrial(), pubList[assignId].getReward(),
                               pubList[assignId].getStatus(), pubList[assignId].getAssignId(),
                               userName, senderCode, CV);
        transList.push_back(trans);
        //向该译者发消息
        MsgBox msg0(senderCode, -1,tr("译者报名通知"), tr("您已报名")+QString::number(assignId) + tr("译者"));
        msgList.push_back(msg0);
        QMessageBox::information(this, tr("提示"), tr("您已报名译者"), QMessageBox::Yes);
        //给发布者发消息
        MsgBox msg(publisherCode, senderCode, tr("译者报名通知"), userName + tr("已报名译者"));
        msgList.push_back(msg);
        //给负责人发消息
        QList<AssignPrincipal>::iterator j;
        for (j = pncpList.begin(); j < pncpList.end(); j++)
        {
            if ((j->getAssignId() == assignId) && (j->getBIsConfirmed()))
            {
                int pncpCode = j->getIPncpCode();
                MsgBox msg(pncpCode, senderCode, tr("译者报名通知"), userName + tr("已报名译者"));
                msgList.push_back(msg);
            }
        }
    }
    accept();
}

/***********************************************************************************************************************
【函数名称】                                 setSenderCode()
【函数功能】                                 成员senderCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void EnrollDlg::setSenderCode(int value)
{
    senderCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 setPublisherCode()
【函数功能】                                 成员publisherCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void EnrollDlg::setPublisherCode(int value)
{
    publisherCode = value;
}
