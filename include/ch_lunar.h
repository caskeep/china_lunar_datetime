//
// Created by Mithwindy on 07/05/2018.
//

#ifndef CHINA_LUNAR_DATETIME_CH_LUNAR_H
#define CHINA_LUNAR_DATETIME_CH_LUNAR_H

#include "cctz/civil_time.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <map>

class ChLunarDate {
public:
    ChLunarDate() = default;

    ~ChLunarDate() = default;

    std::vector<unsigned int> LUNAR_INFO{
            0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2,//1900-1909
            0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977,//1910-1919
            0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970,//1920-1929
            0x06566, 0x0d4a0, 0x0ea50, 0x06e95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950,//1930-1939
            0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557,//1940-1949
            0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5b0, 0x14573, 0x052b0, 0x0a9a8, 0x0e950, 0x06aa0,//1950-1959
            0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0,//1960-1969
            0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b6a0, 0x195a6,//1970-1979
            0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570,//1980-1989
            0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x055c0, 0x0ab60, 0x096d5, 0x092e0,//1990-1999
            0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5,//2000-2009
            0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930,//2010-2019
            0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530,//2020-2029
            0x05aa0, 0x076a3, 0x096d0, 0x04afb, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45,//2030-2039
            0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0,//2040-2049
            0x14b63, 0x09370, 0x049f8, 0x04970, 0x064b0, 0x168a6, 0x0ea50, 0x06b20, 0x1a6c4, 0x0aae0,//2050-2059
            0x0a2e0, 0x0d2e3, 0x0c960, 0x0d557, 0x0d4a0, 0x0da50, 0x05d55, 0x056a0, 0x0a6d0, 0x055d4,//2060-2069
            0x052d0, 0x0a9b8, 0x0a950, 0x0b4a0, 0x0b6a6, 0x0ad50, 0x055a0, 0x0aba4, 0x0a5b0, 0x052b0,//2070-2079
            0x0b273, 0x06930, 0x07337, 0x06aa0, 0x0ad50, 0x14b55, 0x04b60, 0x0a570, 0x054e4, 0x0d160,//2080-2089
            0x0e968, 0x0d520, 0x0daa0, 0x16aa6, 0x056d0, 0x04ae0, 0x0a9d4, 0x0a2d0, 0x0d150, 0x0f252,//2090-2099
            0x0d520,                                                                                 //2100-2100
    };

    int          START_WITH       = 1900;
    int          MAX_SIZE         = 200;
    unsigned int MASK_LUNAR_MONTH = 0xfff0;
    unsigned int MASK_LUNAR_YEAR  = 61440;
    unsigned int MASK_LUNAR_LEAP  = 15;

public:
    using TYMD = std::tuple<int, int, int>;

    int
    GetYear() { return second_.year(); }

    int
    GetMonthOfYear() { return second_.month(); }

    int
    GetDayOfMonth() { return second_.day(); }

    int
    GetDayOfWeek() { return static_cast<int>(cctz::get_weekday(cctz::civil_day(second_))) + 1; }

    int
    GetHourOfDay() { return second_.hour(); }

    int
    GetMinuteOfHour() { return second_.minute(); }

    int
    GetSecondOfMinute() { return second_.second(); }

    unsigned int
    GetLunarValue(const int year) {
        if (year > START_WITH + MAX_SIZE || year < START_WITH) {
            return 0;
        }
        return LUNAR_INFO[year - START_WITH];
    }

    unsigned int
    GetLunarValueMonth(const int year) {
        if (year > START_WITH + MAX_SIZE || year < START_WITH) {
            return 0;
        }
        auto nVal = LUNAR_INFO[year - START_WITH];
        nVal = nVal & MASK_LUNAR_MONTH;
        nVal = nVal >> 4;
        return nVal;
    }

