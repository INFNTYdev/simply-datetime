
#include"simplydt/gregorian_calendar/gregorian_util.hpp"


//  SimplyDt::GregorianCalendar::Util : FREE

bool SimplyDt::GregorianCalendar::Util::isLeapYear(const uint16_t& year) noexcept
{
	return ((year % (uint16_t)4) == 0 && (year % (uint16_t)100 != 0 || year % (uint16_t)400 == 0));
}

uint8_t SimplyDt::GregorianCalendar::Util::getMonthTotalDays(const uint16_t& year, const uint8_t& month) noexcept
{
    
    /*****************************************************************************\
    *             vvv           AI GENERATED CODE BELOW           vvv             *
    \*****************************************************************************/

    // February
    if (month == (uint8_t)2) {
        if (isLeapYear(year))
            return (uint8_t)29;    // Leap year
        else
            return (uint8_t)28;    // Non-leap year
    }
    // April, June, September and November
    else if (month == (uint8_t)4 || month == (uint8_t)6 || month == (uint8_t)9 || month == (uint8_t)11)
        return (uint8_t)30;
    
    // January, March, May, July, August, October and December
    return (uint8_t)31;

    /*****************************************************************************\
    *             ^^^           AI GENERATED CODE ABOVE           ^^^             *
    \*****************************************************************************/
    
}
