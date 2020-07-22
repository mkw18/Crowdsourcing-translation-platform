/**********************************************************************************************************************
【文件名】                                  signupdlg.cpp
【功能模块和目的】                            Signupdlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
**********************************************************************************************************************/

#include "signupdlg.h"
#include "ui_signupdlg.h"
#include <QMessageBox>

/***********************************************************************************************************************
【函数名称】                                 Signupdlg()
【函数功能】                                 类Signupdlg的构造函数
【参数】                                     QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.23
【更改记录】
***********************************************************************************************************************/

Signupdlg::Signupdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signupdlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~Signupdlg()
【函数功能】                                 类Signupdlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

Signupdlg::~Signupdlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_btnSignup_clicked()
【函数功能】                                 注册前的确认槽函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void Signupdlg::on_btnSignup_clicked()
{
    //提醒标签设置
    if(errMsg != nullptr)
    {
        delete errMsg;
    }
    errMsg = new QLabel;
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    errMsg->setPalette(pa);
    QString username = ui->lineEdit_Username->text().trimmed();
    QString mobilePhone = ui->lineEdit_Phone->text().trimmed();
    QString password = ui->lineEdit_Password->text();
    QString confirmPsw = ui->lineEdit_ConfirmPsw->text();
    QString level = ui->plainTextEdit_level->toPlainText().trimmed();
    QList<User>::iterator i = userInfoList.begin();
    if (username.size() == 0)
    {
        errMsg->setText(tr("用户名不能为空"));
        ui->verticalLayout_err->addWidget(errMsg);
        ui->lineEdit_Username->setFocus();
        return;
    }
    for (i = userInfoList.begin(); i < userInfoList.end(); i++)
    {
        if (username == i->getUserName())
        {
            QMessageBox::warning(this, "warning", tr("该用户名已存在"), QMessageBox::Yes);
            ui->lineEdit_Username->clear();
            ui->lineEdit_Username->setFocus();
            return;
        }
    }
    if (mobilePhone.size() != 11)
    {
        errMsg->setText(tr("手机号格式错误"));
        ui->verticalLayout_err->addWidget(errMsg);
        ui->lineEdit_Phone->clear();
        ui->lineEdit_Phone->setFocus();
        return;
    }
    for (i = userInfoList.begin(); i < userInfoList.end(); i++)
    {
        if (mobilePhone == i->getMobilePhone())
        {
            QMessageBox::warning(this, "warning", tr("该手机号已注册"), QMessageBox::Yes);
            ui->lineEdit_Phone->clear();
            ui->lineEdit_Phone->setFocus();
            return;
        }
    }
    if (password.size() == 0)
    {
        errMsg->setText(tr("密码不能为空"));
        ui->verticalLayout_err->addWidget(errMsg);
        ui->lineEdit_Password->setFocus();
        return;
    }
    if (password != confirmPsw)
    {
        errMsg->setText(tr("两次输入密码不一致"));
        ui->verticalLayout_err->addWidget(errMsg);
        ui->lineEdit_Password->clear();
        ui->lineEdit_ConfirmPsw->clear();
        ui->lineEdit_Password->setFocus();
        return;
    }
    //存入用户数据
    User signupItem(-1, username, password, mobilePhone, level);//还有问题，存入数据库的不是全部信息
    userInfoList.push_back(signupItem);
    QMessageBox::information(this, tr("提示"), tr("注册成功"), QMessageBox::Yes);
    close();
}

void Signupdlg::on_btnQuit_clicked()
{
    close();
}
