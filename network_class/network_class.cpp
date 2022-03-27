#include "network_class.h"

Network_Class::Network_Class() {
    if (this->m_clsIsInit) {
        return;
    }

    this->m_clsIsInit = true;

    this->m_url = nullptr;

    connect(this->m_file_class, SIGNAL(dataChanged()), this, SLOT(clipBoardChange(bool)));
    this->m_ThreadStartFlag = false;
}

Network_Class::Network_Class(const QUrl &Url) {
    if (this->m_clsIsInit) {
        return;
    }

    this->m_clsIsInit = true;

    this->m_url->setHost(Url.host());
    this->m_url->setPort(Url.port());
    this->m_url->setPassword(Url.password());
    this->m_url->setUserName(Url.userName());
    this->m_url->setScheme(Url.scheme());

    connect(this->m_file_class, SIGNAL(dataChanged()), this, SLOT(clipBoardChange(bool)));

    this->m_ThreadStartFlag = false;
}

Network_Class::Network_Class(QUrl *url) {
    if (this->m_clsIsInit) {
        return;
    }

    this->m_clsIsInit = true;

    this->m_url = url;
    this->m_ThreadStartFlag = false;

    connect(this->m_file_class, SIGNAL(dataChanged()), this, SLOT(clipBoardChange(bool)));

    this->m_ThreadStartFlag = false;
}

bool Network_Class::finished_of_Reply(QNetworkReply *ftp_reply) {
    if (ftp_reply->isRunning()) {
        qDebug() << "its running";
    } else if (ftp_reply->isFinished()) {
        //TODO: 同步粘贴板

    } else {
        qDebug() << "i don't know network status";
        //this->changeUI();
    }

    return false;
}

//TODO
QString Network_Class::syncFrom_Server() {
    this->m_reconnectTimes = 0;
    return "";
}

//TODO
bool Network_Class::uploadto_Server() {
    QString content = this->m_clipboard->text();
    if (this->m_file_class->append2File(content)) {
        this->m_file_class->getFile()->close();
        this->snd2ser(content, *(this->m_url));
        return true;
    } else {
        qDebug() << "追加文件错误";
        return false;
    }
}

[[noreturn]] void Network_Class::run() {
    if (!this->isInit()) {
        qDebug() << "还未初始化";
        exit(0);
    }

    while (true) {
        if (this->m_ThreadStatus == Status::THREAD_START) {
            if ()
                qDebug() << "Working";
            //this->syncFrom_Server();
            //this->uploadto_Server();
        } else if (this->m_ThreadStatus == Network_Class::Status::THREAD_STOP) {
            sleep(1);
            qDebug() << "Do Nothing...";
        } else {
            sleep(1);
            qDebug() << "Other Thread Status";
        }
    }
}

bool Network_Class::replyError(QNetworkReply::NetworkError) {
    //最多尝试三次重连，如果失败断开连接
    if (this->m_reconnectTimes >= 3) {
        if (this->m_url->isEmpty()) {
            return false;       //网络不可达
        }
        qDebug() << "can't connect to server:" << this->m_url->host() << " : " << this->m_url->port();

        //TODO
        disconnect(this->m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,
                   SLOT(replyError(QNetworkReply::NetworkError)));
    }

    this->getUrl();
    this->m_clipboard = QGuiApplication::clipboard();
    QString clipBoard_str = this->m_clipboard->text();
    this->snd2ser(clipBoard_str, *(this->m_url));
    return true;
}

bool Network_Class::snd2ser(const QString &SndStr2Serv, const QUrl &url) {
    if (url.isEmpty()) {
        return false;
    }

    QNetworkAccessManager *FtpManager = this->getInstance();

    QNetworkRequest request(url);
    QByteArray sndStr = SndStr2Serv.toLatin1();
    if (sndStr.isEmpty()) {
        qDebug() << "Read File Content Fail";
        return false;
    }

    this->m_reply = FtpManager->put(request, sndStr);
    connect(this->m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this,
            SLOT(replyError(QNetworkReply::NetworkError)));
    connect(FtpManager, SIGNAL(finished(QNetworkReply * )), this, SLOT(finished_Of_Reply(QNetworkReply * )));
}

//单例模式?
QNetworkAccessManager *Network_Class::getInstance() {
    if (this->m_manager == nullptr) {
        //TODO : 是否有风险?
        auto *pManager = new QNetworkAccessManager();
        return pManager;

    } else {
        return this->m_manager;
    }
}

bool Network_Class::isInit() {
    if (this->m_url->isEmpty()) {
        return false;
    } else {
        return true;
    }
}

void Network_Class::changeThreadStatus(bool Status) {
    this->m_ThreadStatus = Status;
}

void Network_Class::setUrl(QUrl *url) {
    this->m_url = url;
}

void Network_Class::setUrl(const QUrl &url) {
    this->m_url->setScheme(url.scheme());
    this->m_url->setPort(url.port());
    this->m_url->setUserName(url.userName());
    this->m_url->setPassword(url.password());
    this->m_url->setHost(url.host());
}

bool Network_Class::clipBoardChange(bool status) {
    this->m_cbChange = ~this->m_cbChange;
}


