/**********************************************************************************************************************
【文件名】                                  mainwindow.cpp
【功能模块和目的】                            MainWindow类中成员函数的实现, 界面首页，可切换到其他界面
【开发者及日期】                             门恺文2019.7.23
【更改记录】
**********************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include "book.h"
#include "employmentdlg.h"
#include "logindlg.h"
#include "personalmainwindow.h"
#include "signupdlg.h"
#include "infomaintaindlg.h"
#include "depositdlg.h"
#include "newmissiondlg.h"

/***********************************************************************************************************************
【函数名称】                                 MainWindow()
【函数功能】                                 类MainWindow的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.23
【更改记录】
***********************************************************************************************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //初始化用户名和用户编号
    Username = "";
    userCode = -1;

    //初始化欢迎标签
    if (loginMsg != nullptr)
    {
        delete loginMsg;
        loginMsg = nullptr;
    }
    loginMsg = new QLabel;
    QFont font("ADMUI3Lg", 15,50);
    loginMsg->setFont(font);
    loginMsg->setText(tr("您好，由此登录"));
    ui->welcomeLayout->addWidget(loginMsg);
}

/***********************************************************************************************************************
【函数名称】                                 ~MainWindow()
【函数功能】                                 类MainWindow的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

MainWindow::~MainWindow()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_btnLogin_clicked()
【函数功能】                                 登录槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_btnLogin_clicked()
{
    if (userCode != -1)
    {
        //每个用户在登出后其他用户才可登录
        QMessageBox::warning(this, tr("warning"), tr("您需先登出才可重新登录"), QMessageBox::Ok);
        return;
    }
    Logindlg* login = new Logindlg(this);
    login->exec();
    //获取成功登录的用户编号
    userCode = login->getUserCode();
    //根据用户设置界面
    if (userCode != -1)
    {
        Username = login->getUsername();
        loginMsg->setText(tr("欢迎！") + Username);
        ui->welcomeLayout->addWidget(loginMsg);

        QString avatar = userList[userCode].getSAvatar();
        QImage* img = new QImage;
        if (!img->load(avatar))
        {
            //头像未能成功加载
            ui->labAvatar->setText(tr("图像加载失败"));
            delete img;
        }
        else {
            int height = ui->labAvatar->height();
            int width = ui->labAvatar->width();
            ui->labAvatar->setPixmap(QPixmap::fromImage(img->scaled(width, height,
                                                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        }
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_btnRegister_clicked()
【函数功能】                                 注册槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_btnRegister_clicked()
{
    //进入注册界面
    Signupdlg* signup = new Signupdlg(this);
    signup->exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEmployment_triggered()
【函数功能】                                 用户进入应聘的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_actionemployment_triggered()
{
    //进入应聘界面
    Employmentdlg* employee = new Employmentdlg(this);
    employee->exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEnter_triggered()
【函数功能】                                 用户进入图书主页的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_actionEnter_triggered()
{
    //进入图书首页
    Book* book = new Book;
    book->setUsername(Username);
    book->setUserCode(userCode);
    book->show();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEnter_3_Maintaince_triggered()
【函数功能】                                 用户进入个人中心的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_actionEnter_3_triggered()
{
    //与个人有关的均需先登录
    if (userCode == -1)
    {
        QMessageBox::information(this, tr("提示"), tr("您尚未登录，无法进入个人中心"), QMessageBox::Ok);
        return;
    }
    PersonalMainWindow* personal = new PersonalMainWindow;
    personal->setUserCode(userCode);
    personal->show();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionInfomation_triggered()
【函数功能】                                 用户进入信息维护的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_actionInfomation_triggered()
{
    //进入信息维护
    if (userCode == -1)
    {
        QMessageBox::information(this, tr("提示"), tr("您尚未登录，无法进行信息维护"), QMessageBox::Ok);
        return;
    }
    InfoMaintaindlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionInfo_maintaince_triggered()
【函数功能】                                 用户进入充值的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_actionDeposit_triggered()
{
    //进入充值
    if (userCode == -1)
    {
        QMessageBox::information(this, tr("提示"), tr("您尚未登录，无法进行充值"), QMessageBox::Ok);
        return;
    }
    Depositdlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数，并可改变页面性质
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::setUserCode(int value)
{
    userCode = value;

    if (userCode != -1)
    {
        //获取userCode后设置界面，以保证实时更新
        Username = userList[userCode].getUserName();
        loginMsg->setText(tr("欢迎！") + Username);
        ui->welcomeLayout->addWidget(loginMsg);

        QString avatar = userList[userCode].getSAvatar();
        QImage* img = new QImage;
        if (!img->load(avatar))
        {
            ui->labAvatar->setText(tr("图像加载失败"));
            delete img;
        }
        else {
            int height = ui->labAvatar->height();
            int width = ui->labAvatar->width();
            ui->labAvatar->setPixmap(QPixmap::fromImage(img->scaled(width, height,
                                                                    Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        }
    }
}

/***********************************************************************************************************************
【函数名称】                                 on_assignBtn_clicked()
【函数功能】                                 用户发布新任务点击按钮的槽函数，可使界面跳转至任务发布界面
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_assignBtn_clicked()
{
    //发布新任务
    if (userCode == -1)
    {
        QMessageBox::information(this, tr("提示"), tr("您需先登录才可发布任务"), QMessageBox::Yes);
        return;
    }
    newMissionDlg dlg;
    dlg.setUserCode(userCode);
    dlg.setUserName(Username);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 on_signoutBtn_clicked()
【函数功能】                                 登出槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void MainWindow::on_signoutBtn_clicked()
{
    //登出
    //设置为初始界面
    userCode = -1;
    Username = "";
    if (loginMsg != nullptr)
    {
        delete loginMsg;
        loginMsg = nullptr;
    }
    loginMsg = new QLabel;
    QFont font("ADMUI3Lg", 15,50);
    loginMsg->setFont(font);
    loginMsg->setText(tr("您好，由此登录"));
    ui->welcomeLayout->addWidget(loginMsg);
    ui->labAvatar->clear();
    QMessageBox::information(this, tr("提示"), tr("您已成功登出"), QMessageBox::Yes);
}
