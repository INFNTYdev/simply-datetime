
#include"simplydt/gregorian_calendar/gregorian_util.hpp"


//  SimplyDt::GregorianCalendar::Util : FREE

bool SimplyDt::GregorianCalendar::Util::isValidYear(const uint16_t& year) noexcept
{
    // For compatibility with the standard library,
    // 1970 stands as the minimum representable year
    return year >= (uint16_t)1970;
}

bool SimplyDt::GregorianCalendar::Util::isValidMonth(const uint8_t& month) noexcept
{
    return month >= (uint8_t)1 && month <= (uint8_t)12;
}

bool SimplyDt::GregorianCalendar::Util::isValidDay(const uint8_t& day) noexcept
{
    return day >= (uint8_t)1 && day <= (uint8_t)31;
}

bool SimplyDt::GregorianCalendar::Util::isLeapYear(const uint16_t& year) noexcept
{
	return ((year % (uint16_t)4) == 0 && (year % (uint16_t)100 != 0 || year % (uint16_t)400 == 0));
}

uint8_t SimplyDt::GregorianCalendar::Util::getMonthTotalDays(const uint16_t& year, const uint8_t& month) noexcept
{

    /*****************************************************************************\
    *             vvv           AI GENERATED CODE BELOW           vvv             *
    \*****************************************************************************/

    if (!isValidMonth(month))
        return 0;

    switch (month) {
    // February
    case (uint8_t)2:
        switch (isLeapYear(year)) {
        case true:
            return (uint8_t)29;    // Leap year

        default:
            return (uint8_t)28;    // Non-leap year
        }

    // April, June, September and November
    case (uint8_t)4:
    case (uint8_t)6:
    case (uint8_t)9:
    case (uint8_t)11:
        return (uint8_t)30;

    // January, March, May, July, August, October and December
    default:
        return (uint8_t)31;
    }

    /*****************************************************************************\
    *             ^^^           AI GENERATED CODE ABOVE           ^^^             *
    \*****************************************************************************/
    
}

uint16_t SimplyDt::GregorianCalendar::Util::getYearTotalDays(const uint16_t& year) noexcept
{
    uint16_t totalDays{ 0 };

    for (uint8_t month{ 1 }; month <= (uint8_t)12; ++month)
        totalDays += getMonthTotalDays(year, month);

    return totalDays;
}

uint8_t SimplyDt::GregorianCalendar::Util::getMonthIndex(const uint8_t& month) noexcept
{
    if (!isValidMonth(month))
        return 0;
    
    return month - (uint8_t)1;
}

const char* SimplyDt::GregorianCalendar::Util::getMonth(const uint8_t& month) noexcept
{
    if (!isValidMonth(month))
        return nullptr;

    return SimplyDt::GregorianCalendar::Months[getMonthIndex(month)];
}

std::string_view SimplyDt::GregorianCalendar::Util::getMonthAbbrev(const uint8_t& month) noexcept
{
    if (!isValidMonth(month))
        return nullptr;
    
    std::string_view original{ SimplyDt::GregorianCalendar::Months[getMonthIndex(month)] };

    return original.substr(0, (size_t)3);
}

uint8_t SimplyDt::GregorianCalendar::Util::getDayOfWeekIndex(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept
{
    if (!isValidMonth(month) || !isValidDay(day))
        return 0;

    /*****************************************************************************\
    *             vvv           AI GENERATED CODE BELOW           vvv             *
    \*****************************************************************************/

    // Tomohiko Sakamoto’s Algorithm (modified)

    uint16_t calcYear{ year };
    uint8_t calcMonth{ month };

    if (month < 3) {
        calcMonth += 12;
        calcYear--;
    }

    // Adjustments for leap years
    int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    if (isLeapYear(year)) {
        t[0]--;    // January adjustment in leap years
        t[1]--;    // February adjustment in leap years
    }

    // I don't like this...
    int h = (day + t[month - 1] + year + year / 4 - year / 100 + year / 400) % 7;

    // Adjust for zero-based indexing (Sunday = 0, ..., Saturday = 6)
    if (h < 0)
        h += 7;
    
    // One ugly hack for January and February :(
    // This fixes the 3 offset for Jan and 1 offset for Feb
    if ((month == 13) || (month == 14)) {
        switch (month) {
        case (uint8_t)13:
            switch (h < 4) {
            case true:
                h = (7 - (4 - h));
                break;

            default:
                h -= 4;
            }
            
            break;

        case (uint8_t)14:
            switch (h == 0) {
            case true:
                h = 6;
                break;

            default:
                h -= 1;
            }
        }
    }

    return static_cast<uint8_t>(h);

    /*****************************************************************************\
    *             ^^^           AI GENERATED CODE ABOVE           ^^^             *
    \*****************************************************************************/

}

const char* SimplyDt::GregorianCalendar::Util::getDayOfWeek(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept
{
    if (!isValidMonth(month) || !isValidDay(day))
        return nullptr;

    return SimplyDt::GregorianCalendar::DaysOfWeek[getDayOfWeekIndex(year, month, day)];
}

std::string_view SimplyDt::GregorianCalendar::Util::getDayOfWeekAbbrev(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept
{
    if (!isValidMonth(month) || !isValidDay(day))
        return nullptr;

    std::string_view original{ SimplyDt::GregorianCalendar::DaysOfWeek[getDayOfWeekIndex(year, month, day)] };

    return original.substr(0, (size_t)3);
}

bool SimplyDt::GregorianCalendar::Util::jdnToDate(const SimplyDt::JulianCalendar::JDN& jdn, SimplyDt::GregorianCalendar::Date& date) noexcept
{
    //

    return false;
}
