#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
#ifndef FTP_CLIPBOARD_FILE_CLASS_H
#define FTP_CLIPBOARD_FILE_CLASS_H


#include <string>
//#include <strstream>

#include <QFile>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QFileInfo>
#include <QByteArray>
#include <QClipboard>
#include <QApplication>

#include "Public_Func/PubilcFunc.h"

class File_Class : public QThread, public Pubilc_Func{
Q_OBJECT

signals:
    //发送给network_class，用于检测粘贴板是否更新
    void dataChanged();
    void sendSignal(emitBundle& buf);

private:
    bool emptyFilePath();

public slots:
    //发送给自己，用于更新粘贴板记录的文件内容
//    void changeFile(const QString &);

    //TODO: 实现追加文件内容
    QString getRcvBuf(emitBundle& emitBundle);

public:
    static File_Class* instance(const QFileInfo&);

    bool append2File(QString &str);

    File_Class(const QFileInfo &fileInfo);

    ~File_Class();

    //创建本地的文件
    bool createFile(const QFileInfo &fileInfo);

    //获取文件内容
    QByteArray getFileContent();

    //单例模式
    QFile *getFile();

    //对外接口
    QClipboard *getClipBoard();

    //线程启动函数
    [[noreturn]] void run() override;

    //生成报文
    static QString generateMessage(QString &str);

private:
    static File_Class* m_fileClass;
    bool m_emptyPath;
    QFile *m_file{};
    QString *m_cbContent;
    QClipboard *m_ClipBoard{};
};

#endif // FTP_CLIPBOARD_FILE_CLASS_H

#pragma clang diagnostic pop