#include "mainwindow/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();
}
