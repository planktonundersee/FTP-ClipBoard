#include <QFileInfo>
#include <sstream>
#include "FileClass.h"

File_Class* File_Class::m_fileClass = nullptr;

File_Class::File_Class(const QFileInfo &fileInfo)
{
    //路径为空
    if(fileInfo.path().isNull())
    {
        this->m_emptyPath = true;
        exit(0);
    }

    //路径格式不对
    if(-1 == fileInfo.path().indexOf('\\') || (-1 == fileInfo.path().indexOf('/')))
    {
        this->m_emptyPath = true;
        exit(0);
    }

    this->m_cbContent = new QString();
    //初始化
    if (!this->createFile(fileInfo)) {
        return;
    }
}

File_Class::~File_Class() {
    delete this->m_file;
    delete this->m_cbContent;
}

bool File_Class::createFile(const QFileInfo &fileInfo) {
    if (fileInfo.isDir()) {
        qDebug() << "Path String Is A Directory";
        return false;
    }

    //存在就直接打开
    if (fileInfo.isFile()) {
        this->m_file->open(QIODevice::ReadWrite);
        return true;
    }
    else
    {   //不存在就新建
        if (!this->m_file->open(QIODevice::ReadWrite | QIODevice::Text)) {
            qDebug() << __LINE__ - 2 << "\t" << __FUNCTION__;
            return true;
        }
        else
        {
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

bool File_Class::append2File(QString &str) {
    QString fpath = QApplication::applicationDirPath();
    this->m_file = new QFile(fpath);
    this->m_file->setFileName(fpath + "/ClipBoard.txt");
    QFileInfo fileInfo(this->m_file->fileName());
    if (!this->createFile(fileInfo)) {
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

void File_Class::run() {
    while (true) {
        QString content = this->m_ClipBoard->text();
        if (*this->m_cbContent == content) {
            //do nothing
        } else {
            emit this->dataChanged();
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
    int contentBit = Pubilc_Func::calculate_Dec_Bit(content);

    //拿到当前时间
    std::string currentTime = Pubilc_Func::getCurrentTime();

    //去除报文和总长的长度
    int msgLen = 36 + contentBit + 4;

    //msgLen的长度
    int msgLenBit = Pubilc_Func::calculate_Dec_Bit(msgLen);
    msgLen += msgLenBit;
    msgLenBit = Pubilc_Func::calculate_Dec_Bit(msgLen);

    //拼凑报文
    message << "%%Message&&" << currentTime << "&&" << contentBit << "&&" << msgLenBit << "::" << str.toStdString();

    //stringstream转std::string
    std::string retStr;
    message >> retStr;

    return {retStr.c_str()};
}

QString File_Class::getRcvBuf(emitBundle emitBundle) {
    return {};
}

File_Class* File_Class::instance(const QFileInfo &fileInfo) {
    if(File_Class::m_fileClass == nullptr)
        File_Class::m_fileClass = new File_Class(fileInfo);
    return File_Class::m_fileClass;
}

bool File_Class::emptyFilePath() {
    if(this->m_emptyPath)
        return true;
    return false;
}


