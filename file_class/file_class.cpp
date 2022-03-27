#include <QFileInfo>
#include <sstream>
#include "file_class.h"

File_Class::File_Class(const QFileInfo &File_Info) {
    this->m_cbContent = new QString();
    //初始化
    if (!this->CreateFile(File_Info)) {
        return;
    }
    connect(this, SIGNAL(changeFile(const QString&)), this, SLOT(append2File(const QString&)));
}

File_Class::~File_Class() {
    delete this->m_file;
    delete this->m_cbContent;
}

bool File_Class::CreateFile(const QFileInfo &File_Info) {
    if (File_Info.isDir()) {
        qDebug() << "Path String Is A Directory";
        return false;
    }

    qDebug() << "File Path : " << this->m_file->fileName();

    if (File_Info.isFile()) {
        this->m_file->open(QIODevice::ReadWrite);
        return true;
    } else {
        if (!this->m_file->open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << __LINE__ - 2 << "\t" << __FUNCTION__;
            return true;
        } else {
            qDebug() << "open file success" << " :: " << this->m_file->fileName();
            return false;
        }
    }
}

QByteArray File_Class::getFileContent() {
    if (!this->m_file->isOpen()) {
        return {};
    }

    this->m_file->seek(0);
    QByteArray sndStr = this->m_file->readAll();
    qDebug() << "sndStr" << sndStr;
    return sndStr;
}

bool File_Class::append2File(const QString &str) {
    QString Fpath = QApplication::applicationDirPath();
    this->m_file = new QFile(Fpath);
    this->m_file->setFileName(Fpath + "/ClipBorad.txt");
    QFileInfo File_Info(this->m_file->fileName());
    if (!this->CreateFile(File_Info)) {
        return false;
    }

    this->m_file->seek(this->m_file->size());
    QString buff = QString::fromUtf8((QString("\n") + str).toLatin1());
    qDebug() << "buff: " << buff;
    if (this->m_file->write(buff.toLatin1())) {
        return true;
    } else {
        return false;
    }
}

QFile *File_Class::getFile() {
    return this->m_file;
}

QClipboard *File_Class::getClipBoard() {
    return this->m_ClipBoard;
}

[[noreturn]] void File_Class::run() {
    while (true) {
        QString content = this->m_ClipBoard->text();
        if (this->m_cbContent == content) {
            //do nothing
        } else {
            emit this->dataChanged();
            emit this->changeFile(content);
        }
    }
}

//根据传入的数据生成帧
//%%Message&&2022/03/27 12:26:23 sun&&11&&47::xxxxxxxxxxx
//%%表示新一帧开始, 以Message表示是报文，&& 为分隔符, ::表示报文结束。
//表示报文头长47
//58表示此帧总长为58
//11表示后面的内容有11个字符
QString File_Class::generateMessage(QString &str) {
    std::stringstream message;

    //计算真正的内容才长度
    long long int content = str.length();
    int content_bit = Pubilc_Func::calculate_dec_Bit(content);

    //拿到当前时间
    std::string CurrentTime = Pubilc_Func::getCurrentTime();

    //去除报文和总长的长度
    int msgLen = 36 + content_bit + 4;

    //msgLen的长度
    int msgLenBit = Pubilc_Func::calculate_dec_Bit(msgLen);
    msgLen += msgLenBit;
    msgLenBit = Pubilc_Func::calculate_dec_Bit(msgLen);

    //拼凑报文
    message << "%%Message&&" << CurrentTime << "&&" << content_bit << "&&" << msglenBit << "::" << str.toStdString();

    //stringstream转std::string
    std::string retStr;
    message >> retStr;

    return {retStr.c_str()};
}


