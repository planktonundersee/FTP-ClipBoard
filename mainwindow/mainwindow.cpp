#include "mainwindow.h"
#include "ui_mainwindow.h"
//密码加密
//选择配置 JSON
//NetWork 保活

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    this->m_ui->setupUi(this);
    this->m_ui->pawdEdit->setEchoMode(QLineEdit::Password);
    this->m_ReconnectTimes = 0;
    this->m_Hide_UI = false;

    this->setWindowTitle("这儿应该放点儿什么东西才对");

    this->setText();
    this->m_Network = this->getInstance();
    connect(this, SIGNAL(threadStatus(bool)), this->m_Network, SLOT(changeThreadStatus(bool)));
}

MainWindow::~MainWindow() {
    delete this->m_Network;
    delete this->m_record;
    delete this->m_Reply;
    delete this->m_File;
    delete this->m_ui;
}

void MainWindow::on_pushButton_clicked(bool checked) {
    if (checked) {
        this->m_UploadFlag = true;
        this->m_DownloadFlag = true;
        this->m_ui->pushButton->setText("开启同步");
        this->m_Url = this->setUrl();
        this->changeUi();
        //启动线程
        this->m_Network->setUrl(this->setUrl());
        this->m_Network->start();
        emit this->threadStatus(networkClass::status::THREAD_START);
        //networkClass networkClass(this->setUrl(true));
        //networkClass.run();
    } else {
        this->m_UploadFlag = false;
        this->m_DownloadFlag = false;
        this->m_ui->pushButton->setText("暂停同步");
        this->changeUi();
        emit this->threadStatus(networkClass::status::THREAD_STOP);
        //结束线程
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->modifiers() == Qt::ControlModifier) && (event->key() == Qt::Key_C)) {
        if (this->m_UploadFlag) {
            //TODO
            emitBundle sendClass;
            sendClass.operator_num = 1;
            emit sendSignal(sendClass);
        }

    }
    if ((event->modifiers() == Qt::ControlModifier) && (event->modifiers() == Qt::ShiftModifier) && (event->key()) == Qt::Key_V) {
        if (this->m_DownloadFlag) {
            //TODO
        }
    }
}

//单例模式?
networkClass *MainWindow::getInstance() {
    if (this->m_Network == nullptr) {
        auto network = new networkClass(this->m_Url);
        return network;
    } else {
        return this->m_Network;
    }
}

void MainWindow::changeUi() {
    if (this->m_Hide_UI) {
        this->showUi();
        this->m_Hide_UI = false;
    } else {
        this->hideUi();
        this->m_Hide_UI = true;
    }
}

//双击复制
void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    this->m_ClipBoard->setText(item->text());
}

//顺序添加
void MainWindow::addListWidget() {
    this->m_ReconnectTimes = 0;
    auto clipBoardString = this->m_ClipBoard->text();
    auto *listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText(clipBoardString);
    size_t countRow = this->m_ui->listWidget->count();

    for (size_t i = countRow; i > 0; i--) {
        this->m_ui->listWidget->insertItem(i, this->m_ui->listWidget->item(i));
    }
    this->m_ui->listWidget->insertItem(0, listWidgetItem);
    qDebug() << "Upload Success";
    this->changeUi();
}

//与别的文件不同步时，同步时使用
void MainWindow::delListWidget() {

}

//与别的文件不同步时，同步时使用
void MainWindow::insertListWidget(const QString &input, int row) {
    this->m_ReconnectTimes = 0;
    auto clipBoardString = this->m_ClipBoard->text();
    auto *listWidgetItem = new QListWidgetItem;
    listWidgetItem->setText(clipBoardString);
    size_t countRow = this->m_ui->listWidget->count();

    for (size_t i = countRow; i > 0; i--) {
        this->m_ui->listWidget->insertItem(i, this->m_ui->listWidget->item(i));
    }
    this->m_ui->listWidget->insertItem(0, listWidgetItem);
    qDebug() << "Upload Success";
    this->changeUi();
}

//差别较大时，刷新ListWidget
void MainWindow::refreshListWidget() {

}

QUrl MainWindow::setUrl(bool point) {
    if (this->m_ui->addrEdit->text().isEmpty() ||
        this->m_ui->portEdit->text().isEmpty() ||
        this->m_ui->pawdEdit->text().isEmpty() ||
        this->m_ui->nameEdit->text().isEmpty()) {
        return {};
    } else {
        QUrl *url = this->setUrl();
        return *url;
    }
}

QUrl *MainWindow::setUrl() {

    QString name = this->m_ui->nameEdit->text();
    QString pawd = this->m_ui->pawdEdit->text();
    QString addr = this->m_ui->addrEdit->text();
    QString port = this->m_ui->portEdit->text();

    if (port.isEmpty() || addr.isEmpty() || pawd.isEmpty() || name.isEmpty()) {
        QMessageBox::warning(this, QString("Input Error"), tr("input all information"), QMessageBox::Ok);
        return {};
    }
    if (port.toInt() < 1 && port.toInt() > 65535) {
        qDebug() << port.toInt();
        QMessageBox::warning(this, QString("Input Error"), tr("input valid number of port"), QMessageBox::Ok);
        //return QUrl(nullptr);
        return {};
    }

    QUrl *url;
    url = new QUrl(this->m_ui->addrEdit->text() + "ClipBoradCache");
    url->setScheme("ftp");
    url->setPort(port.toInt());
    url->setUserName(name);
    url->setPassword(pawd);

    qDebug() << "The Url Addr:\t" << url->host();
    qDebug() << "The Url Name:\t" << url->userName();
    qDebug() << "The Url Pawd:\t" << url->password();
    qDebug() << "The Url Port:\t" << url->port();

    this->m_Url = url;
    return url;
}

void MainWindow::setText() {
    this->m_ui->nameEdit->setText("ftpuser");
    this->m_ui->pawdEdit->setText("qwer1234");
    this->m_ui->addrEdit->setText("ftp://124.222.207.94/");
    this->m_ui->portEdit->setText("579");
}

void MainWindow::hideUi() {
    this->m_ui->addrEdit->hide();
    this->m_ui->nameEdit->hide();
    this->m_ui->pawdEdit->hide();
    this->m_ui->portEdit->hide();
    this->m_ui->addrLabel->hide();
    this->m_ui->nameLabel->hide();
    this->m_ui->pawdLabel->hide();
    this->m_ui->portLabel->hide();
}

void MainWindow::showUi() {
    this->m_ui->addrEdit->show();
    this->m_ui->nameEdit->show();
    this->m_ui->pawdEdit->show();
    this->m_ui->portEdit->show();
    this->m_ui->addrLabel->show();
    this->m_ui->nameLabel->show();
    this->m_ui->pawdLabel->show();
    this->m_ui->portLabel->show();
    this->m_ui->pawdEdit->inputMask();

}

