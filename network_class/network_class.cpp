#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-convert-member-functions-to-static"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
// clazy:excludeall=connect-not-normalized
#include "network_class.h"

networkClass* networkClass::m_networkClass = nullptr;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Winvalid-noreturn"
#pragma ide diagnostic ignored "ConstantFunctionResult"
networkClass::networkClass() {
    if (this->m_clsIsInit) {
        return;
    }

    this->m_operator_Mutex = true;
    this->m_clsIsInit = true;
    this->m_url = nullptr;

    connect(this->m_file_class, SIGNAL(dataChanged()), this, SLOT(clipBoardChange(bool)));
    this->m_ThreadStatus = false;
}


networkClass::networkClass(const QUrl &url) {
    if (this->m_clsIsInit) {
        return;
    }

    this->m_clsIsInit = true;
    this->m_operator_Mutex = true;
    this->m_url->setHost(url.host());
    this->m_url->setPort(url.port());
    this->m_url->setPassword(url.password());
    this->m_url->setUserName(url.userName());
    this->m_url->setScheme(url.scheme());

    connect(this->m_file_class, SIGNAL(dataChanged()), this, SLOT(clipBoardChange(bool)));
    connect(this, SIGNAL(sendBuftoFileClass(QString & )), this->m_file_class, SLOT());

    this->m_ThreadStatus = false;
}

networkClass::networkClass(QUrl *url) {
    if (this->m_clsIsInit) {
        return;
    }

    this->m_url = url;
    this->m_clsIsInit = true;
    this->m_operator_Mutex = true;
    this->m_ThreadStatus = false;

    connect(this->m_file_class, SIGNAL(dataChanged()), this, SLOT(clipBoardChange(bool)));
    connect(this, SIGNAL(sendSignal(emit_Bundle<T> &emitBundle)), this->m_file_class, SLOT(getRcvBuf(emit_Bundle<T>)));

    this->m_ThreadStatus = false;
}

bool networkClass::finishedOfUpload(QNetworkReply *ftpReply) {
    while (!ftpReply->isRunning()) {
        qDebug() << "its running";
        //TODO: 同步粘贴板

    }

    return false;
}

bool networkClass::finishedOfDownload(QNetworkReply *ftpReply) {
    while (!ftpReply->isRunning()) {
        ftpReply->thread();
    }
    return true;
}

//TODO
QString networkClass::downloadFromServer() {
    while (this->m_operator_Mutex) {
        this->m_operator_Mutex = false;
        this->m_reconnectTimes = 0;

        QString rcvBuf = "";
        rcvBuf;
        this->sync(*(this->m_url));

    }
    this->m_operator_Mutex = true;
    return "";
}

//TODO
bool networkClass::uploadToServer() {
    while (this->m_operator_Mutex) {
        this->m_operator_Mutex = false;
        QString content = this->m_file_class->getClipBoard()->text();
        if (this->m_file_class->append2File(content)) {
            this->m_file_class->getFile()->close();
            this->send(content, *(this->m_url));
            this->m_operator_Mutex = true;
            return true;
        } else {
            qDebug() << "追加文件错误";
            this->m_operator_Mutex = true;
            return false;
        }
    }
    return true;
}

void networkClass::run() {
    if (!this->isInit())
    {
        qDebug() << "还未初始化";
        exit(0);
    }

    //放到槽函数中,while(1)函数保证线程不结束
    while (true) {
        if (this->m_ThreadStatus == status::THREAD_START) {
            //if ()
            qDebug() << "Working";

        } else if (this->m_ThreadStatus == networkClass::status::THREAD_STOP) {
            sleep(1);
            qDebug() << "Do Nothing...";
        } else {
            sleep(1);
            qDebug() << "Other Thread status";
        }
        exit(0);
    }
}

