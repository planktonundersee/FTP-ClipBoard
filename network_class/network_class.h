#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H
#pragma clang diagnostic push
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "google-explicit-constructor"

#include <QUrl>
#include <QDebug>
#include <QThread>
#include <QClipboard>
#include <QByteArray>
#include <QMessageBox>
#include <QNetworkReply>
#include <QListWidgetItem>
#include <QNetworkAccessManager>

#include "file_class/file_class.h"

class networkClass : public QThread ,public Pubilc_Func
{
    Q_OBJECT

signals:
    void sendSignal(emitBundle& buf);
public:
    enum status {
        THREAD_START, THREAD_STOP
    };

    networkClass();

    networkClass(const QUrl &url);

    networkClass(QUrl *url);

    [[noreturn]] void run();

    //QString 上次到服务器

    void setUrl(const QUrl &url);

    void setUrl(QUrl *url);

public slots:
    QString getRcvBuf(emitBundle &emitBundle);

    bool uploadToServer();

    QString downloadFromServer();

    bool replyError(QNetworkReply::NetworkError);

    bool finishedOfUpload(QNetworkReply *ftpReply);

    static bool finishedOfDownload(QNetworkReply *ftpReply);

    void changeThreadStatus(bool status);

    bool clipBoardChange(bool status);

    QString getFtpContent();

private:
    QNetworkAccessManager *getInstance();

    bool send(const QString &sndStr2Serv, const QUrl &url);

    bool sync(const QUrl &url);

    bool isInit();



private:
    QUrl *m_url{};
    QString m_swpBuf;                       //用于去除重复上下载操作
    bool m_operator_Mutex;                  //上下载操作锁   TODO 其他的上下载操作放入队列中
    bool m_cbChange{};                      //判断粘贴板内容改变
    bool m_clsIsInit;                       //本类是否被初始化过
    bool m_ThreadStatus{};                  //线程状态
    int m_reconnectTimes{};                 //重连次数
    QNetworkReply *m_reply{};               //应答类
    File_Class *m_file_class{};             //文件管理
    QNetworkAccessManager *m_manager{};     //网络请求类
};

#endif // NETWORK_CLASS_H
#pragma clang diagnostic pop
#pragma clang diagnostic pop
