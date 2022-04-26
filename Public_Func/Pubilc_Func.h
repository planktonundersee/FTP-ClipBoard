//
// Created by Aquito on 2022/3/27.
//
#ifndef FTP_CLIPBOARD_PUBILC_FUNC_H
#define FTP_CLIPBOARD_PUBILC_FUNC_H

#include <QString>
#include <QDateTime>

//只用于发送信号使用
struct emit_Bundle
{
    int operator_num;           //对该类进行什么操作
    short thread_Name           //发给那个线程进行操作
    QString template_Class;     //将类序列化存入QString
};

class Pubilc_Func {
public:
    static int calculate_Dec_Bit(long long int);

    static std::string getCurrentTime();

signals:
    void sendBuf(emit_Bundle& buf);
slots:
    static void getBuf();
};

#endif //FTP_CLIPBOARD_PUBILC_FUNC_H
