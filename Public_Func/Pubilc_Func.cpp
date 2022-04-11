//
// Created by Aquito on 2022/3/27.
//

#include "Pubilc_Func.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
int Pubilc_Func::calculate_Dec_Bit(long long int value) {
    int bit = 0;
    while (value / 10 != 0) {
        bit += 1;
        value /= 10;
    }
}
#pragma clang diagnostic pop

std::string Pubilc_Func::getCurrentTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate = currentDateTime.toString("yyyy/MM/dd hh:mm:ss ddd");// clazy:exclude=unused-non-trivial-variable
}
