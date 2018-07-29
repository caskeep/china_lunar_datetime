//
// Created by Mithwindy on 07/06/2018.
//

#include "ch_lunar.h"

int
main(int argc, char* argv[])
{
    std::cout << "## Class ChLunarDate Test build map." << std::endl;

    ChLunarDate::Init();
    std::cout << ChLunarDate::DebugToString();
    const auto tmp = static_cast<unsigned long long>(86400000u) * static_cast<unsigned long long>(13u) +
                     static_cast<unsigned long long>(1u);
    ChLunarDate chLunarDate(tmp);
    const auto  oGDateTime = chLunarDate.GetGDateTime();
    const auto  strGDateTime = oGDateTime.ToString();
    std::cout << "tostring: " << strGDateTime;
    const auto oLDateTime = chLunarDate.GetLDateTime();
    const auto strLDateTime = oLDateTime.ToString();
    std::cout << "tostring: " << strLDateTime;

    return 0;
}
