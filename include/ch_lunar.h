//
// Created by Mithwindy on 07/05/2018.
//

#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <array>
#include <map>
#include <string>

class CChLunarDateTime {
public:
    CChLunarDateTime() = default;

//    explicit
//    CChLunarDateTime(const unsigned long long nVal)
//    {
//        m_nTimeIndex = nVal;
//		CalGDateTime();
//		CalLDateTime();
//    }

    //CChLunarDateTime(const int nGYear, const int nGMonthOfYear, const int nGDayOfMonth)
    //{
    //    m_nGYear = nGYear;
    //    m_nGMonthOfYear = nGMonthOfYear;
    //    m_nGDayOfMonth = nGDayOfMonth;
    //}

    //CChLunarDateTime(const int nGYear,
    //            const int nGMonthOfYear,
    //            const int nGDayOfMonth,
    //            const int nGHourOfDay,
    //            const int nGMinuteOfHour,
    //            const int nGSecondOfMinute,
    //            const int nGMilliOfSecond)
    //{
    //    m_nGYear = nGYear;
    //    m_nGMonthOfYear = nGMonthOfYear;
    //    m_nGDayOfMonth = nGDayOfMonth;
    //    m_nHourOfDay = nGHourOfDay;
    //    m_nMinuteOfHour = nGMinuteOfHour;
    //    m_nSecondOfMinute = nGSecondOfMinute;
    //    m_nMilliOfSecond = nGMilliOfSecond;
    //}

    ~CChLunarDateTime() = default;

public:

    void
    Reset() {
        m_nTimeIndex = std::numeric_limits<unsigned long long>::max();

        m_nGYear = -1;
        m_nGMonthOfYear = -1;
        m_nGDayOfMonth = -1;
        m_nGDayOfWeek = -1;

        m_nHourOfDay = -1;
        m_nMinuteOfHour = -1;
        m_nSecondOfMinute = -1;
        m_nMilliOfSecond = -1;

        m_nLYear = -1;
        m_nLMonthOfYear = -1;
        m_nLDayOfMonth = -1;
    }

    void
    SetVal(const unsigned long long nVal) {
        m_nTimeIndex = nVal;
        if (!CheckVal()) {
            Reset();
            return;
        }
        CalGDateTime();
        CalLDateTime();
    }

    bool
    CheckVal() const {
        auto nGBegin = s_mapGday2Ym.cbegin()->first;
        auto nGEnd = s_mapGday2Ym.cend()->first;
        if (m_nTimeIndex < nGBegin || m_nTimeIndex > nGEnd) {
            return false;
        }
        auto nLBegin = s_mapLday2Ym.cbegin()->first;
        auto nLEnd = s_mapLday2Ym.cend()->first;
        if (m_nTimeIndex < nLBegin || m_nTimeIndex > nLEnd) {
            return false;
        }
        return true;
    }

    bool
    Set(const int nGYear, const int nGMonthOfYear, const int nGDayOfMonth) {
        m_nGYear = nGYear;
        m_nGMonthOfYear = nGMonthOfYear;
        m_nGDayOfMonth = nGDayOfMonth;

        m_nHourOfDay = 0;
        m_nMinuteOfHour = 0;
        m_nSecondOfMinute = 0;
        m_nMilliOfSecond = 0;

        if (!CheckGDateTimeValid()) {
            Reset();
            return false;
        }

        CalValBaseOnGDateTime();
        CalDayOfWeekOnVal();
        return true;
    }

