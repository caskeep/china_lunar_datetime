//
// Created by Mithwindy on 07/06/2018.
//

#include "ch_lunar.h"
#include <iostream>

int main(int argc, char *argv[]) {
    {
        const std::string civil_string = "2015-09-22 09:35:00";

        std::chrono::system_clock::time_point tp;

        const auto        now = std::chrono::system_clock::now();
        const std::string s   = now > tp ? "running long!" : "on time!";

        std::cout << "Talk " << s << "\n";

        cctz::civil_day civilDay(2018, 7, 9);
//        std::cout << civilDay << std::endl;
        const auto dayOfWeek = static_cast<int>(cctz::get_weekday(civilDay));
        std::cout << "civil day year: " << civilDay.year() << " month: " << civilDay.month() << " day of month: "
                  << civilDay.day() << " day of week: " << dayOfWeek << std::endl;
    }
    return 0;
}
