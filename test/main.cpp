//
// Created by Mithwindy on 07/06/2018.
//

#include "ch_lunar.h"

int main(int argc, char* argv[])
{
	//{
	//	std::cout << "## Basic Test." << std::endl;
	//	const std::string civil_string = "2015-09-22 09:35:00";

	//	std::chrono::system_clock::time_point tp;

	//	const auto        now = std::chrono::system_clock::now();
	//	const std::string s = now > tp ? "running long!" : "on time!";

	//	std::cout << "Talk " << s << "\n";

	//	cctz::civil_day civilDay(2018, 7, 12);
	//	//        std::cout << civilDay << std::endl;
	//	const auto dayOfWeek = static_cast<int>(get_weekday(civilDay));

	//	std::cout << "civil day year: " << civilDay.year() << " month: " << civilDay.month() << " day of month: "
	//		<< civilDay.day() << " day of week: " << dayOfWeek << std::endl;

	//	cctz::civil_second civilSecond(2018, 7, 11, 10, 11, 25);
	//	const auto         dayOfWeek2 = static_cast<int>(get_weekday(civilDay));

	//	std::cout << "civil second year: " << civilSecond.year() << " month: " << civilSecond.month()
	//		<< " day of month: "
	//		<< civilSecond.day() << " day of week: " << dayOfWeek2 << " hour of day: " << civilSecond.hour()
	//		<< std::endl;
	//}

	{
		std::cout << "## Class ChLunarDate Test build map." << std::endl;
		ChLunarDate chLunarDate;
		chLunarDate.BuildGMap();
		chLunarDate.DebugPrintBuildMap();
		//        auto tup1 = chLunarDate.GetYMD(86400001);
		//        chLunarDate.DebugPrintYMD(tup1);
		unsigned long long tmp = static_cast<unsigned long long>(86400000u) * static_cast<unsigned long long>(600u) +
		                         static_cast<unsigned long long>(1u);
		//        unsigned long long tmp = 2678400001;
		chLunarDate.SetVal(tmp);
		const auto oGDateTime = chLunarDate.GetGDateTime();
		const auto strDateTime = oGDateTime.ToString();
		std::cout << "tostring: " << strDateTime;
	}
	return 0;
}
