/**********************************************************************************************************************
【文件名】                                  msgboxdlg.cpp
【功能模块和目的】                            MsgBoxDlg类中成员函数的实现, 包括槽函数、接口函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
**********************************************************************************************************************/

#include "msgboxdlg.h"
#include "ui_msgboxdlg.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include "msgdetaildlg.h"

/***********************************************************************************************************************
【函数名称】                                 MsgBoxDlg()
【函数功能】                                 类MsgBoxDlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.26
【更改记录】
***********************************************************************************************************************/

MsgBoxDlg::MsgBoxDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MsgBoxDlg)
{
    ui->setupUi(this);

    //将tableView双击信号与进入消息槽函数连接
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex&)),
            this, SLOT(enterDetail(const QModelIndex&)));
}


/***********************************************************************************************************************
【函数名称】                                 ~MsgBoxDlg()
【函数功能】                                 类MsgBoxDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

MsgBoxDlg::~MsgBoxDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 enterDetail()
【函数功能】                                 进入消息详情槽函数
【参数】                                    QModelIndex &index，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void MsgBoxDlg::enterDetail(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *detail = const_cast<QAbstractItemModel *>(index.model());
    //获取消息编号
    msgId = detail->data(detail->index(row, 0 ,QModelIndex())).toInt();
    senderCode = msgList[msgId].iSenderCode();
    QString senderName;
    //senderCode为-1时，规定为系统发出的消息
    if (senderCode == -1)
    {
        senderName = tr("系统消息");
    }
    else {
        senderName = userInfoList[senderCode].getUserName();
    }
    //进入消息详情
    MsgDetailDlg dlg;
    dlg.setSenderName(senderName);
    dlg.setMsgId(msgId);
    dlg.exec();
}

/***********************************************************************************************************************
【函数名称】                                 setUserCode()
【函数功能】                                 成员userCode的设置函数，改变页面，使页面对应特定用户
【参数】                                     value, int, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.26
【更改记录】
***********************************************************************************************************************/

void MsgBoxDlg::setUserCode(int value)
{
    userCode = value;

    //获取用户编号后设置消息盒子界面
    ui->labFront->setText(userInfoList[userCode].getUserName() + tr(" 的消息盒子"));
    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("消息序号")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("发送者序号")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("发送者")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("主题")));
    model->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("查看详情")));
    QList<MsgBox>::iterator i;
    int row = 0;
    for (i = msgList.begin(); i < msgList.end(); i++)
    {
        if (i->iUserCode() == userCode)
        {
            QString senderName;
            if (i->iSenderCode() == -1)
            {
                senderName = tr("系统消息");
            }
            else {
                senderName = userInfoList[i->iSenderCode()].getUserName();
            }
            model->setItem(row, 0, new QStandardItem(QString::number(i->getIMsgId())));
            model->setItem(row, 1, new QStandardItem(QString::number(i->iSenderCode())));
            model->setItem(row, 2, new QStandardItem(senderName));
            model->setItem(row, 3, new QStandardItem(i->sTheme()));
            model->setItem(row, 4, new QStandardItem(tr("进入")));
            row++;
        }
    }
    ui->tableView->setShowGrid(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setModel(model);
}
