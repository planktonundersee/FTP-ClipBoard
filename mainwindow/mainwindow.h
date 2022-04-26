#ifndef FTP_CLIPBOARD_MAINWINDOW_H
#define FTP_CLIPBOARD_MAINWINDOW_H

#include <string>

#include <QUrl>
#include <QFile>
#include <QJsonObject>
#include <QWidget>
#include <iostream>
#include <QKeyEvent>
#include <QFileInfo>
#include <QClipboard>
#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "Public_Func/Pubilc_Func.h"
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

    template<typename T>
    void sendSignal(emit_Bundle<T> );

public:

    QUrl *setUrl();

    QUrl setUrl(bool point);

    void keyPressEvent(QKeyEvent *event) override;

    void addListWidget();

    void delListWidget();

    void insertListWidget(const QString &input, int row);

    void refreshListWidget();

    networkClass *getInstance();

    void changeUi();

    void hideUi();

    void showUi();

private slots:


    void on_pushButton_clicked(bool checked);

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    template<typename T>
    void getRcvBuf(T);

private:
    void setText();

private:
    QUrl *m_Url{};                          //Url
    QFile *m_File{};                        //用于读取配置文件
    Ui::MainWindow *m_ui;                   //UI对象
    QNetworkReply *m_Reply{};               //网络应答
    networkClass *m_Network{};             //网络上下载
    QClipboard *m_ClipBoard{};              //获取系统粘贴板
    QJsonObject m_JsonObj;                  //读取和解析配置文件
    bool m_Hide_UI;                         //
    bool m_DownloadFlag{};                  //
    bool m_UploadFlag{};                    //
    unsigned int m_ReconnectTimes;          //重连次数
    std::map<int, std::string> *m_record{}; //用于管理粘贴板的历史记录
};

#endif // FTP_CLIPBOARD_MAINWINDOW_H
