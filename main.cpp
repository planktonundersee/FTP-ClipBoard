#include "mainwindow/mainwindow.h"

#include <QApplication>

#include "KeyBoard_Mouse_Hook/KeyBoard_Mouse_Hook.h"

int main(int argc, char *argv[])
{
    qDebug()<<"the number of parameter is :" << argc ;
    for (int i = 0; i < argc ; ++i)
    {
        qDebug()<< "\n" << "argv is : " << argv[i];
    }
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}