    static unsigned int
    GetLVal(const int nGYear) {
        if (nGYear > 200 + s_nMinGYear || nGYear < s_nMinGYear) {
            return 0u;
        }
        unsigned val[201] = {
                0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2, //1900-1909
                0x04ae0, 0x0a5b6, 0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977, //1910-1919
                0x04970, 0x0a4b0, 0x0b4b5, 0x06a50, 0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970, //1920-1929
                0x06566, 0x0d4a0, 0x0ea50, 0x06e95, 0x05ad0, 0x02b60, 0x186e3, 0x092e0, 0x1c8d7, 0x0c950, //1930-1939
                0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2, 0x0a950, 0x0b557, //1940-1949
                0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5b0, 0x14573, 0x052b0, 0x0a9a8, 0x0e950, 0x06aa0, //1950-1959
                0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0, //1960-1969
                0x096d0, 0x04dd5, 0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b6a0, 0x195a6, //1970-1979
                0x095b0, 0x049b0, 0x0a974, 0x0a4b0, 0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570, //1980-1989
                0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58, 0x055c0, 0x0ab60, 0x096d5, 0x092e0, //1990-1999
                0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0, 0x092d0, 0x0cab5, //2000-2009
                0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930, //2010-2019
                0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530, //2020-2029
                0x05aa0, 0x076a3, 0x096d0, 0x04afb, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45, //2030-2039
                0x0b5a0, 0x056d0, 0x055b2, 0x049b0, 0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0, //2040-2049
                0x14b63, 0x09370, 0x049f8, 0x04970, 0x064b0, 0x168a6, 0x0ea50, 0x06b20, 0x1a6c4, 0x0aae0, //2050-2059
                0x0a2e0, 0x0d2e3, 0x0c960, 0x0d557, 0x0d4a0, 0x0da50, 0x05d55, 0x056a0, 0x0a6d0, 0x055d4, //2060-2069
                0x052d0, 0x0a9b8, 0x0a950, 0x0b4a0, 0x0b6a6, 0x0ad50, 0x055a0, 0x0aba4, 0x0a5b0, 0x052b0, //2070-2079
                0x0b273, 0x06930, 0x07337, 0x06aa0, 0x0ad50, 0x14b55, 0x04b60, 0x0a570, 0x054e4, 0x0d160, //2080-2089
                0x0e968, 0x0d520, 0x0daa0, 0x16aa6, 0x056d0, 0x04ae0, 0x0a9d4, 0x0a2d0, 0x0d150, 0x0f252, //2090-2099
                0x0d520,                                                                                  //2100-2100
        };
        return val[nGYear - s_nMinGYear];
    }

    static void
    Init() {
        BuildGMap();
        BuildLMap();
        BuildInverseGMap();
        BuildInverseLMap();
    }

    static void
    BuildGMap() {
        unsigned long long nIndex = 0;
        int nGMonthOfYear = s_nGMonth;
        int nGDayOfMonth = s_nGDayOfMonth;
        int nGYear = s_nGYear;
        int nGMonthDayMax = GetGMonthMaxDay(nGMonthOfYear, nGYear);
        s_mapGday2Ym[0] = std::make_tuple(nGYear, nGMonthOfYear);
        while (nGYear < s_nMaxGYear) {
            nIndex += s_nMilliSecondIn1Day;
            ++nGDayOfMonth;
            if (nGDayOfMonth > nGMonthDayMax) {
                nGDayOfMonth = 1;
                ++nGMonthOfYear;
                nGMonthDayMax = GetGMonthMaxDay(nGMonthOfYear, nGYear);
                if (nGMonthOfYear > 12) {
                    nGMonthOfYear = 1;
                    ++nGYear;
                }
                s_mapGday2Ym[nIndex] = std::make_tuple(nGYear, nGMonthOfYear);
            }
        }
    }

