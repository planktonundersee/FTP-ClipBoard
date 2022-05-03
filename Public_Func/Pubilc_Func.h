//
// Created by Aquito on 2022/3/27.
//
#ifndef FTP_CLIPBOARD_PUBILC_FUNC_H
#define FTP_CLIPBOARD_PUBILC_FUNC_H

#include <QDateTime>

//只用于发送信号使用
typedef struct emit_Bundle
{
    int operator_num;           //对该类进行什么操作
    short int thread_Name;          //发给那个线程进行操作
    QString template_Class;     //将类序列化存入QString
}emitBundle;

class Pubilc_Func {
public:
    Pubilc_Func();
    static int calculate_Dec_Bit(long long int);
    static std::string getCurrentTime();

public slots:
    //virtual QString getRcvBuf(emitBundle& buf);
    QString getRcvBuf(emitBundle& buf);
signals:
    void sendSignal(emitBundle& buf);
};

#endif //FTP_CLIPBOARD_PUBILC_FUNC_H
