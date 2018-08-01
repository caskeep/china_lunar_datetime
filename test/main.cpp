//
// Created by Mithwindy on 07/06/2018.
//

#include "ch_lunar.h"

int
main(int argc, char* argv[])
{
    std::cout << "## Class ChLunarDate Test build map." << std::endl;

    CChLunarDateTime::Init();
    std::cout << CChLunarDateTime::StaticDataToString();
    const auto tmp = static_cast<unsigned long long>(86400000u) * static_cast<unsigned long long>(13u) +
                     static_cast<unsigned long long>(1u);
    CChLunarDateTime chLunarDate1;
    chLunarDate1.Set(2018, 8, 1);
    std::cout << "tostring: " << chLunarDate1.GDateTimeToString();
    std::cout << "tostring: " << chLunarDate1.LDateTimeToString();

    const auto nVal1 = chLunarDate1.GetVal();
    CChLunarDateTime chLunarDate2;
    chLunarDate2.SetVal(nVal1);
    std::cout << "tostring: " << chLunarDate2.GDateTimeToString();
    std::cout << "tostring: " << chLunarDate2.LDateTimeToString();
    return 0;
}