    int
    GetLunarMonthDayCount() {
        auto year = second_.year();
        if (year > START_WITH + MAX_SIZE || year < START_WITH) {
            return 0;
        }
        auto nVal = LUNAR_INFO[year - START_WITH];
        nVal = nVal & MASK_LUNAR_MONTH;
        nVal = nVal >> 4;
        auto tmp         = nVal;
        auto monthOfYear = second_.month();
        nVal = nVal >> (12 - monthOfYear);
        nVal = nVal & 1;
        if (nVal) {
            return 30;
        } else {
            return 29;
        }
    }

    int
    BuildGMap() {
        unsigned long long nIndex        = 0;
        int                nGMonthDayMax = 0;
        int                nGMonthOfYear = s_nGMonth;
        int                nGDayOfMonth  = s_nGDayOfMonth;
        int                nGYear        = s_nGYear;
        nGMonthDayMax = GetGMonthMaxDay(nGMonthOfYear, nGYear);
        while (nIndex < 700) {
            ++nIndex;
            ++nGDayOfMonth;
            if (nGDayOfMonth > nGMonthDayMax) {
                nGDayOfMonth = 1;
                ++nGMonthOfYear;
                if (nGMonthOfYear > 12) {
                    nGMonthOfYear = 1;
                    ++nGYear;
                }
                m_mapGday2YM[nIndex] = std::make_tuple(nGYear, nGMonthOfYear);
            }
        }
    }

    void
    DebugPrintBuildMap() {
        for (const auto &pair : m_mapGday2YM) {
            auto &nIndex = pair.first;
            auto &tupYM  = pair.second;
            auto nGYear  = std::get<0>(tupYM);
            auto nGMonth = std::get<1>(tupYM);
            std::cout << "index[" << nIndex << "] year,month[" << nGYear << "," << nGMonth << "]" << std::endl;
        }
    }

    int
    GetGMonthMaxDay(int nGMonth, int nGYear) {
        if (nGMonth == 1 || nGMonth == 3 || nGMonth == 5 || nGMonth == 7 || nGMonth == 8 || nGMonth == 10 ||
            nGMonth == 12) {
            return 31;
        } else {
            if (nGMonth == 2 && IsLeapGYear(nGYear)) {
                return 29;
            }
            return 30;
        }
    }

    bool
    IsLeapGYear(int nYear) {
        if (nYear % 400 == 0) {
            return true;
        }
        if (nYear % 100 == 0) {
            return false;
        }
        if (nYear % 4 == 0) {
            return true;
        }
        return false;
    }

    TYMD
    GetYMD(unsigned long long nIndex) {
        TYMD tupRes;
        auto it = m_mapGday2YM.upper_bound(nIndex);
        if (it == m_mapGday2YM.end()) {
            return std::make_tuple(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(),
                                   std::numeric_limits<int>::max());
        }
        if (it == m_mapGday2YM.begin()) {
            return std::make_tuple(0, 0, 0);
        }
        --it;
        const auto &tupGYM = it->second;
        std::get<0>(tupRes) = std::get<0>(tupGYM);
        std::get<1>(tupRes) = std::get<1>(tupGYM);
        std::get<2>(tupRes) = nIndex - it->first + 1;
        return tupRes;
    }

    void
    DebugPrintYMD(const TYMD &tup) {
        std::cout << "TYMD year[" << std::get<0>(tup) << "] month[" << std::get<1>(tup) << "] day[" << std::get<2>(tup)
                  << "].";
    }

    void
    DebugPrintYM(const std::tuple<int, int> &tup) {
        std::cout << "TYMD year[" << std::get<0>(tup) << "] month[" << std::get<1>(tup) << "] day.";
    }


public: // TODO
    cctz::civil_second                                  second_;
    unsigned long long                                  miliseconds_;
    std::map<unsigned long long, std::tuple<int, int> > m_mapGday2YM;

    static constexpr int s_nGYear       = 2018;
    static constexpr int s_nGMonth      = 6;
    static constexpr int s_nGDayOfMonth = 30;

    static constexpr int s_nLYear      = 0;
    static constexpr int s_nLMonth     = 0;
    static constexpr int s_nLDayOfMont = 0;
};


#endif //CHINA_LUNAR_DATETIME_CH_LUNAR_H
