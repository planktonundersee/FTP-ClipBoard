
//
// Created by Aquit on 2022/3/27.
//

#include "Pubilc_Func.h"

int Pubilc_Func::calculate_dec_Bit(long long int value) {
    int bit = 0;
    while (value / 10 != 0) {
        bit += 1;
        value /= 10;
    }
}

std::string Pubilc_Func::getCurrentTime() {
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy/MM/dd hh:mm:ss ddd");
}
