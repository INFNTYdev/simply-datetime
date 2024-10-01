
#ifndef SIMPLYDTLIB_JDN_UTIL_H_
#define SIMPLYDTLIB_JDN_UTIL_H_



#include<cmath>
#include<cstdint>


/* Decimal based continuous time system */
namespace JulianDateSystem {

	/* Julian Day Number (JDN) */
	using JDN = double;

	
	/* Returns gregorian date as Julian Day Number */
	JDN gregorianToJDN(const uint16_t& year, const uint8_t& month, const uint8_t& day) noexcept;

	/* Returns universal coordinated time as Julian Day Number */
	JDN utcToJDN(const uint8_t& hour, const uint8_t& minute, const uint8_t& second) noexcept;

}



#endif // SIMPLYDTLIB_JDN_UTIL_H_
