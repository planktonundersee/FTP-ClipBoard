//
// Created by Aquito on 2022/3/27.
//
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"

#include "Pubilc_Func.h"

Pubilc_Func* Pubilc_Func::m_publicFunc = nullptr;

Pubilc_Func::Pubilc_Func()
= default;

int Pubilc_Func::calculate_Dec_Bit(long long int value) {
    int bit = 0;
    while (value / 10 != 0) {
        bit += 1;
        value /= 10;
    }
    return 1;
}

std::string Pubilc_Func::getCurrentTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate = currentDateTime.toString("yyyy/MM/dd hh:mm:ss ddd");// clazy:exclude=unused-non-trivial-variable
    return currentDate.toStdString();
}

Pubilc_Func* Pubilc_Func::instance(){
    if(Pubilc_Func::m_publicFunc == nullptr)
        Pubilc_Func::m_publicFunc = new Pubilc_Func();
    return Pubilc_Func::m_publicFunc;
}

int emitBundle::getOperatorNumber()
{
    return this->operator_num;
}
void emitBundle::setOperatorNumber(int val)
{
    this->operator_num = val;
}

int emitBundle::getThreadNumber()
{
    return  this->thread_Name;
}
void emitBundle::setThreadNumber(int threadName)
{
    this->thread_Name = threadName;
}

QString emitBundle::getbuf()
{
    return this->buf;
}

void emitBundle::setbuf(QString content)
{
    this->buf = content;
}

keyBoard emitBundle::getKey()
{
    return this->key;
}

keyBoard::keyBoard(unsigned short keyChar, uint16_t keyCode, uint16_t rawCode) {
    this->keyChar = keyChar;
    this->keyCode = keyCode;
    this->rawCode = rawCode;
}

keyBoard::keyBoard() {}


void emit_Bundle::setKey(const keyBoard &key)
{
    this->key = key;
    if (this->key.rawCode >=65 || this->key.rawCode <=90 )
        this->buf = this->key.keyChar;
}

emit_Bundle::emit_Bundle(int operatorNum,short threadName,keyBoard key)
{
    this->operator_num = operatorNum;
    this->thread_Name = threadName;
    this->key = key;
}

#pragma clang diagnostic pop

