/**********************************************************************************************************************
【文件名】                                  transdlg.cpp
【功能模块和目的】                            TransDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.28
【更改记录】
**********************************************************************************************************************/

#include "transdlg.h"
#include "ui_transdlg.h"
#include <QDateTime>
#include "confirmdlg.h"

/***********************************************************************************************************************
【函数名称】                                 TransDlg()
【函数功能】                                 类TransDlg的构造函数
【参数】                                     QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.28
【更改记录】
***********************************************************************************************************************/

TransDlg::TransDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransDlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~TransDlg()
【函数功能】                                 类TransDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

TransDlg::~TransDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 setTransCode()
【函数功能】                                 成员transCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void TransDlg::setTransCode(int value)
{
    transCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 setTransId()
【函数功能】                                 成员transId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void TransDlg::setTransId(int value)
{
    transId = value;
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId()
【函数功能】                                 成员assignId的设置函数，同时改变页面
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void TransDlg::setAssignId(int value)
{
    assignId = value;

    ui->labFront->setText(tr("任务") + QString::number(assignId) + tr("：") + pubList[assignId].getSTitle());
    if (QDate::currentDate().toString("yyyy-MM-dd") > assignList[assignId].getEndTime())
    {
        ui->submitBtn->setEnabled(false);
        ui->saveBtn->setEnabled(false);
    }
    if (transList[transId].getStatus() != ON_SHELF)
    {
        ui->getBtn->setEnabled(false);
    }
    ui->plainTextEditAssign->setPlainText(transList[transId].getSMission());
    ui->plainTextEditFeedback->setPlainText(transList[transId].getSFeedback());
    ui->plainTextEditMission->setPlainText(transList[transId].getSSubmit());
}

/***********************************************************************************************************************
【函数名称】                                 on_saveBtn_clicked()
【函数功能】                                 译者任务的暂存
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void TransDlg::on_saveBtn_clicked()
{
    QString mission = ui->plainTextEditMission->toPlainText();
    ConfirmDlg dlg;
    dlg.setContent(tr("是否确认保存？"));
    if (dlg.exec() == QDialog::Accepted)
    {
        transList[transId].setSSubmit(mission);
        transList[transId].setETransState(TRANSLATING);
        QMessageBox::information(this, tr("提示"), tr("您已成功保存"), QMessageBox::Yes);
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_submitBtn_clicked()
【函数功能】                                 译者任务的提交
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void TransDlg::on_submitBtn_clicked()
{
    QString mission = ui->plainTextEditMission->toPlainText();
    if (!transList[transId].getSSubmit().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("系统只保留最后一次提交内容"), QMessageBox::Yes);
    }
    if (mission.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写翻译内容"), QMessageBox::Ok);
        return;
    }
    ConfirmDlg dlg;
    dlg.setContent(tr("是否确认提交？"));
    if (dlg.exec() == QDialog::Accepted)
    {
        transList[transId].setSSubmit(mission);
        transList[transId].setETransState(SUBMITED);
        QMessageBox::information(this, tr("提示"), tr("您已成功提交"), QMessageBox::Yes);
    }
    return;
}

/***********************************************************************************************************************
【函数名称】                                 on_getBtn_clicked()
【函数功能】                                 译者领取酬金
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.28
【更改记录】
***********************************************************************************************************************/

void TransDlg::on_getBtn_clicked()
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
    double account = userInfoList[transCode].getBalance();
    account += transList[transId].getReward()/sum;
    userInfoList[transCode].setBalance(account);
    QMessageBox::information(this, tr("提示"), tr("您已领取酬金"), QMessageBox::Yes);
}
