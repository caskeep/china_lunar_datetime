//
// Created by Mithwindy on 07/06/2018.
//

#include "ch_lunar.h"

int
main(int argc, char* argv[])
{
    std::cout << "## Class ChLunarDate Test build map." << std::endl;

    CChLunarDateTime::Init();
    //std::cout << CChLunarDateTime::StaticDataToString();
    const auto tmp = static_cast<unsigned long long>(86400000u) * static_cast<unsigned long long>(13u) +
                     static_cast<unsigned long long>(1u);
    CChLunarDateTime chLunarDate;
    chLunarDate.Set(2017, 8, 1);
    const auto  strGDateTime = chLunarDate.GDateTimeToString();
    std::cout << "tostring: " << strGDateTime;
    const auto strLDateTime = chLunarDate.LDateTimeToString();
    std::cout << "tostring: " << strLDateTime;
    return 0;
}
