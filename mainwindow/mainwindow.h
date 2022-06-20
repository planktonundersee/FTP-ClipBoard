#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
#ifndef FTP_CLIPBOARD_MAINWINDOW_H
#define FTP_CLIPBOARD_MAINWINDOW_H

#include <string>

#include <QUrl>
#include <QFile>
#include <QWidget>
#include <iostream>
#include <QKeyEvent>
#include <QFileInfo>
#include <QClipboard>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "Public_Func/PublicFunc.h"
#include "network_class/network_class.h"
#include "KeyBoard_Mouse_Hook/KeyBoard_Mouse_Hook.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public Pubilc_Func{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

public slots:


signals:
    void threadStatus(bool Status);

    void sendSignal(emitBundle buf);


public:
    QUrl *setUrl();

    QUrl setUrl(bool point);

//    void keyPressEvent(QKeyEvent *event) override;

    void addListWidget();

    void delListWidget();

    void insertListWidget(const QString &input, int row);

    void refreshListWidget();

    void changeUi();

    void hideUi();

    void showUi();

    static MainWindow* instance();

private slots:
    void on_pushButton_clicked(bool checked);

    QString getRcvBuf(emitBundle &emitBundle);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void setText();

private:
    static MainWindow* m_mainWindow;
    KeyBoard_Mouse_Hook m_KBMH;             //全局监控类
    QUrl *m_Url{};                          //Url
    QFile *m_File{};                        //用于读取配置文件
    Ui::MainWindow *m_ui;                   //UI对象
    QNetworkReply *m_Reply{};               //网络应答
    QClipboard *m_ClipBoard{};              //获取系统粘贴板
    QJsonObject m_JsonObj;                  //读取和解析配置文件
    bool m_Hide_UI;                         //
    bool m_DownloadFlag{};                  //
    bool m_UploadFlag{};                    //
    unsigned int m_ReconnectTimes;          //重连次数
    std::map<int, std::string> *m_record{}; //用于管理粘贴板的历史记录
};

#endif // FTP_CLIPBOARD_MAINWINDOW_H

#pragma clang diagnostic pop