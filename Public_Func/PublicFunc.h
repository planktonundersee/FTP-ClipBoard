//
// Created by Aquit on 2022/5/9.
//

#ifndef FTP_CLIPBOARD_PUBLICFUNC_H
#define FTP_CLIPBOARD_PUBLICFUNC_H

#include <ostream>
#include <QDateTime>
#include <QString>

enum ThreadName{
    MAIN_WINDOW = 1,
    NETWORK_CLASS,
    FILE_CLASS,
    KEYBOARD_MOUSE_HOOK
};

struct keyBoard
{
    unsigned short keyChar;
    uint16_t keyCode;
    uint16_t rawCode;

    keyBoard(unsigned short keyChar, uint16_t keyCode, uint16_t rawCode);

    keyBoard();
};

//只用于发送信号使用
typedef class emit_Bundle
{
private:
    int operator_num;               //对该类进行什么操作
    int thread_Name;                //发给那个线程进行操作
    QString buf;                    //将类序列化存入QString
    keyBoard key;;

public:
    emit_Bundle();
    emit_Bundle(int operatorNum,short threadName, keyBoard key);

    int getOperatorNumber();
    void setOperatorNumber(int val);

    int getThreadNumber();
    void setThreadNumber(int threadName);

    QString getbuf();
    void setbuf(QString content);

    keyBoard getKey();
    void setKey(const keyBoard& key);
}emitBundle;

class Pubilc_Func {
private:
    static Pubilc_Func *m_publicFunc;
public:
    Pubilc_Func();
    static Pubilc_Func* instance();
    static int calculate_Dec_Bit(long long int);
    static std::string getCurrentTime();

public slots:
    static QString getRcvBuf(emitBundle& buf);

signals:
    void sendSignal(emitBundle& buf);

public:
    static std::ostream *output;
};

#endif //FTP_CLIPBOARD_PUBLICFUNC_H
