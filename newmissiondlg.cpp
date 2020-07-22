/**********************************************************************************************************************
【文件名】                                  newmissiondlg.cpp
【功能模块和目的】                            newMissionDlg类中成员函数的实现, 包括槽函数、接口函数,完成界面设置
【开发者及日期】                             门恺文2019.7.24
【更改记录】
**********************************************************************************************************************/

#include "newmissiondlg.h"
#include "ui_newmissiondlg.h"
#include <QDateTime>

/***********************************************************************************************************************
【函数名称】                                 newMissionDlg()
【函数功能】                                 类newMissionDlg的构造函数，在创建对象时被调用
【参数】                                    QWidget *parent，输入参数
【返回值】                                   无
【开发者及日期】                              门恺文 2019.7.24
【更改记录】
***********************************************************************************************************************/

newMissionDlg::newMissionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newMissionDlg)
{
    ui->setupUi(this);

    vari = 0;

    //设置日期的均不可直接输入，需要在日历上选择
    ui->lineEditFrom->setFocusPolicy(Qt::NoFocus);
    ui->lineEditTo->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
}

/***********************************************************************************************************************
【函数名称】                                 ~newMissionDlg()
【函数功能】                                 类newMissionDlg的析构函数，在对象被销毁时调用
【参数】                                    ui
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

newMissionDlg::~newMissionDlg()
{
    delete ui;
}

/***********************************************************************************************************************
【函数名称】                                 setUsername()
【函数功能】                                 成员Username的设置函数
【参数】                                     Username, QString, 输入参数
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void newMissionDlg::setUserName(const QString &value)
{
    userName = value;
}

/***********************************************************************************************************************
【函数名称】                                 on_addBtn_clicked()
【函数功能】                                 添加译文语言槽函数，用户可通过此函数添加语言
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void newMissionDlg::on_addBtn_clicked()
{
    if (ui->lineEditTrans->text().trimmed().isEmpty())
    {
        //添加译文不得为空
        QMessageBox::information(this, tr("提示"), tr("请先输入目标译文"), QMessageBox::Yes);
        ui->lineEditTrans->setFocus();
        return;
    }
    goal.push_back(ui->lineEditTrans->text().trimmed());
    vari = goal.size();
    QMessageBox::information(this, tr("提示"), tr("已成功添加"), QMessageBox::Yes);
    ui->lineEditTrans->clear();
    ui->lineEditTrans->setFocus();
}

/***********************************************************************************************************************
【函数名称】                                 on_calendarFrom_selectionChanged()
【函数功能】                                 起始日期变更槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void newMissionDlg::on_calendarFrom_selectionChanged()
{
    //获取起始日期
    QDate start = ui->calendarFrom->selectedDate();
    QString startDate = start.toString("yyyy-MM-dd");
    ui->lineEditFrom->setText(startDate);
}

/***********************************************************************************************************************
【函数名称】                                 on_calendarTo_selectionChanged()
【函数功能】                                 截止日期变更槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void newMissionDlg::on_calendarTo_selectionChanged()
{
    //获取截止日期
    QDate end = ui->calendarTo->selectedDate();
    QString endDate = end.toString("yyyy-MM-dd");
    ui->lineEditTo->setText(endDate);
}

/***********************************************************************************************************************
【函数名称】                                 on_finishBtn_clicked()
【函数功能】                                 提交新任务槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void newMissionDlg::on_finishBtn_clicked()
{
    //标题不得为空
    if (ui->lineEditTitle->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入任务标题"), QMessageBox::Ok);
        ui->lineEditTitle->setFocus();
        return;
    }
    //简介不得为空
    if (ui->plainTextEditDesc->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, tr("warning"), tr("您尚未输入任务简介"), QMessageBox::Ok);
        ui->plainTextEditDesc->setFocus();
        return;
    }
    //翻译内容不得为空
    if (ui->plainTextEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, tr("warning"), tr("您尚未提交翻译内容"), QMessageBox::Ok);
        ui->plainTextEdit->setFocus();
        return;
    }
    //负责人报名截止日期不得为空
    if (ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请指定负责人报名截止日期"), QMessageBox::Ok);
        return;
    }
    //检测负责人截止日期是否合法
    if (ui->lineEdit->text() < QDate::currentDate().toString("yyyy-MM-dd"))
    {
        QMessageBox::warning(this, "warning", tr("负责人报名截止日期不得早于今日"), QMessageBox::Yes);
        ui->lineEdit->clear();
        return;
    }
    //金额不得为空
    if (ui->lineEditReward->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请指定任务金额"), QMessageBox::Ok);
        ui->lineEditReward->setFocus();
        return;
    }
    //金额不得小于0
    if (ui->lineEditReward->text().toInt() <= 0)
    {
        QMessageBox::warning(this, "warning", tr("任务金额需为正数"), QMessageBox::Ok);
        ui->lineEditReward->clear();
        ui->lineEditReward->setFocus();
        return;
    }
    //开始日期不得为空
    if (ui->lineEditFrom->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入开始日期"), QMessageBox::Ok);
        return;
    }
    //结束日期不得为空
    if (ui->lineEditTo->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入结束日期"), QMessageBox::Ok);
        return;
    }
    //结束日期不可早于起始日期
    if (ui->lineEditFrom->text() > ui->lineEditTo->text())
    {
        QMessageBox::warning(this, tr("warning"), tr("结束日期不得早于开始日期"), QMessageBox::Ok);
        ui->lineEditFrom->clear();
        ui->lineEditTo->clear();
        return;
    }
    //截止日期不得早于今日
    if (ui->lineEditTo->text() < QDate::currentDate().toString("yyyy-MM-dd"))
    {
        QMessageBox::warning(this, "warning", tr("任务截止日期不得早于今日"), QMessageBox::Yes);
        ui->lineEditTo->clear();
        return;
    }
    //原文语言不可为空
    if (ui->lineEditOri->text().isEmpty())
    {
        QMessageBox::information(this, tr("提示"), tr("请输入原文语言"), QMessageBox::Ok);
        ui->lineEditOri->setFocus();
        return;
    }
    //译文语言不可为空
    if ((ui->lineEditFrom->text().isEmpty()) && (goal.size() == 0))
    {
        QMessageBox::information(this, tr("提示"), tr("请输入译文语言"), QMessageBox::Ok);
        ui->lineEditTrans->setFocus();
        return;
    }
    //添加语言
    if (!ui->lineEditTrans->text().isEmpty())
    {
        goal.push_back(ui->lineEditTrans->text().trimmed());
        vari = goal.size();
    }
    //删去不必要的空格，更加安全
    QString orign = ui->lineEditOri->text().trimmed();
    Translanguage trans(goal, orign, vari);
    QString title = ui->lineEditTitle->text().trimmed();
    QString content = ui->plainTextEdit->toPlainText().trimmed();
    QString desc = ui->plainTextEditDesc->toPlainText().trimmed();
    QString startDate = ui->lineEditFrom->text();
    QString endDate = ui->lineEditTo->text();
    QString pncpDDL = ui->lineEdit->text();
    double reward = ui->lineEditReward->text().toDouble();
    //添加任务
    Assignment assign(trans, title, content, desc, startDate, endDate, 0, 0, pncpDDL,
                      "", "", reward, RECUITING_PRICIPAL, -1);
    assignList.push_back(assign);
    //添加发布者任务
    AssignPublisher publisher(trans, title, content, desc, startDate, endDate, 0, 0, pncpDDL,
                              "", "", reward, RECUITING_PRICIPAL, assign.getAssignId(), userName, userCode);
    pubList.push_back(publisher);
    //给发布者发消息
    MsgBox msg(userCode, -1, tr("任务发布通知"), tr("任务")+title+tr("已成功发布"));
    msgList.push_back(msg);

    QMessageBox::information(this, tr("提示"), tr("任务成功发布"), QMessageBox::Yes);
    accept();
}

/***********************************************************************************************************************
【函数名称】                                 on_calendarPncp_selectionChanged()
【函数功能】                                 负责人报名截止日期变更槽函数
【参数】                                    无
【返回值】                                   无
【开发者及日期】                              门恺文2019.7.24
【更改记录】
***********************************************************************************************************************/

void newMissionDlg::on_calendarPncp_selectionChanged()
{
    //选择负责人报名截止日期
    QDate pncp = ui->calendarPncp->selectedDate();
    QString pncpDDL = pncp.toString("yyyy-MM-dd");
    ui->lineEdit->setText(pncpDDL);
}

void newMissionDlg::setUserCode(int value)
{
    userCode = value;
}
