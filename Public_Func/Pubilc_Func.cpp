//
// Created by Aquito on 2022/3/27.
//
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"

#include "Pubilc_Func.h"

int Pubilc_Func::calculate_Dec_Bit(long long int value) {
    int bit = 0;
    while (value / 10 != 0) {
        bit += 1;
        value /= 10;
    }
}

std::string Pubilc_Func::getCurrentTime() {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentDate = currentDateTime.toString("yyyy/MM/dd hh:mm:ss ddd");// clazy:exclude=unused-non-trivial-variable
}

#pragma clang diagnostic pop
