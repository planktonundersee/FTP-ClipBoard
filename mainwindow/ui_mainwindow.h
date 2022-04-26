/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FTP_CLIPBOARD_UI_MAINWINDOW_H
#define FTP_CLIPBOARD_UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *pawdLabel;
    QLineEdit *pawdEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *addrLabel;
    QLineEdit *addrEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *portLabel;
    QLineEdit *portEdit;
    QListWidget *listWidget;
    QPushButton *pushButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow) {
            if (MainWindow->objectName().isEmpty()) {
                    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
            }
            MainWindow->resize(400, 600);
            MainWindow->setMinimumSize(QSize(400, 600));
            MainWindow->setMaximumSize(QSize(400, 600));
            centralwidget = new QWidget(MainWindow);
            centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
            verticalLayout_2 = new QVBoxLayout(centralwidget);
            verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
            verticalLayout = new QVBoxLayout();
            verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
            horizontalLayout = new QHBoxLayout();
            horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
            nameLabel = new QLabel(centralwidget);
            nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

            horizontalLayout->addWidget(nameLabel);

            nameEdit = new QLineEdit(centralwidget);
            nameEdit->setObjectName(QString::fromUtf8("nameEdit"));

            horizontalLayout->addWidget(nameEdit);


            verticalLayout->addLayout(horizontalLayout);

            horizontalLayout_2 = new QHBoxLayout();
            horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
            pawdLabel = new QLabel(centralwidget);
            pawdLabel->setObjectName(QString::fromUtf8("pawdLabel"));

            horizontalLayout_2->addWidget(pawdLabel);

            pawdEdit = new QLineEdit(centralwidget);
            pawdEdit->setObjectName(QString::fromUtf8("pawdEdit"));

            horizontalLayout_2->addWidget(pawdEdit);


            verticalLayout->addLayout(horizontalLayout_2);

            horizontalLayout_3 = new QHBoxLayout();
            horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
            addrLabel = new QLabel(centralwidget);
            addrLabel->setObjectName(QString::fromUtf8("addrLabel"));

            horizontalLayout_3->addWidget(addrLabel);

            addrEdit = new QLineEdit(centralwidget);
            addrEdit->setObjectName(QString::fromUtf8("addrEdit"));

            horizontalLayout_3->addWidget(addrEdit);


            verticalLayout->addLayout(horizontalLayout_3);

            horizontalLayout_4 = new QHBoxLayout();
            horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
            portLabel = new QLabel(centralwidget);
            portLabel->setObjectName(QString::fromUtf8("portLabel"));

            horizontalLayout_4->addWidget(portLabel);

            portEdit = new QLineEdit(centralwidget);
            portEdit->setObjectName(QString::fromUtf8("portEdit"));

            horizontalLayout_4->addWidget(portEdit);


            verticalLayout->addLayout(horizontalLayout_4);

            listWidget = new QListWidget(centralwidget);
            listWidget->setObjectName(QString::fromUtf8("listWidget"));

            verticalLayout->addWidget(listWidget);

            pushButton = new QPushButton(centralwidget);
            pushButton->setObjectName(QString::fromUtf8("pushButton"));
            pushButton->setCheckable(true);

            verticalLayout->addWidget(pushButton);


            verticalLayout_2->addLayout(verticalLayout);

            MainWindow->setCentralWidget(centralwidget);
            statusbar = new QStatusBar(MainWindow);
            statusbar->setObjectName(QString::fromUtf8("statusbar"));
            MainWindow->setStatusBar(statusbar);

            retranslateUi(MainWindow);

            QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow) const {
            MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
            nameLabel->setText(QCoreApplication::translate("MainWindow", "\350\264\246\345\217\267 : ", nullptr));
            pawdLabel->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201 : ", nullptr));
            pawdEdit->setInputMask(QString());
            pawdEdit->setPlaceholderText(QString());
            addrLabel->setText(QCoreApplication::translate("MainWindow", "\345\234\260\345\235\200 : ", nullptr));
            portLabel->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243 : ", nullptr));
            pushButton->setText(QCoreApplication::translate("MainWindow", "\345\220\214\346\255\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow : public Ui_MainWindow {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // FTP_CLIPBOARD_UI_MAINWINDOW_H
