#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"
#ifndef NETWORK_CLASS_H
#define NETWORK_CLASS_H

#include <QUrl>
#include <QDebug>
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

    [[noreturn]] void run() override;

    bool isInit();

    QString syncFrom_Server();

    //QString 上次到服务器
    bool uploadto_Server();

    void setUrl(const QUrl &url);

    void setUrl(QUrl *url);

public slots:


    bool replyError(QNetworkReply::NetworkError);

    bool finished_of_Reply(QNetworkReply *);

    bool snd2ser(const QString &SndStr2Serv, const QUrl &url);

    void changeThreadStatus(bool Status);

    bool clipBoardChange(bool status);

signals:

private:
    QNetworkAccessManager *getInstance();

private:
    QUrl *m_url{};
    bool m_clsIsInit;
    bool m_cbChange;
    bool m_ThreadStartFlag;
    bool m_ThreadStatus{};
    int m_reconnectTimes{};
    QNetworkReply *m_reply{};
    File_Class *m_file_class{};
    QClipboard *m_clipboard{};
    QNetworkAccessManager *m_manager{};
};

#endif // NETWORK_CLASS_H

#pragma clang diagnostic pop