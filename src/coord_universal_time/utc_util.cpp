
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
	JulianCalendar::JDN multi;

	if (jdn >= (JulianCalendar::JDN)1.)
		multi = jdn - std::floor(jdn);
	else
		multi = jdn;

	if (multi < (JulianCalendar::JDN).5)
		multi += (JulianCalendar::JDN).5;
	else
		multi -= (JulianCalendar::JDN).5;

	JulianCalendar::JDN totalSeconds{ (multi * (JulianCalendar::JDN)86'400.) };

	if (totalSeconds) {
		time.hour = static_cast<uint8_t>((totalSeconds / (JulianCalendar::JDN)3'600.));
		totalSeconds -= ((JulianCalendar::JDN)time.hour * (JulianCalendar::JDN)3'600.);
	}

	if (totalSeconds) {
		time.minute = static_cast<uint8_t>((totalSeconds / (JulianCalendar::JDN)60.));
		totalSeconds -= ((JulianCalendar::JDN)time.minute * (JulianCalendar::JDN)60.);
	}

	// NOTE: Rounding issue when dealing with 11:59:59 PM
	if (totalSeconds)
		time.second = static_cast<uint8_t>(std::round(totalSeconds));

	// Corrects rounding issue when dealing with 11:59:59 PM
	// NOTE: (Temporary until precision update)
	if (time.hour == (uint8_t)23 && time.minute == (uint8_t)59) {
		if (time.second == (uint8_t)60 && multi < (JulianCalendar::JDN)1.)
			--time.second;
	}

	// Adjustments for rounding errors
	if (time.second == (uint8_t)60) {
		time.second = 0;
		time.minute += (uint8_t)1;
	}

	if (time.minute == (uint8_t)60) {
		time.minute = 0;
		time.hour += (uint8_t)1;
	}

	if (time.hour == (uint8_t)24)
		time.hour = 0;
}
