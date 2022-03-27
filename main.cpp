#include "mainwindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication l_application(argc, argv);
    MainWindow l_window;
    l_window.show();
    return l_application.exec();
}
