/************************************************************************************************************************
【文件名】                                  msgdetaildlg.h
【模块功能和目的】                           MsgDetailDlg类声明，对应消息盒子中的消息细节
【开发者及日期】                             门恺文 2019.7.26
【更改记录】
************************************************************************************************************************/

#ifndef MSGDETAILDLG_H
#define MSGDETAILDLG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class MsgDetailDlg;
}

/************************************************************************************************************************
【类名】                                   MsgDetailDlg
【功能】                                   封装消息详情界面类所需要的数据和接口函数
【接口说明】                                一个构造函数和一个析构函数为基本组件
                                          数据成员获取和设置函数
【开发者及日期】                             门恺文2019.7.26
【更改记录】
************************************************************************************************************************/

class MsgDetailDlg : public QDialog
{
    Q_OBJECT

public:
    //构造和析构函数
    explicit MsgDetailDlg(QWidget *parent = nullptr);
    ~MsgDetailDlg();

    //任务编号设置函数
    void setMsgId(int value);

    //发送者姓名设置函数
    void setSenderName(const QString &value);

private:
    Ui::MsgDetailDlg *ui;
    int msgId;
    QString senderName;
    QList<MsgBox>& msgList = Database::msgList;
};

#endif // MSGDETAILDLG_H