    static void
    BuildLMap() {
        unsigned long long nIndex = 0;
        int nLMonthOfYear = s_nLMonth;
        int nLDayOfMonth = s_nLDayOfMont;
        int nLYear = s_nLYear;
        int nGYear = s_nGYear;
        auto mapLYearMonthDayCount = GetLYearMonthDayMap(nGYear);
        int nLMonthDayMax = mapLYearMonthDayCount[nLMonthOfYear];
        if (nLMonthDayMax == 0) {
            return;
        }
        const auto nMaxMilli = static_cast<unsigned long long>(s_nFullMilliSec);
        while (nIndex < nMaxMilli) {
            nIndex += s_nMilliSecondIn1Day;
            ++nLDayOfMonth;
            if (nLDayOfMonth > nLMonthDayMax) {
                bool bNewYear = false;
                nLDayOfMonth = 1;
                if (nLMonthOfYear > 12) {
                    nLMonthOfYear -= 11;
                } else {
                    const auto it = mapLYearMonthDayCount.find(nLMonthOfYear + 12);
                    if (it == mapLYearMonthDayCount.end()) {
                        ++nLMonthOfYear;
                        if (nLMonthOfYear == 13) {
                            bNewYear = true;
                        }
                    } else {
                        nLMonthOfYear += 12;
                    }
                }
                if (bNewYear) {
                    nLMonthOfYear = 1;
                    ++nLYear;
                    ++nGYear;
                    mapLYearMonthDayCount = GetLYearMonthDayMap(nGYear);
                }
                nLMonthDayMax = mapLYearMonthDayCount[nLMonthOfYear];
                if (nLMonthDayMax == 0) {
                    return;
                }
                s_mapLday2Ym[nIndex] = std::make_tuple(nLYear, nLMonthOfYear);
            }
        }
    }

    static void
    BuildInverseGMap() {
        for (const auto &pair : s_mapGday2Ym) {
            const auto &tupGYM = pair.second;
            const auto nIndexNew = std::get<0>(tupGYM) * 100 + std::get<1>(tupGYM);
            s_mapGYM2Day[nIndexNew] = pair.first;
        }
    }

    static void
    BuildInverseLMap() {
        for (const auto &pair : s_mapLday2Ym) {
            const auto &tupGYM = pair.second;
            const auto nIndexNew = std::get<0>(tupGYM) * 100 + std::get<1>(tupGYM);
            s_mapLYM2Day[nIndexNew] = pair.first;
        }
    }

    static int
    GetGMonthMaxDay(const int nGMonth, const int nGYear) {
        if (nGMonth == 1 || nGMonth == 3 || nGMonth == 5 || nGMonth == 7 || nGMonth == 8 || nGMonth == 10 ||
            nGMonth == 12) {
            return 31;
        }
        if (nGMonth != 2)
        {
            return 30;
        }
        if (IsLeapGYear(nGYear)) {
            return 29;
        }
        return 28;
    }

    static std::map<int, int>
    GetLYearMonthDayMap(const int nLYear) {
        std::map<int, int> mapLMonth2DayCount;
        if (nLYear > s_nMaxGYear || nLYear < s_nMinGYear) {
            return mapLMonth2DayCount;
        }
        unsigned nLVal = GetLVal(nLYear);
        const unsigned nLeapLMonth = nLVal & 0x000f;
        nLVal = nLVal >> 4;
        int nLMonth = 12;
        unsigned nTmp;
        for (; nLMonth > 0; --nLMonth) {
            nTmp = nLVal & 0x0001;
            if (nTmp > 0) {
                mapLMonth2DayCount[nLMonth] = 30;
            } else {
                mapLMonth2DayCount[nLMonth] = 29;
            }
            nLVal = nLVal >> 1;
        }
        if (nLeapLMonth > 0 && nLeapLMonth <= 12) {
            nLMonth = static_cast<int>(nLeapLMonth) + 12;
            nTmp = nLVal & 0x0001;
            if (nTmp > 0) {
                mapLMonth2DayCount[nLMonth] = 30;
            } else {
                mapLMonth2DayCount[nLMonth] = 29;
            }
        }
        return mapLMonth2DayCount;
    }

