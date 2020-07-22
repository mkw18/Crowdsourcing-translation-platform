/**********************************************************************************************************************
【文件名】                                  transddldlg.cpp
【功能模块和目的】                            transDDLDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.27
【更改记录】
**********************************************************************************************************************/

#include "transddldlg.h"
#include "ui_transddldlg.h"
#include <QDateTime>

/***********************************************************************************************************************
【函数名称】                                 transDDLDlg()
【函数功能】                                 类transDDLDlg的构造函数
【参数】                                     QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.27
【更改记录】
***********************************************************************************************************************/

transDDLDlg::transDDLDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transDDLDlg)
{
    ui->setupUi(this);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
}

/***********************************************************************************************************************
【函数名称】                                 ~transDDLDlg()
【函数功能】                                 类transDDLDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

transDDLDlg::~transDDLDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_confirmBtn_clicked()
【函数功能】                                 负责人指定截止日期前的确认
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void transDDLDlg::on_confirmBtn_clicked()
{
    if (DDL.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请先选择截止日期"), QMessageBox::Ok);
        return;
    }
    if (DDL < QDate::currentDate().toString("yyyy-MM-dd"))
    {
        QMessageBox::warning(this, "warning", tr("截止日期不得早于今日"));
        return;
    }
    //所有相关任务状态均变
    assignList[assignId].setTransDDL(DDL);
    pubList[assignId].setTransDDL(DDL);
    pncpList[pncpId].setTransDDL(DDL);
    QList<AssignTranslator>::iterator i;
    for (i = transList.begin(); i < transList.end(); i++)
    {
        if ((i->getAssignId() == assignId) && (i->getETransState() != APPLYING))
        {
            int transCode = i->getITransCode();
            int transId = i->iTransId();
            transList[transId].setTransDDL(DDL);
            //向译者发送消息
            MsgBox msg(transCode, pncpCode, tr("任务截止日期提醒"), tr("您所翻译的任务")+
                       QString::number(i->getAssignId())+i->getSTitle()+tr("已设定截止日期，")+DDL+tr("请及时翻译"));
        }
    }
    QMessageBox::information(this, tr("提示"), tr("已成功设定截止日期"), QMessageBox::Yes);
    accept();
}

/***********************************************************************************************************************
【函数名称】                                 setPncpCode()
【函数功能】                                 成员pncpCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void transDDLDlg::setPncpCode(int value)
{
    pncpCode = value;
}

/***********************************************************************************************************************
【函数名称】                                 setPncpId()
【函数功能】                                 成员pncpId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void transDDLDlg::setPncpId(int value)
{
    pncpId = value;
}

/***********************************************************************************************************************
【函数名称】                                 setAssignId()
【函数功能】                                 成员assignId的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void transDDLDlg::setAssignId(int value)
{
    assignId = value;
}

/***********************************************************************************************************************
【函数名称】                                 on_calendar_selectionChanged()
【函数功能】                                 负责人选择日期改变时对应的槽函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.27
【更改记录】
***********************************************************************************************************************/

void transDDLDlg::on_calendar_selectionChanged()
{
    QDate ddl = ui->calendar->selectedDate();
    DDL = ddl.toString("yyyy-MM-dd");
    ui->lineEdit->setText(DDL);
}
