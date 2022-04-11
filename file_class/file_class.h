#ifndef FILE_CLASS_H
#define FILE_CLASS_H


#include <string>
#include <strstream>

#include <QFile>
#include <QDebug>
#include <QThread>
#include <QString>
#include <QFileInfo>
#include <QByteArray>
#include <QClipboard>
#include <QApplication>

#include "Public_Func/Pubilc_Func.h"

class File_Class : public QThread {
Q_OBJECT

public slots:

    //追加文件内容
    bool append2File(QString &str);

    template<typename T>
    void getRcvBuf(T);

signals:

    //发送给network_class，用于检测粘贴板是否更新
    void dataChanged();

    //发送给自己，用于更新粘贴板记录的文件内容
    void changeFile(const QString &);

public:

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
    QFile *m_file{};
    QString *m_cbContent;
    QClipboard *m_ClipBoard{};
};

#endif // FILE_CLASS_H
