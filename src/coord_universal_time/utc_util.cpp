
#include"simplydt/coord_universal_time/utc_util.hpp"


//	SimplyDt::CoordUniversalTime::Util : FREE

inline bool SimplyDt::CoordUniversalTime::Util::isValidHour(const uint8_t& hour) noexcept
{
	return hour <= (uint8_t)23;
}

inline bool SimplyDt::CoordUniversalTime::Util::isValidMinute(const uint8_t& minute) noexcept
{
	return minute <= (uint8_t)59;
}

inline bool SimplyDt::CoordUniversalTime::Util::isValidSecond(const uint8_t& second) noexcept
{
	return second <= (uint8_t)59;
}

inline bool SimplyDt::CoordUniversalTime::Util::isValidTime(const uint8_t& hour, const uint8_t& minute, const uint8_t& second) noexcept
{
	return (isValidHour(hour) && isValidMinute(minute) && isValidSecond(second));
}

void SimplyDt::CoordUniversalTime::Util::jdnToUtc(const SimplyDt::JulianCalendar::JDN& jdn, SimplyDt::CoordUniversalTime::Time& time) noexcept
{
	//
}
