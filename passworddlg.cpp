/**********************************************************************************************************************
【文件名】                                  passworddlg.cpp
【功能模块和目的】                            PasswordDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
**********************************************************************************************************************/

#include "passworddlg.h"
#include "ui_passworddlg.h"
#include <QLineEdit>
#include <QMessageBox>

/***********************************************************************************************************************
【函数名称】                                 PasswordDlg()
【函数功能】                                 类PasswordDlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.23
【更改记录】
***********************************************************************************************************************/

PasswordDlg::PasswordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordDlg)
{
    ui->setupUi(this);
    userCode = -1;
}

/***********************************************************************************************************************
【函数名称】                                 ~PasswordDlg()
【函数功能】                                 类PasswordDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

PasswordDlg::~PasswordDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_sendBtn_clicked()
【函数功能】                                 发送验证码槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void PasswordDlg::on_sendBtn_clicked()
{
    //发送验证码前须有手机号
    if (ui->LineEditPhone->text().isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请先填写手机号"), QMessageBox::Ok);
        ui->LineEditPhone->setFocus();
        return;
    }
    //检测该手机号是否注册过
    QList<User>::iterator i;
    for (i = userInfoList.begin(); i < userInfoList.end(); i++)
    {
        if (i->getMobilePhone() == ui->LineEditPhone->text())
        {
            break;
        }
    }
    //手机号需已注册
    if (i == userInfoList.end())
    {
        QMessageBox::critical(this, tr("提示"), tr("手机号错误，请确认手机号"), QMessageBox::Yes);
        ui->LineEditPhone->clear();
        ui->LineEditPhone->setFocus();
        return;
    }
    userCode = i->getICode();
    QMessageBox::information(this, tr("提示"), tr("验证码已发送至手机，请在一分钟内使用"), QMessageBox::Ok);
    ui->LineEditConfirm->setEnabled(true);
    ui->sendBtn->setEnabled(false);
}

/***********************************************************************************************************************
【函数名称】                                 on_confirmBtn_clicked()
【函数功能】                                 确认找回密码槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void PasswordDlg::on_confirmBtn_clicked()
{
    //需先输入验证码
    if (userCode == -1)
    {
        QMessageBox::critical(this, tr("提示"), tr("请先输入手机号和验证码"), QMessageBox::Yes);
        return;
    }
    if (ui->LineEditConfirm->text().isEmpty())
    {
        QMessageBox::critical(this, tr("提示"), tr("请输入验证码"), QMessageBox::Yes);
        return;
    }
    //用户名和手机号必须匹配
    if (userInfoList[userCode].getUserName() != ui->LineEditUsername->text())
    {
        QMessageBox::critical(this, tr("提示"), tr("请匹配用户名和手机号"), QMessageBox::Yes);
        ui->LineEditUsername->clear();
        ui->LineEditUsername->setFocus();
        return;
    }
    //密码与确认密码必须一致
    if (ui->LineEditPassword->text() != ui->LineEditConfirmPsw->text())
    {
        QMessageBox::critical(this, tr("提示"), tr("新密码与确认密码不一致"), QMessageBox::Yes);
        ui->LineEditConfirm->clear();
        ui->LineEditConfirm->setFocus();
        return;
    }
    userInfoList[userCode].setPassword(ui->LineEditPassword->text());
    QMessageBox::information(this, tr("提示"), tr("密码已找回"), QMessageBox::Yes);
    accept();
}
