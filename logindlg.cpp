/**********************************************************************************************************************
【文件名】                                  logindlg.cpp
【功能模块和目的】                            Logindlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
**********************************************************************************************************************/

#include "logindlg.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <QLabel>
#include "mainwindow.h"
#include "passworddlg.h"

//int Logindlg::isLogin = 0;

/***********************************************************************************************************************
【函数名称】                                 Logindlg()
【函数功能】                                 类Logindlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.24
【更改记录】
***********************************************************************************************************************/

Logindlg::Logindlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logindlg)
{
    ui->setupUi(this);
    userCode = -1;
}

/***********************************************************************************************************************
【函数名称】                                 ~Logindlg()
【函数功能】                                 类Logindlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

Logindlg::~Logindlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_btnLogin_clicked()
【函数功能】                                 登录槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Logindlg::on_btnLogin_clicked()
{
    //登录匹配用户名和密码
    QList<User>::iterator userInfo_i;
    for (userInfo_i = userInfoList.begin(); userInfo_i < userInfoList.end(); userInfo_i++)
    {
        if(ui->editUsername->text().trimmed() == userInfo_i->getUserName() &&
                   ui->editPassword->text().trimmed() == userInfo_i->getPassword())
        {
            userCode = userInfo_i->getICode();
            Username = ui->editUsername->text().trimmed();//shan
            QMessageBox::information(this, tr("提示"), tr("您已成功登录"), QMessageBox::tr("确定"));
            accept();
        }
    }
    //未能匹配的情况
    if (userCode == -1)
    {
        QMessageBox::warning(this, tr("warning"),
                                 tr("用户名或密码错误"),
                                 QMessageBox::tr("确定"));

        //清空内容并定位光标
        ui->editUsername->clear();
        ui->editPassword->clear();
        ui->editUsername->setFocus();
        return;
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_btnRegister_clicked()
【函数功能】                                 注册槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Logindlg::on_btnRegister_clicked()
{
    //进入注册界面
    Signupdlg signup(this);
    signup.exec();
    return;
}

/***********************************************************************************************************************
【函数名称】                                 getUsername()
【函数功能】                                 成员Username的获取函数
【参数】                                     Username, QString, 输出参数
【返回值】                                   Username，用户名
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

QString Logindlg::getUsername() const
{
    return Username;
}

/***********************************************************************************************************************
【函数名称】                                 on_commandLinkButton_clicked()
【函数功能】                                 找回密码槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Logindlg::on_commandLinkButton_clicked()
{
    //进入找回密码界面
    PasswordDlg dlg;
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 getUserCode()
【函数功能】                                 成员UserCode的获取函数
【参数】                                     UserCode, int, 输出参数
【返回值】                                   UserCode，用户编号
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

int Logindlg::getUserCode() const
{
    return userCode;
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void Logindlg::setUserCode(int value)
{
    userCode = value;
}
