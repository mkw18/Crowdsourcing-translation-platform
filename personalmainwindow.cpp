/**********************************************************************************************************************
【文件名】                                  personalmainwindow.cpp
【功能模块和目的】                            PersonalMainWindow类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.23
【更改记录】
**********************************************************************************************************************/

#include "personalmainwindow.h"
#include "ui_personalmainwindow.h"
#include "infomaintaindlg.h"
#include "depositdlg.h"
#include "msgboxdlg.h"
#include <QTableView>
#include <QStandardItemModel>
#include "pubdlg.h"
#include "pncpdlg.h"
#include "transdlg.h"
#include "mainwindow.h"
#include "book.h"
#include "employmentdlg.h"

/***********************************************************************************************************************
【函数名称】                                 PersonalMainWindow()
【函数功能】                                 类PersonalMainWindow的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.23
【更改记录】
***********************************************************************************************************************/

PersonalMainWindow::PersonalMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PersonalMainWindow)
{
    ui->setupUi(this);
}

/***********************************************************************************************************************
【函数名称】                                 ~PersonalMainWindow()
【函数功能】                                 类PersonalMainWindow的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

PersonalMainWindow::~PersonalMainWindow()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 on_infoBtn_clicked()
【函数功能】                                 用户进入信息维护的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::on_infoBtn_clicked()
{
    InfoMaintaindlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
    //及时显示更改
    init();
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::setUserCode(int value)
{
    userCode = value;
    init();
}

/***********************************************************************************************************************
【函数名称】                                 on_depositBtn_clicked()
【函数功能】                                 用户进入充值的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::on_depositBtn_clicked()
{
    Depositdlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
    ui->labBalanceOutPut->setText(QString::number(userInfoList[userCode].getBalance()));
}

/***********************************************************************************************************************
【函数名称】                                 on_messageBtn_clicked()
【函数功能】                                 用户进入消息盒子的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::on_messageBtn_clicked()
{
    MsgBoxDlg dlg;
    dlg.setUserCode(userCode);
    dlg.exec();
    //及时显示更改
    init();
}

/***********************************************************************************************************************
【函数名称】                                 enterAssignment()
【函数功能】                                 用户进入个人任务的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::enterAssignment(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *assign = const_cast<QAbstractItemModel *>(index.model());
    //获取任务编号
    int assignId = assign->data(assign->index(row, 0 ,QModelIndex())).toInt();
    //获取用户角色，进入不同界面
    QString role = assign->data(assign->index(row, 2, QModelIndex())).toString();
    if (role == tr("发布者"))
    {
        PubDlg dlg;
        dlg.setPubCode(userCode);
        dlg.setAssignId(assignId);
        dlg.exec();
    }
    else if (role == tr("负责人"))
    {
        QList<AssignPrincipal>::iterator i;
        for (i = pncpList.begin(); i < pncpList.end(); i++)
        {
            if ((i->getAssignId() == assignId) && (i->getIPncpCode() == userCode) && (i->getBIsConfirmed() == true))
            {
                PncpDlg dlg;
                dlg.setPncpCode(userCode);
                int pncpId = i->getINum();
                dlg.setPncpId(pncpId);
                dlg.setAssignId(assignId);
                dlg.exec();
                break;
            }
        }
    }
    else if (role == tr("译者"))
    {
        QList<AssignTranslator>::iterator i;
        for (i = transList.begin(); i < transList.end(); i++)
        {
            if ((i->getAssignId() == assignId) && (i->getITransCode() == userCode) && (i->getETransState() != APPLYING))
            {
                TransDlg dlg;
                dlg.setTransCode(userCode);
                int transId = i->iTransId();
                dlg.setTransId(transId);
                dlg.setAssignId(assignId);
                dlg.exec();
                break;
            }
        }
    }
}

/***********************************************************************************************************************
【函数名称】                                 init()
【函数功能】                                 存放一些较大型和重复利用率高的操作
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::init()
{
    //设置界面
    ui->labCodeOutPut->setText(QString::number(userInfoList[userCode].getICode()));
    ui->labNameOutPut->setText(userInfoList[userCode].getName());
    ui->labEmailOutPut->setText(userInfoList[userCode].getEmail());
    ui->labUserOutPut->setText(userInfoList[userCode].getUserName());
    ui->labPhoneOutPut->setText(userInfoList[userCode].getMobilePhone());
    ui->plainTextEditLevelOutput->setPlainText(userInfoList[userCode].getSLanguageLevel());
    ui->labPointsOutPut->setText(QString::number(userInfoList[userCode].getPoint()));
    ui->labBalanceOutPut->setText(QString::number(userInfoList[userCode].getBalance()));

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

    //显示表格
    int row = 0;
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("序号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("标题")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("我的角色")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("任务状态")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("查看详情")));

    //按顺序显示任务列表
    //发布者
    QList<AssignPublisher>::iterator pub_i;
    for (pub_i = publisherList.begin(); pub_i < publisherList.end(); pub_i++)
    {
        if (pub_i->getIPublisherCode() == userCode)
        {
            QString status;
            switch (pub_i->getStatus())
            {
            case RECUITING_PRICIPAL:
            {
                status = tr("正在招募负责人");
                break;
            }
            case RECUITING_TRANSLATOR:
            {
                status = tr("正在招募译者");
                break;
            }
            case ON_TRANSLATING:
            {
                status = tr("正在翻译");
                break;
            }
            case TRANSLATION_FINISHED:
            {
                status = tr("翻译完成");
                break;
            }
            case ON_SHELF:
            {
                status= tr("已上架");
                break;
            }
            }
            model->setItem(row, 0, new QStandardItem(QString::number(pub_i->getAssignId())));
            model->setItem(row, 1, new QStandardItem(pub_i->getSTitle()));
            model->setItem(row, 2, new QStandardItem(tr("发布者")));
            model->setItem(row, 3, new QStandardItem(status));
            model->setItem(row, 4, new QStandardItem(tr("进入")));
            row++;
        }
    }

    //负责人
    QList<AssignPrincipal>::iterator pncp_i;
    for (pncp_i = pncpList.begin(); pncp_i < pncpList.end(); pncp_i++)
    {
        if ((pncp_i->getIPncpCode() == userCode) && (pncp_i->getBIsConfirmed()))
        {
            QString status;
            switch (pncp_i->getStatus())
            {
            case RECUITING_PRICIPAL:
            {
                status = tr("正在招募负责人");
                break;
            }
            case RECUITING_TRANSLATOR:
            {
                status = tr("正在招募译者");
                break;
            }
            case ON_TRANSLATING:
            {
                status = tr("正在翻译");
                break;
            }
            case TRANSLATION_FINISHED:
            {
                status = tr("翻译完成");
                break;
            }
            case ON_SHELF:
            {
                status= tr("已上架");
                break;
            }
            }
            model->setItem(row, 0, new QStandardItem(QString::number(pncp_i->getAssignId())));
            model->setItem(row, 1, new QStandardItem(pncp_i->getSTitle()));
            model->setItem(row, 2, new QStandardItem(tr("负责人")));
            model->setItem(row, 3, new QStandardItem(status));
            model->setItem(row, 4, new QStandardItem(tr("进入")));
            row++;
        }
    }

    //译者
    QList<AssignTranslator>::iterator trans_i;
    for (trans_i = transList.begin(); trans_i < transList.end(); trans_i++)
    {
        if ((trans_i->getITransCode() == userCode) && (trans_i->getETransState() != APPLYING))
        {
            QString status;
            switch (trans_i->getStatus())
            {
            case RECUITING_PRICIPAL:
            {
                status = tr("正在招募负责人");
                break;
            }
            case RECUITING_TRANSLATOR:
            {
                status = tr("正在招募译者");
                break;
            }
            case ON_TRANSLATING:
            {
                status = tr("正在翻译");
                break;
            }
            case TRANSLATION_FINISHED:
            {
                status = tr("翻译完成");
                break;
            }
            case ON_SHELF:
            {
                status= tr("已上架");
                break;
            }
            }
            model->setItem(row, 0, new QStandardItem(QString::number(trans_i->getAssignId())));
            model->setItem(row, 1, new QStandardItem(trans_i->getSTitle()));
            model->setItem(row, 2, new QStandardItem(tr("译者")));
            model->setItem(row, 3, new QStandardItem(status));
            model->setItem(row, 4, new QStandardItem(tr("进入")));
            row++;
        }
    }
    ui->tableView_Assignment->setShowGrid(true);
    ui->tableView_Assignment->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView_Assignment->setModel(model);

    //将信号与槽函数关联
    connect(ui->tableView_Assignment, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterAssignment(const QModelIndex&)));

}

/***********************************************************************************************************************
【函数名称】                                 on_actionEnter_triggered()
【函数功能】                                 用户进入首页的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::on_actionEnter_triggered()
{
    //进入主页
    MainWindow* mainwindow = new MainWindow;
    mainwindow->setUserCode(userCode);
    mainwindow->show();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEnter_2_triggered()
【函数功能】                                 用户进入图书主页的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::on_actionEnter_2_triggered()
{
    Book* book = new Book;
    book->setUsername(userInfoList[userCode].getUserName());
    book->setUserCode(userCode);
    book->show();
}

/***********************************************************************************************************************
【函数名称】                                 on_actionEmployment_triggered()
【函数功能】                                 用户进入应聘的槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.23
【更改记录】
***********************************************************************************************************************/

void PersonalMainWindow::on_actionEmployment_triggered()
{
    Employmentdlg* employee = new Employmentdlg(this);
    employee->exec();
}
