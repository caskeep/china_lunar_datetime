//
// Created by Mithwindy on 07/05/2018.
//

#ifndef CHINA_LUNAR_DATETIME_CH_LUNAR_H
#define CHINA_LUNAR_DATETIME_CH_LUNAR_H

#include "cctz/civil_time.h"
#include <chrono>


class ChLunarDate
{
public:
    ChLunarDate() = default;
    ~ChLunarDate() = default;

public:
    int
    GetYear() {return second_.year(); }

    int
    GetMonthOfYear() {return second_.month(); }

    int
    GetDayOfMonth() { return second_.day(); }

    int
    GetDayOfWeek() {
        cctz::civil_day day(second_);
        static_cast<int>(cctz::get_weekday(day)) + 1;
    }

    int
    GetHourOfDay() { return second_.hour(); }

    int
    GetMinuteOfHour() { return second_.minute(); }

    int
    GetSecondOfMinute() {return second_.second(); }

public: // TODO
    cctz::civil_second second_;
};


#endif //CHINA_LUNAR_DATETIME_CH_LUNAR_H
