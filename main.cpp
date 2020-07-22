/**********************************************************************************************************************
【文件名】                                  main.cpp
【功能模块和目的】                            程序主函数，执行的起点，数据导入和导出函数的使用位置, 含有C++异常处理机制，预防系统崩溃
【开发者及日期】                             门恺文2019.7.24
【更改记录】
**********************************************************************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QMessageBox>
#include "database.h"


int main(int argc, char *argv[])
{
    //C++异常处理机制
    try
    {
        QApplication a(argc, argv);
        //设置中文字体
        QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());

        //从数据库导出数据
        QSqlDatabase db = Database::loadData();

        MainWindow w;
        w.show();

        //设置ret，保留a运行返回值
        int ret = a.exec();

        //向数据库导入数据
        Database::saveData(db);

        return ret;

    } catch (std::exception e) {
        QMessageBox::critical(nullptr, "异常", e.what(), QMessageBox::YesAll);
    }
    //若异常则返回值为1
    return 1;
}