bool networkClass::replyError(QNetworkReply::NetworkError) {
    //最多尝试三次重连，如果失败断开连接
    if (this->m_reconnectTimes >= 3) {
        if (this->m_url->isEmpty()) {
            return false;       //网络不可达
        }
        qDebug() << "can't connect to server:" << this->m_url->host() << " : " << this->m_url->port();

        //TODO
        disconnect(this->m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,SLOT(replyError(QNetworkReply::NetworkError)));
    }

    QString clipBoardStr = this->m_file_class->getClipBoard()->text();
    this->send(clipBoardStr, *(this->m_url));
    return true;
}

bool networkClass::send(const QString &sndStr2Serv, const QUrl &url) {
    if (url.isEmpty()) {
        return false;
    }

    QNetworkAccessManager *ftpManager = this->getInstance();

    QNetworkRequest request(url);
    QByteArray sndStr = sndStr2Serv.toLatin1();

    if (sndStr.isEmpty()) {
        qDebug() << "Read File Content Fail";
        return false;
    }

    this->m_reply = ftpManager->put(request, sndStr);

    connect(this->m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,
            SLOT(replyError(QNetworkReply::NetworkError)));
    connect(ftpManager, SIGNAL(finished(QNetworkReply * )), this, SLOT(finishedOfUpload(QNetworkReply * )));
    return true;
}

//单例模式?
QNetworkAccessManager *networkClass::getInstance() {
    if (this->m_manager == nullptr) {
        //TODO : 是否有风险?
        auto *pManager = new QNetworkAccessManager();
        return pManager;

    } else {
        return this->m_manager;
    }
}

bool networkClass::isInit() {
    if (this->m_url->isEmpty()) {
        return false;
    } else {
        return true;
    }
}

void networkClass::changeThreadStatus(bool status) {
    this->m_ThreadStatus = status;
}

void networkClass::setUrl(QUrl *url) {
    this->m_url = url;
}

void networkClass::setUrl(const QUrl &url) {
    this->m_url->setScheme(url.scheme());
    this->m_url->setPort(url.port());
    this->m_url->setUserName(url.userName());
    this->m_url->setPassword(url.password());
    this->m_url->setHost(url.host());
}

bool networkClass::clipBoardChange(bool status) {
    this->m_cbChange = ~this->m_cbChange;
    return true;
}

bool networkClass::sync(const QUrl &url) {

    QNetworkAccessManager *ftpManager = this->getInstance();

    QNetworkRequest request(*(this->m_url));

    this->m_reply = ftpManager->get(request);

    connect(this->m_reply, SIGNAL(QNetworkReply::readyRead()), this, SLOT(getFtpContent()));
    connect(ftpManager, SIGNAL(finished(QNetworkReply * )), this, SLOT(finishedOfDownload(QNetworkReply * )));// clazy:exclude=connect-not-normalized
    connect(this->m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,SLOT(replyError(QNetworkReply::NetworkError)));
    return true;
}

QString networkClass::getFtpContent() {
    QByteArray ftpContent = this->m_reply->readAll();
    QString rcvBuf = ftpContent;

    if (this->m_swpBuf == rcvBuf) {
        return {};
    } else {
        this->m_swpBuf = rcvBuf;
        this->m_file_class->getClipBoard()->setText(rcvBuf);
        this->m_file_class->append2File(rcvBuf);

        // 发给mainWindow
        emit_Bundle getRcvBuf;
        getRcvBuf.setbuf(rcvBuf);
        emit sendSignal(getRcvBuf);
    }
    return {};
}

networkClass* networkClass::instance()
{
    if(networkClass::m_networkClass == nullptr)
        networkClass::m_networkClass = new networkClass();
    return networkClass::m_networkClass;
}

//接受外部信号
//接受外部信号
QString networkClass::getRcvBuf(emitBundle& emitBundle)
{
    if (emitBundle.getOperatorNumber() == 1)
    {
        //TODO 上传操作
        return {};
    }
    if(emitBundle.getOperatorNumber() == 2)
    {
        //TODO 下载操作
        return {};
    }
    return {};
}


#pragma clang diagnostic pop
#pragma clang diagnostic pop