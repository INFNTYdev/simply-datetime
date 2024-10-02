
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

const char* GregorianCalendar::getDayOfWeek(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept
{
	return DaysOfWeek[getDayOfWeekIndex(year, month, day)];
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
	// Calculate intermediate values
	JDN a = ((JDN)4. * jdn + (JDN)274'277.);
	JDN b = std::floor(a / (JDN)146'097.);
	JDN c = std::floor((b * (JDN)3.) / (JDN)4.);

	JDN f = (jdn + (JDN)1'401. + c - (JDN)38.);
	JDN e = ((JDN)4. * f + (JDN)3.);
	JDN eSub = e - (std::floor(e / (JDN)1'461.) * (JDN)1'461.);
	JDN g = std::floor(eSub / (JDN)4.);
	JDN h = ((JDN)5. * g + (JDN)2.);
	JDN hSub = h - (std::floor(h / (JDN)153.) * (JDN)153.);
	JDN hSub2 = (std::floor(h / 153.) + (JDN)2.);
	hSub2 = hSub2 - (std::floor(hSub2 / (JDN)12.) * (JDN)12.);

	JDN gregorianDay{ (std::floor(hSub / (JDN)5.) + (JDN)1.) };
	JDN gregorianMonth{ (hSub2 + (JDN)1.) };
	JDN gregorianYear{
		std::floor(e / 1'461. - 4'716. + (14. - gregorianMonth) / 12.)
	};

	return GregorianDate{
		.year = static_cast<uint16_t>(gregorianYear),
		.month = static_cast<uint8_t>(gregorianMonth),
		.day = static_cast<uint8_t>(gregorianDay)
	};
}
 
uint16_t GregorianCalendar::interpretJDNYear(const JDN& jdn) noexcept
{
	GregorianDate date{ interpretJDNDate(jdn) };

	return date.year;
}

uint8_t GregorianCalendar::interpretJDNMonth(const JDN& jdn) noexcept
{
	GregorianDate date{ interpretJDNDate(jdn) };

	return date.month;
}

uint8_t GregorianCalendar::interpretJDNDay(const JDN& jdn) noexcept
{
	GregorianDate date{ interpretJDNDate(jdn) };

	return date.day;
}
