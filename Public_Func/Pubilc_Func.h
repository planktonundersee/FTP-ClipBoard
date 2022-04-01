//
// Created by Aquito on 2022/3/27.
//

#include <string>

#include <QString>
#include <QDateTime>

#ifndef FTP_CLIPBOARD_PUBILC_FUNC_H
#define FTP_CLIPBOARD_PUBILC_FUNC_H


class Pubilc_Func {
public:
    static int calculate_dec_Bit(long long int);

    static std::string getCurrentTime();

};

//只用于发送信号使用
template<typename T>
struct emit_bundle
{
    int operator_num;               //对该类进行什么操作
    T template_Class;               //将类序列化存入QString
};

#endif //FTP_CLIPBOARD_PUBILC_FUNC_H
