
#ifndef SIMPLYDTLIB_UTC_UTIL_H_
#define SIMPLYDTLIB_UTC_UTIL_H_



#include<array>
#include"simplydt/common/julian_date_system/jdn_util.hpp"


/* Coordinated Universal Time system (UTC) */
namespace CoordinatedUniversalTime {

	/* Julian Day Number (JDN) */
	using JDN = JulianDateSystem::JDN;

	/* Coordinated Universal Time (UTC) */
	typedef struct _UTC_TIME_STRUCT {
		const uint8_t hour;
		const uint8_t minute;
		const uint8_t second;
	} UTCTime;


	/* Time phase labels */
	const std::array<const char*, 2> Phases{
		"AM",
		"PM"
	};


	/* Returns decimal percentage of day completed */
	JDN timeInDay(const uint8_t& hour, const uint8_t& minute, const uint8_t& second) noexcept;

	/* Evaluate UTC from JDN */
	UTCTime interpretJDNTime(const JDN& jdn) noexcept;

	/* Evaluate UTC hour from JDN */
	uint8_t interpretJDNHour(const JDN& jdn) noexcept;

	/* Evaluate UTC minute from JDN */
	uint8_t interpretJDNMinute(const JDN& jdn) noexcept;

	/* Evaluate UTC second from JDN */
	uint8_t interpretJDNSecond(const JDN& jdn) noexcept;

	/* Returns time phase index of provided time */
	uint8_t getPhaseIndex(const UTCTime& utc) noexcept;

	/* Returns time phase literal for provided time */
	const char* getPhaseStr(const UTCTime& utc) noexcept;

	/* Returns true if provided t2 time occurs before t1 time */
	bool isBefore(const UTCTime& t1, const UTCTime& t2) noexcept;

	/* Returns true if provided t2 time occurs after t1 time */
	bool isAfter(const UTCTime& t1, const UTCTime& t2) noexcept;

	/* Returns true if provided times reference same time point */
	bool isEqual(const UTCTime& t1, const UTCTime& t2) noexcept;

}



#endif // SIMPLYDTLIB_UTC_UTIL_H_
