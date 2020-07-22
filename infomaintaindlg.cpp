/**********************************************************************************************************************
【文件名】                                  infomaintaindlg.cpp
【功能模块和目的】                            InfoMaintaindlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.24
【更改记录】
**********************************************************************************************************************/

#include "infomaintaindlg.h"
#include "ui_infomaintaindlg.h"
#include <QMessageBox>
#include "depositdlg.h"

/***********************************************************************************************************************
【函数名称】                                 InfoMaintaindlg()
【函数功能】                                 类InfoMaintaindlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.24
【更改记录】
***********************************************************************************************************************/

InfoMaintaindlg::InfoMaintaindlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoMaintaindlg)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~InfoMaintaindlg()
【函数功能】                                 类InfoMaintaindlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

InfoMaintaindlg::~InfoMaintaindlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_feedbackBtn_clicked()
【函数功能】                                 提交修改信息的槽函数
【参数】                                     无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void InfoMaintaindlg::on_acceptBtn_clicked()
{
    //获取界面上的数据
    //身份证号填写后不得修改
    QString id;
    if (userInfoList[userCode].getId().isEmpty())
    {
        id = ui->lineEditId->text();
    }
    else
    {
        ui->lineEditId->setFocusPolicy(Qt::NoFocus);
        id = userInfoList[userCode].getId();
    }
    QString username = ui->lineEditUsername->text();
    QString phone = ui->lineEditPhone->text();
    QString name = ui->lineEditName->text();
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();
    QString comfirm = ui->lineEditComfirm->text();

    for (QList<User>::iterator i = userInfoList.begin(); i < userInfoList.end(); i++)
    {
        //用户名,手机号，邮箱不可与他人重复，但可不改
        if ((i->getUserName() == username) && (username != userInfoList[userCode].getUserName()))
        {
            QMessageBox::warning(this, "warning", tr("该用户名已存在"), QMessageBox::Yes);
            ui->lineEditUsername->clear();
            ui->lineEditUsername->setFocus();
            return;
        }
        if ((i->getMobilePhone() == phone) && (phone != userInfoList[userCode].getMobilePhone()))
        {
            QMessageBox::warning(this, "warning", tr("该手机号已注册"), QMessageBox::Yes);
            ui->lineEditPhone->clear();
            ui->lineEditPhone->setFocus();
            return;
        }
        if ((i->getEmail() == email) && (email != userInfoList[userCode].getEmail()))
        {
            QMessageBox::warning(this, "warning", tr("该邮箱已注册"), QMessageBox::Yes);
            ui->lineEditEmail->clear();
            ui->lineEditEmail->setFocus();
            return;
        }
    }
    //用户名，手机号，密码，确认密码为必填项
    if ((username.isEmpty()) || (phone.isEmpty()) || (password.isEmpty()) || (comfirm.isEmpty()))
    {
        QMessageBox::warning(this, "warning", tr("您有信息尚未填写"), QMessageBox::Yes);
        return;
    }
    if((!id.isEmpty()) && (id.length() != 18))
    {
        QMessageBox::warning(this, tr("warning"), tr("身份证号格式错误"), QMessageBox::Ok);
        return;
    }
    //密码与确认密码需一致
    if (password != comfirm)
    {
        QMessageBox::warning(this, "warning", tr("密码与确认密码不一致"), QMessageBox::Yes);
        ui->lineEditComfirm->clear();
        ui->lineEditComfirm->setFocus();
        return;
    }
    //更改信息
    userInfoList[userCode].setId(id);
    userInfoList[userCode].setName(name);
    userInfoList[userCode].setEmail(email);
    userInfoList[userCode].setPassword(password);
    userInfoList[userCode].setUserName(username);
    userInfoList[userCode].setMobilePhone(phone);

    //更改成功
    QMessageBox::information(this, tr("提示"), tr("更改信息成功"), QMessageBox::Yes);
    accept();
}

/***********************************************************************************************************************
【函数名称】                                 on_depositBtn_clicked()
【函数功能】                                 用户进入充值的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void InfoMaintaindlg::on_depositBtn_clicked()
{
    //进入充值界面
    Depositdlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
    //实时显示余额变化
    ui->lineEditBalance->setText(QString::number(userInfoList[userCode].getBalance()));
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void InfoMaintaindlg::setUserCode(int value)
{
    userCode = value;

    //获取用户编号后初始化
    ui->lineEditUsername->setText(userInfoList[userCode].getUserName());
    ui->lineEditId->setText(userInfoList[userCode].getId());
    ui->lineEditPhone->setText(userInfoList[userCode].getMobilePhone());
    ui->lineEditPoints->setText(QString::number(userInfoList[userCode].getPoint()));
    ui->lineEditBalance->setText(QString::number(userInfoList[userCode].getBalance()));
    ui->lineEditPassword->setText(userInfoList[userCode].getPassword());
    ui->lineEditComfirm->setText(userInfoList[userCode].getPassword());
    ui->lineEditName->setText(userInfoList[userCode].getName());
    ui->lineEditEmail->setText(userInfoList[userCode].getEmail());

    //身份证号码不可更改
    if (!userInfoList[userCode].getId().isEmpty())
    {
        ui->lineEditId->setFocusPolicy(Qt::NoFocus);
    }
    //显示头像
    QString avatar = userInfoList[userCode].getSAvatar();
    QImage* img = new QImage;
    if (!img->load(avatar))
    {
        ui->labAvatar->setText(tr("头像加载失败"));
        delete img;
    }
    else {
        int height = ui->labAvatar->height();
        int width = ui->labAvatar->width();
        ui->labAvatar->setPixmap(QPixmap::fromImage(img->scaled(width, height,
                                                                Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_avatarBtn_clicked()
【函数功能】                                 更改头像的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void InfoMaintaindlg::on_avatarBtn_clicked()
{
    QString avatar = ui->avatarlineEdit->text();
    userInfoList[userCode].setSAvatar(avatar);
    QImage* img = new QImage;
    if (!img->load(avatar))
    {
        //没能加载出头像的情况
        ui->labAvatar->setText(tr("头像加载失败"));
        delete img;
    }
    else {
        int height = ui->labAvatar->height();
        int width = ui->labAvatar->width();
        ui->labAvatar->setPixmap(QPixmap::fromImage(img->scaled(width, height,
                                                                Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    }
}
