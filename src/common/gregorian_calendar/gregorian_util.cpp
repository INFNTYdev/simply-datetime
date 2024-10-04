
#include"simplydt/common/gregorian_calendar/gregorian_util.hpp"


bool GregorianCalendar::isLeapYear(const uint16_t& year) noexcept
{
	return ((year % 4Ui16) == 0 && (year % 100Ui16 != 0 || year % 400Ui16 == 0));
}

uint8_t GregorianCalendar::getTotalDaysInMonth(const uint16_t& year, const uint8_t& month) noexcept
{
	
	/*****************************************************************************\
	*             vvv           AI GENERATED CODE BELOW           vvv             *
	\*****************************************************************************/

	// February
	if (month == 2Ui8) {
		if (isLeapYear(year))
			return (uint8_t)29Ui8;// Leap year
		else
			return (uint8_t)28Ui8;// Non-leap year
	}

	// April, June, September and November
	else if (month == 4Ui8 || month == 6Ui8 || month == 9Ui8 || month == 11Ui8)
		return (uint8_t)30Ui8;

	// January, March, May, July, August, October and December
	return (uint8_t)31Ui8;

	/*****************************************************************************\
	*             ^^^           AI GENERATED CODE ABOVE           ^^^             *
	\*****************************************************************************/

}

uint8_t GregorianCalendar::getTotalDaysInMonth(const GregorianDate& date) noexcept
{
	return getTotalDaysInMonth(date.year, date.month);
}

uint16_t GregorianCalendar::getTotalDaysInYear(const uint16_t& year) noexcept
{
	uint16_t totalDays{ 0 };

	for (uint8_t month{ 1 }; month <= 12Ui8; ++month)
		totalDays += getTotalDaysInMonth(year, month);

	return totalDays;
}

uint8_t GregorianCalendar::getDayOfWeekIndex(uint16_t year, uint8_t month, uint8_t day) noexcept
{
	
	/*****************************************************************************\
	*             vvv           AI GENERATED CODE BELOW           vvv             *
	\*****************************************************************************/

	// Tomohiko Sakamoto’s Algorithm (modified)

	if (month < 3) {
		month += 12;
		year--;
	}

	// Adjustments for leap years
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	if (isLeapYear(year)) {
		t[0]--; // January adjustment in leap years
		t[1]--; // February adjustment in leap years
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
		case 13:
			if (h < 4)
				h = (7 - (4 - h));
			else
				h -= 4;

			break;

		case 14:
			if (h == 0)
				h = 6;
			else
				h -= 1;

			break;
		}
	}

	return h;

	/*****************************************************************************\
	*             ^^^           AI GENERATED CODE ABOVE           ^^^             *
	\*****************************************************************************/

}

uint8_t GregorianCalendar::getDayOfWeekIndex(const GregorianDate& date) noexcept
{
	return getDayOfWeekIndex(date.year, date.month, date.day);
}

const char* GregorianCalendar::getDayOfWeek(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept
{
	return DaysOfWeek[getDayOfWeekIndex(year, month, day)];
}

const char* GregorianCalendar::getDayOfWeek(const GregorianDate& date) noexcept
{
	return getDayOfWeek(date.year, date.month, date.day);
}

uint8_t GregorianCalendar::getMonthIndex(const uint8_t& month) noexcept
{
	if ((month >= 1Ui8) && (month <= 12Ui8))
		return (uint8_t)(month - 1Ui8);

	return (uint8_t)0Ui8;
}

const char* GregorianCalendar::getMonthTitle(const uint8_t& month) noexcept
{
	return Months[getMonthIndex(month)];
}

GregorianCalendar::GregorianDate GregorianCalendar::interpretJDNDate(const JDN& jdn) noexcept
{
	int Z = static_cast<int>(jdn + 0.5);
	int A = Z;

	if (Z >= 2299161) {
		int alpha = static_cast<int>((Z - 1867216.25) / 36524.25);
		A = Z + 1 + alpha - static_cast<int>(alpha / 4);
	}

	int B = A + 1524;
	int C = static_cast<int>((B - 122.1) / 365.25);
	int D = static_cast<int>(365.25 * C);
	int E = static_cast<int>((B - D) / 30.6001);

	int day = B - D - static_cast<int>(30.6001 * E);
	int month = (E < 14) ? E - 1 : E - 13;
	int year = (month > 2) ? C - 4716 : C - 4715;

	return GregorianDate{ static_cast<uint16_t>(year), static_cast<uint8_t>(month), static_cast<uint8_t>(day) };
}
 
uint16_t GregorianCalendar::interpretJDNYear(const JDN& jdn) noexcept
{
	return interpretJDNDate(jdn).year;
}

uint8_t GregorianCalendar::interpretJDNMonth(const JDN& jdn) noexcept
{
	return interpretJDNDate(jdn).month;
}

uint8_t GregorianCalendar::interpretJDNDay(const JDN& jdn) noexcept
{
	return interpretJDNDate(jdn).day;
}

bool GregorianCalendar::isBefore(const GregorianDate& d1, const GregorianDate& d2) noexcept
{
	if (d2.year < d1.year)
		return true;
	else if (d2.year > d1.year)
		return false;

	if (d2.month < d1.month)
		return true;
	else if (d2.month > d1.month)
		return false;

	if (d2.day < d1.day)
		return true;
	else
		return false;
}

bool GregorianCalendar::isAfter(const GregorianDate& d1, const GregorianDate& d2) noexcept
{
	if (d2.year > d1.year)
		return true;
	else if (d2.year < d1.year)
		return false;

	if (d2.month > d1.month)
		return true;
	else if (d2.month < d1.month)
		return false;

	if (d2.day > d1.day)
		return true;
	else
		return false;
}

bool GregorianCalendar::isEqual(const GregorianDate& d1, const GregorianDate& d2) noexcept
{
	if (d2.year != d1.year)
		return false;

	if (d2.month != d1.month)
		return false;

	if (d2.day != d1.day)
		return false;

	return true;
}
