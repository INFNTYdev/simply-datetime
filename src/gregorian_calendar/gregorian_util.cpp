
#include"simplydt/gregorian_calendar/gregorian_util.hpp"


//  SimplyDt::GregorianCalendar::Util : FREE

bool SimplyDt::GregorianCalendar::Util::isLeapYear(const uint16_t& year) noexcept
{
	return ((year % (uint16_t)4) == 0 && (year % (uint16_t)100 != 0 || year % (uint16_t)400 == 0));
}
