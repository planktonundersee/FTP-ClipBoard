#include <QApplication>
#include "mainwindow/mainwindow.h"
#include "libiohook/GlobalParameter.h"
//TODO: MIMEdata
//TODO: 读取配置文件

int main(int argc, char *argv[])
{
    //TODO: 读取文件路径
    QApplication application(argc, argv);
    MainWindow::instance()->show();
    return QApplication::exec();
}
