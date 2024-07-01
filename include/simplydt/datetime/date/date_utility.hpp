
#ifndef SIMPLYDTLIB_L_DATE_UTILITY_H_
#define SIMPLYDTLIB_L_DATE_UTILITY_H_



#include<cstdint>


namespace simplydt {

	/* Returns true if provided year is a leap year */
	bool isLeapYear(uint16_t year) noexcept
	{
		return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
	}

	/* Returns total number of days in provided year-month combination */
	uint16_t getTotalDaysInMonth(uint16_t year, uint16_t month) noexcept
	{
		/*****************************************************************************\
		*             vvv           AI GENERATED CODE BELOW           vvv             *
		\*****************************************************************************/

		// February
		if (month == 2) {
			if (isLeapYear(year))
				return 29;// Leap year
			else
				return 28;// Non-leap year
		}

		// April, June, September and November
		else if (month == 4 || month == 6 || month == 9 || month == 11)
			return 30;

		// January, March, May, July, August, October and December
		return 31;

		/*****************************************************************************\
		*             ^^^           AI GENERATED CODE ABOVE           ^^^             *
		\*****************************************************************************/
	}

	/* Returns total number of days in provided year */
	uint16_t getTotalDaysInYear(uint16_t year) noexcept
	{
		uint16_t totalDays{ 0 };

		for (uint8_t month{ 1 }; month <= (uint8_t)12U; ++month) {

			totalDays += getTotalDaysInMonth(year, month);

		}

		return totalDays;
	}

	/* Returns zero-based century representation of provided year */
	uint16_t getYearZeroBasedCentury(uint16_t year) noexcept
	{
		return (year / (uint16_t)100);
	}

	/* Returns year in century representation of provided year */
	uint16_t getYearInCentury(uint16_t year) noexcept
	{
		return (year % (uint16_t)100);
	}

	/* Returns day of week index from provided date */
	uint8_t getDayOfWeekIndex(uint16_t year, uint16_t month, uint16_t day) noexcept
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

}



#endif // SIMPLYDTLIB_L_DATE_UTILITY_H_
