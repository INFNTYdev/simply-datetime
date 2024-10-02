
#ifndef SIMPLYDTLIB_GREGORIAN_CALENDAR_UTIL_H_
#define SIMPLYDTLIB_GREGORIAN_CALENDAR_UTIL_H_



#include<array>
#include"simplydt/common/julian_date_system/jdn_util.hpp"


/* Standard civil calendar system */
namespace GregorianCalendar {

	/* Julian Day Number (JDN) */
	using JDN = JulianDateSystem::JDN;

	typedef struct _GREGORIAN_DATE_STRUCT {
		const uint16_t year;
		const uint8_t month;
		const uint8_t day;
	} GregorianDate;


	/* Month labels */
	const std::array<const char*, 12> Months{
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	/* Day of week labels */
	const std::array<const char*, 7> DaysOfWeek{
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday"
	};


	/* Returns true if provided year is a leap year */
	bool isLeapYear(const uint16_t& year) noexcept;

	/* Returns total number of days in provided year-month combination */
	uint8_t getTotalDaysInMonth(const uint16_t& year, const uint8_t& month) noexcept;

	/* Returns total number of days in provided year-month combination */
	uint8_t getTotalDaysInMonth(const GregorianDate& date) noexcept;

	/* Returns total number of days in provided year */
	uint16_t getTotalDaysInYear(const uint16_t& year) noexcept;

	/* Returns day of week index of provided date */
	uint8_t getDayOfWeekIndex(uint16_t year, uint8_t month, uint8_t day) noexcept;

	/* Returns day of week index of provided date */
	uint8_t getDayOfWeekIndex(const GregorianDate& date) noexcept;

	/* Returns day of week literal from provided date */
	const char* getDayOfWeek(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

	/* Returns day of week literal from provided date */
	const char* getDayOfWeek(const GregorianDate& date) noexcept;

	/* Returns month index of provided month */
	uint8_t getMonthIndex(const uint8_t& month) noexcept;

	/* Returns month literal from provided month */
	const char* getMonthTitle(const uint8_t& month) noexcept;

	/* Evaluate Gregorian date from JDN */
	GregorianDate interpretJDNDate(const JDN& jdn) noexcept;

	/* Evaluate Gregorian year from JDN */
	uint16_t interpretJDNYear(const JDN& jdn) noexcept;

	/* Evaluate Gregorian month from JDN */
	uint8_t interpretJDNMonth(const JDN& jdn) noexcept;

	/* Evaluate Gregorian day from JDN */
	uint8_t interpretJDNDay(const JDN& jdn) noexcept;

}



#endif // SIMPLYDTLIB_GREGORIAN_CALENDAR_UTIL_H_
