#pragma clang diagnostic push
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
#pragma ide diagnostic ignored "google-explicit-constructor"
#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

#include <QUrl>
#include <QDebug>
#include <QByteArray>
#include <QThread>
#include <QListWidgetItem>
#include <QClipboard>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "file_class/file_class.h"

class Network_Class : public QThread {
Q_OBJECT

public:

    enum Status {
        THREAD_START, THREAD_STOP
    };

    Network_Class();

    Network_Class(const QUrl &Url);

    Network_Class(QUrl *url);

    void run() override;

    void setUrl(const QUrl &url);

    void setUrl(QUrl *url);

public slots:

    bool upload_to_Server();

    QString download_From_Server();

    bool replyError(QNetworkReply::NetworkError);

    bool finished_of_Upload(QNetworkReply *);

    bool finished_of_download(QNetworkReply *);

    void changeThreadStatus(bool Status);

    bool clipBoardChange(bool status);

    QString getFTPContent();

signals:

    template<typename T>
    void sendSignal(emit_bundle<T> &emitBundle);
    
    //a 表示操作数，
    //
//    void sendBuftoMainWindow(QString &);
//
//    void sendBuftoFileClass(QString &);

private:
    QNetworkAccessManager *getInstance();

    bool send(const QString &SndStr2Serv, const QUrl &url);

    bool sync(const QUrl &url);

    bool isInit();


private:
    QUrl *m_url{};
    QString m_swpBuf;                       //用于去除重复上下载操作
    bool m_operator_Mutex;                  //上下载操作锁   TODO 其他的上下载操作放入队列中
    bool m_cbChange;                        //判断粘贴板内容改变
    bool m_clsIsInit;                       //本类是否被初始化过
    bool m_ThreadStatus{};                  //线程状态
    bool m_ThreadStartFlag;                 //用于开关线程
    int m_reconnectTimes{};                 //重连次数
    QNetworkReply *m_reply{};               //应答类
    File_Class *m_file_class{};             //文件管理
    QNetworkAccessManager *m_manager{};     //网络请求类
};

#endif // NETWORK_CLASS_H
#pragma clang diagnostic pop
