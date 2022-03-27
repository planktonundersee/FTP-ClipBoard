#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QUrl>
#include <QFile>
#include <QJsonObject>
#include <QWidget>
#include <iostream>
#include <QKeyEvent>
#include <QFileInfo>
#include <QTextCodec>
#include <QClipboard>
#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "network_class/network_class.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

signals:

    void threadStatus(bool Status);

public:
    static QString convert2UTF8(const QString &str, const QString &charType = "GBK");

    QUrl *setUrl();

    QUrl setUrl(bool point);

    void keyPressEvent(QKeyEvent *event) override;

    void addListWidget();

    void delListWidget();

    void insertListWidget(const QString &input, int row);

    void refreshListWidget();

    Network_Class *getInstance();

    void changeUI();

private slots:

    void hideUI();

    void showUI();

    void on_pushButton_clicked(bool checked);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void setText();

private:
    QUrl *m_Url{};                             //Url
    Ui::MainWindow *m_ui;                   //UI对象
    QNetworkReply *m_Reply{};               //网络应答
    Network_Class *m_Network{};               //网络上下载
    QClipboard *m_ClipBoard{};              //获取系统粘贴板
    QFile *m_File{};                        //用于读取配置文件
    //QNetworkAccessManager *m_Manager{};   //网络管理；发请求
    QJsonObject m_JsonObj;                  //读取和解析配置文件
    std::map<int, std::string> *m_record{};    //用于管理粘贴板的历史记录
    bool m_DownloadFlag{};                  //
    bool m_UploadFlag{};                    //
    bool m_Hide_UI;                         //
    unsigned int m_ReconnectTimes;          //重连次数
};

#endif // MAINWINDOW_H
