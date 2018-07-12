//
// Created by Mithwindy on 07/06/2018.
//

#include "ch_lunar.h"
#include <iostream>

int main(int argc, char *argv[]) {
    {
        std::cout << "## Basic Test." << std::endl;
        const std::string civil_string = "2015-09-22 09:35:00";

        std::chrono::system_clock::time_point tp;

        const auto        now         = std::chrono::system_clock::now();
        const std::string s           = now > tp ? "running long!" : "on time!";

        std::cout << "Talk " << s << "\n";

        cctz::civil_day civilDay(2018, 7, 12);
//        std::cout << civilDay << std::endl;
        const auto      dayOfWeek     = static_cast<int>(cctz::get_weekday(civilDay));

        std::cout << "civil day year: " << civilDay.year() << " month: " << civilDay.month() << " day of month: "
                  << civilDay.day() << " day of week: " << dayOfWeek << std::endl;

        cctz::civil_second civilSecond(2018, 7, 11, 10, 11, 25);
        const auto         dayOfWeek2 = static_cast<int>(cctz::get_weekday(civilDay));

        std::cout << "civil second year: " << civilSecond.year() << " month: " << civilSecond.month()
                  << " day of month: "
                  << civilSecond.day() << " day of week: " << dayOfWeek2 << " hour of day: " << civilSecond.hour()
                  << std::endl;
    }

    {
        std::cout << "## Class ChLunarDate Test." << std::endl;
        cctz::civil_second civilSecond(2018, 12, 12, 10, 11, 25);
        ChLunarDate        chLunarDate;
        chLunarDate.second_ = civilSecond;
        std::cout << "year:             " << chLunarDate.GetYear() << std::endl
                  << "month:            " << chLunarDate.GetMonthOfYear() << std::endl
                  << "day of month:     " << chLunarDate.GetDayOfMonth() << std::endl
                  << "day of week:      " << chLunarDate.GetDayOfWeek() << std::endl
                  << "hour of day:      " << chLunarDate.GetHourOfDay() << std::endl
                  << "minute of hour:   " << chLunarDate.GetMinuteOfHour() << std::endl
                  << "second of minute: " << chLunarDate.GetSecondOfMinute() << std::endl
                  << std::endl;
        std::cout << "lunar value:      " << static_cast<int>(chLunarDate.GetLunarValue(2018)) << std::endl
                  << "lunar month:      " << static_cast<int>(chLunarDate.GetLunarValueMonth(2018)) << std::endl
                  << "lunar leap month: " << chLunarDate.GetLunarMonthDayCount() << std::endl
                  << std::endl;
    }
    return 0;
}
