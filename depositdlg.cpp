/**********************************************************************************************************************
【文件名】                                  depositdlg.cpp
【功能模块和目的】                            Depositdlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.25
【更改记录】
**********************************************************************************************************************/

#include "depositdlg.h"
#include "ui_depositdlg.h"
#include <QMessageBox>
#include "confirmdlg.h"
#include <QDateTime>

/***********************************************************************************************************************
【函数名称】                                 Depositdlg()
【函数功能】                                 类Depositdlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.25
【更改记录】
***********************************************************************************************************************/

Depositdlg::Depositdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Depositdlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~Depositdlg()
【函数功能】                                 类Depositdlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.25
【更改记录】
***********************************************************************************************************************/

Depositdlg::~Depositdlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_confirmBtn_clicked()
【函数功能】                                 确认支付的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.25
【更改记录】
***********************************************************************************************************************/

void Depositdlg::on_confirmBtn_clicked()
{
    double account = userInfoList[userCode].getBalance();
    double deposit = ui->doubleSpinBox->value();
    if (deposit < 0)
    {
        //检测充值金额是否为负
        QMessageBox::warning(this, "warning", tr("充值金额不可为负数"), QMessageBox::Yes);
        ui->doubleSpinBox->clear();
        return;
    }
    //充值前再次判断
    ConfirmDlg dlg;
    QString content = tr("您现有余额为：") + QString::number(userInfoList[userCode].getBalance())
            + tr("，充值金额为：") + QString::number(deposit) + tr("是否确认充值？");
    dlg.setContent(content);
    if (dlg.exec() == QDialog::Accepted)
    {
        account += deposit;
        userInfoList[userCode].setBalance(account);
        //充值成功后系统给用户发消息提醒
        MsgBox msg(userCode, -1, tr("充值操作提醒"), tr("您于")+QDate::currentDate().toString("yyyy年MM月dd日")
                   +QTime::currentTime().toString("hh：mm:ss")+tr("充值")
                   +QString::number(deposit));
        msgList.push_back(msg);
        QMessageBox::information(this, tr("提示"), tr("充值成功"), QMessageBox::Yes);
        ui->labCurrNum->setText(QString::number(account));
        close();
    }
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Depositdlg::setUserCode(int value)
{
    userCode = value;
    //初始化，显示余额
    ui->labFront->setAlignment(Qt::AlignCenter);
    ui->labCurrNum->setText(QString::number(userInfoList[userCode].getBalance()));
    ui->labCurrNum->setAlignment(Qt::AlignCenter);
}
