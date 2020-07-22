/**********************************************************************************************************************
【文件名】                                  employmentdlg.cpp
【功能模块和目的】                            Employmentdlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
**********************************************************************************************************************/

#include "employmentdlg.h"
#include "ui_employmentdlg.h"
#include "confirmdlg.h"

/***********************************************************************************************************************
【函数名称】                                 Employmentdlg()
【函数功能】                                 类Employmentdlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.26
【更改记录】
***********************************************************************************************************************/

Employmentdlg::Employmentdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employmentdlg)
{
    ui->setupUi(this);

}

/***********************************************************************************************************************
【函数名称】                                 ~Employmentdlg()
【函数功能】                                 类Employmentdlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

Employmentdlg::~Employmentdlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_confirmBtn_clicked()
【函数功能】                                 确认应聘的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void Employmentdlg::on_confirmBtn_clicked()
{
    QString name = ui->lineEditName->text();
    QString id = ui->lineEditId->text();
    QString phone = ui->lineEditPhone->text();
    QString email = ui->lineEditEmail->text();
    QString nickName = ui->lineEditNickName->text();
    QString CV = ui->plainTextEditCV->toPlainText();

    //真实姓名为必填项
    if (name.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写真实姓名"), QMessageBox::Ok);
        ui->lineEditName->setFocus();
        return;
    }
    //身份证号为必填项
    if (id.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写身份证号"), QMessageBox::Ok);
        ui->lineEditId->setFocus();
        return;
    }
    //检测身份证号是否合法
    if (id.size() != 18)
    {
        QMessageBox::warning(this, "warning", tr("身份证号格式错误"), QMessageBox::Ok);
        ui->lineEditId->clear();
        ui->lineEditId->setFocus();
        return;
    }
    //手机号码为必填项
    if (phone.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写手机号码"), QMessageBox::Ok);
        ui->lineEditPhone->setFocus();
        return;
    }
    //检测手机号格式是否合法
    if (phone.size() != 11)
    {
        QMessageBox::warning(this, "warning", tr("手机号格式错误"), QMessageBox::Yes);
        ui->lineEditPhone->clear();
        ui->lineEditPhone->setFocus();
        return;
    }
    //邮箱为必填项
    if (email.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写邮箱"), QMessageBox::Ok);
        ui->lineEditEmail->setFocus();
        return;
    }
    //昵称为必填项
    if (nickName.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写昵称"), QMessageBox::Ok);
        ui->lineEditNickName->setFocus();
        return;
    }
    //简历为必填项
    if (CV.isEmpty())
    {
        QMessageBox::warning(this, "warning", tr("请填写简历"), QMessageBox::Ok);
        ui->plainTextEditCV->setFocus();
        return;
    }
    //应聘前再次确认
    ConfirmDlg dlg;
    QString content = tr("是否确定提交应聘材料？");
    dlg.setContent(content);
    if (dlg.exec() == QDialog::Accepted)
    {
        //工作人员信息录入
        Platform platform(name, phone, email, id, CV);
        platformList.push_back(platform);
        QMessageBox::information(this, tr("提示"), tr("您已成功应聘工作人员"), QMessageBox::Yes);
        accept();
    }
}