    static bool
    IsLeapGYear(const int nYear) {
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

    void
    CalGDateTime() {
        auto it = s_mapGday2Ym.lower_bound(m_nTimeIndex);
        if (it == s_mapGday2Ym.end() || it == s_mapGday2Ym.begin()) {
            return;
        }
        --it;
        const auto &tupGym = it->second;
        m_nGYear = std::get<0>(tupGym);
        m_nGMonthOfYear = std::get<1>(tupGym);
        const auto nRemainderMilliSecondDays = (m_nTimeIndex - it->first);
        m_nGDayOfMonth = static_cast<int>(nRemainderMilliSecondDays / s_nMilliSecondIn1Day + 1);
        const auto nRemainderMilliSecondHours = nRemainderMilliSecondDays % s_nMilliSecondIn1Day;
        m_nHourOfDay = static_cast<int>(nRemainderMilliSecondHours / s_nMilliSecondIn1Hour);
        const auto nRemainderMilliSecondMinutes = nRemainderMilliSecondHours % s_nMilliSecondIn1Hour;
        m_nMinuteOfHour = static_cast<int>(nRemainderMilliSecondMinutes / s_nMilliSecondIn1Minute);
        const auto nRemainderMilliSecondSeconds = nRemainderMilliSecondMinutes % s_nMilliSecondIn1Minute;
        m_nSecondOfMinute = static_cast<int>(nRemainderMilliSecondSeconds / s_nMilliSecondIn1Minute);
        m_nMilliOfSecond = static_cast<int>(nRemainderMilliSecondSeconds % s_nMilliSecondIn1Minute);
        m_nGDayOfWeek = static_cast<int>((m_nTimeIndex / s_nMilliSecondIn1Day + s_nGDayOfWeek) % 7);
    }

    void
    CalLDateTime() {
        auto it = s_mapLday2Ym.lower_bound(m_nTimeIndex);
        if (it == s_mapLday2Ym.end() || it == s_mapLday2Ym.begin()) {
            return;
        }
        --it;
        const auto &tupLYM = it->second;
        m_nLYear = std::get<0>(tupLYM);
        m_nLMonthOfYear = std::get<1>(tupLYM);
        const auto nRemainderMilliSecondDays = (m_nTimeIndex - it->first);
        m_nLDayOfMonth = static_cast<int>(nRemainderMilliSecondDays / s_nMilliSecondIn1Day + 1);
    }

    bool
    CalValBaseOnGDateTime() {
        const auto it = s_mapGYM2Day.find(m_nGYear * 100 + m_nGMonthOfYear);
        if (it == s_mapGYM2Day.end()) {
            return false;
        }
        m_nTimeIndex = it->second;
        m_nTimeIndex += static_cast<unsigned long long>((m_nGDayOfMonth - 1) * s_nMilliSecondIn1Day) + static_cast<
                unsigned long long>(m_nHourOfDay * s_nMilliSecondIn1Hour) +
                        static_cast<unsigned long long>(m_nMinuteOfHour * s_nMilliSecondIn1Hour) + static_cast<unsigned
        long long>(m_nMinuteOfHour * s_nMilliSecondIn1Minute)
                        + static_cast<unsigned long long>(m_nMilliOfSecond);
        return true;
    }

    bool
    CalDayOfWeekOnVal() {
        m_nGDayOfWeek =
                ((m_nTimeIndex + static_cast<unsigned long long>(s_nGDayOfWeek) *
                                 static_cast<unsigned long long>(s_nMilliSecondIn1Day)) %
                 static_cast<unsigned long long>(s_nMilliSecondIn1Week)) /
                static_cast<unsigned long long>(s_nMilliSecondIn1Day);
    }

    //bool
    //SetVal(const CLDateTime& oLDateTIme)
    //{
    //    //const auto it = s_mapGYM2Day.find(oLDateTIme.m_nGYear * 100 + oLDateTIme.m_nGMonthOfYear);
    //    //if (it == s_mapGYM2Day.end())
    //    //{
    //    //	return false;
    //    //}
    //    //auto nIndex = it->second;
    //    //nIndex += static_cast<unsigned long long>(oLDateTIme.m_nGDayOfMonth * s_nMilliSecondIn1Day) + static_cast<
    //    //	unsigned long long>(oLDateTIme.m_nGHourOfDay * s_nMilliSecondIn1Hour) +
    //    //	static_cast<unsigned long long>(oLDateTIme.m_nGMinuteOfHour * s_nMilliSecondIn1Hour) + static_cast<unsigned
    //    //	long long>(oLDateTIme.m_nGMinuteOfHour * s_nMilliSecondIn1Minute)
    //    //	+ static_cast<unsigned long long>(oLDateTIme.m_nGMilliOfSecond);
    //    //SetVal(nIndex);
    //    return true;
    //}


    bool
    CheckGDateTimeValid() const {
        if (m_nGYear > s_nMaxGYear || m_nGYear < s_nMinGYear) {
            return false;
        }
        if (m_nGMonthOfYear < 1 || m_nGMonthOfYear > s_nMonthIn1GYear) {
            return false;
        }
        if (m_nGDayOfMonth < 1 || m_nGDayOfMonth > GetGMonthMaxDay(m_nGMonthOfYear, m_nGYear)) {
            return false;
        }
        if (m_nHourOfDay < 0 || m_nHourOfDay > s_nHourIn1Day) {
            return false;
        }
        if (m_nMinuteOfHour < 0 || m_nMinuteOfHour > s_nMinuteIn1Hour) {
            return false;
        }
        if (m_nSecondOfMinute < 0 || m_nSecondOfMinute > s_nSecondIn1Minute) {
            return false;
        }
        if (m_nMilliOfSecond < 0 || m_nMilliOfSecond > s_nMilliSecondIn1Second) {
            return false;
        }
        return true;
    }

    unsigned long long
    GetVal() const {
        return m_nTimeIndex;
    }

    std::string
    LDateTimeToString() const {
        std::string str;
        str += "chinese lunar \nyear[";
        str += std::to_string(m_nLYear) + "] ";
        str += "monthOfYear[";
        str += std::to_string(m_nLMonthOfYear) + "] ";
        str += "dayOfMonth[";
        str += std::to_string(m_nLDayOfMonth) + "] \n";
        return str;
    }

    std::string
    GDateTimeToString() const {
        std::string str;
        str += "georgia \nyear[";
        str += std::to_string(m_nGYear) + "] ";
        str += "monthOfYear[";
        str += std::to_string(m_nGMonthOfYear) + "] ";
        str += "dayOfMonth[";
        str += std::to_string(m_nGDayOfMonth) + "] ";
        str += "dayOfWeek[";
        str += std::to_string(m_nGDayOfWeek) + "] ";
        str += "hourOfDay[";
        str += std::to_string(m_nHourOfDay) + "] \n";
        str += "minuteOfHour[";
        str += std::to_string(m_nMinuteOfHour) + "] ";
        str += "secondOfMinute[";
        str += std::to_string(m_nSecondOfMinute) + "] ";
        str += "milliOfSecond[";
        str += std::to_string(m_nMilliOfSecond) + "] ";
        str += "val[";
        str += std::to_string(m_nTimeIndex) + "] \n";
        return str;
    }

    static std::string
    StaticDataToString() {
        std::string str;
        str += "s_mapGday2Ym \n";
        for (const auto &pair : s_mapGday2Ym) {
            auto &nIndex = pair.first;
            auto &tupYm = pair.second;
            const auto nGYear = std::get<0>(tupYm);
            const auto nGMonth = std::get<1>(tupYm);
            str += "index[" + std::to_string(nIndex) + "] gyear,gmonth[" + std::to_string(nGYear) + "," + std::
            to_string(nGMonth) + "]" + "\n";
        }
        str += "s_mapLday2Ym \n";
        for (const auto &pair : s_mapLday2Ym) {
            auto &nIndex = pair.first;
            auto &tupYm = pair.second;
            const auto nGYear = std::get<0>(tupYm);
            const auto nGMonth = std::get<1>(tupYm);
            str += "index[" + std::to_string(nIndex) + "] lyear,lmonth[" + std::to_string(nGYear) + "," + std::
            to_string(nGMonth) + "]" + "\n";
        }
        str += "s_mapGYM2Day \n";
        for (const auto &pair : s_mapGYM2Day) {
            str += "index[" + std::to_string(pair.first) + "] inverse index[" + std::to_string(pair.second) + "]\n";
        }
        str += "s_mapLYM2Day \n";
        for (const auto &pair : s_mapLYM2Day) {
            str += "index[" + std::to_string(pair.first) + "] inverse index[" + std::to_string(pair.second) + "]\n";
        }
        return str;
    }

public:
    unsigned long long m_nTimeIndex = std::numeric_limits<unsigned long long>::max();

    int m_nGYear = -1;
    int m_nGMonthOfYear = -1;
    int m_nGDayOfMonth = -1;
    int m_nGDayOfWeek = -1;

    int m_nHourOfDay = -1;
    int m_nMinuteOfHour = -1;
    int m_nSecondOfMinute = -1;
    int m_nMilliOfSecond = -1;

    int m_nLYear = -1;
    int m_nLMonthOfYear = -1;
    int m_nLDayOfMonth = -1;

    static std::map<unsigned long long, std::tuple<int, int>> s_mapGday2Ym;
    static std::map<unsigned long long, std::tuple<int, int>> s_mapLday2Ym;
    static std::map<int, unsigned long long> s_mapGYM2Day;
    static std::map<int, unsigned long long> s_mapLYM2Day;

    static constexpr int s_nGYear = 1970;
    static constexpr int s_nGMonth = 1;
    static constexpr int s_nGDayOfMonth = 1;
    static constexpr int s_nGDayOfWeek = 4;

    static constexpr int s_nLYear = s_nGYear + 2697;
    static constexpr int s_nLMonth = 11;
    static constexpr int s_nLDayOfMont = 24;

    static constexpr int s_nMilliSecondIn1Second = 1000;
    static constexpr int s_nSecondIn1Minute = 60;
    static constexpr int s_nMinuteIn1Hour = 60;
    static constexpr int s_nHourIn1Day = 24;
    static constexpr int s_nMonthIn1GYear = 12;
    static constexpr int s_nDayIn1Week = 7;

    static constexpr int s_nMilliSecondIn1Minute = s_nMilliSecondIn1Second * s_nSecondIn1Minute;
    static constexpr int s_nMilliSecondIn1Hour = s_nMilliSecondIn1Minute * s_nMinuteIn1Hour;
    static constexpr int s_nMilliSecondIn1Day = s_nMilliSecondIn1Hour * s_nHourIn1Day;
    static constexpr int s_nMilliSecondIn1Week = s_nMilliSecondIn1Day * s_nDayIn1Week;

    static constexpr int s_nMinGYear = 1970;
    static constexpr int s_nMaxGYear = 2037;

    static constexpr unsigned long long s_nFullMilliSec = (static_cast<unsigned long long>(s_nMaxGYear) -
                                                           static_cast<unsigned long long>(s_nMinGYear)) * 365u *
                                                          static_cast<unsigned long long>(s_nMilliSecondIn1Day);
};

std::map<unsigned long long, std::tuple<int, int>> CChLunarDateTime::s_mapGday2Ym;
std::map<unsigned long long, std::tuple<int, int>> CChLunarDateTime::s_mapLday2Ym;
std::map<int, unsigned long long>                  CChLunarDateTime::s_mapGYM2Day;
std::map<int, unsigned long long>                  CChLunarDateTime::s_mapLYM2Day;
