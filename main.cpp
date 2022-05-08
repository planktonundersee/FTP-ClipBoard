#include <QApplication>
#include "mainwindow/mainwindow.h"

//TODO: MIMEdata
//TODO: 读取配置文件
//TODO: 读取文件路径

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow::instance()->show();
    return QApplication::exec();
}
