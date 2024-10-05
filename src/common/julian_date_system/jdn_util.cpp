
#include"simplydt/common/julian_date_system/jdn_util.hpp"


JulianDateSystem::JDN JulianDateSystem::gregorianToJDN(const uint16_t& year,
	const uint8_t& month, const uint8_t& day) noexcept
{
	double A{ .0 };
	double D{ .0 };
	double E{ .0 };

	bool monthAdjust{ (month < (uint8_t)3Ui8) };

	// Adjustment for January and February
	switch (monthAdjust) {
	case true:
		A = std::floor(
			(uint16_t)(year - 1Ui16) / (double)100.
		);
		D = std::floor(
			(double)365.25 * (((uint32_t)year - 1Ui32) + (uint32_t)4'716Ui32)
		);
		E = std::floor(
			(double)30.6001 * (((uint32_t)month + 12Ui32) + (uint32_t)1Ui32)
		);
		break;

	default:
		A = std::floor(
			year / (double)100.
		);
		D = std::floor(
			(double)365.25 * ((uint32_t)year + (uint32_t)4'716Ui32)
		);
		E = std::floor(
			(double)30.6001 * ((uint32_t)month + (uint32_t)1Ui32)
		);
	}

	double B = std::floor(A / (double)4.);
	double C = std::floor((double)2. - A + B);

	return (C + day + D + E - (double)1'524.5);
}

JulianDateSystem::JDN JulianDateSystem::utcToJDN(const uint8_t& hour,
	const uint8_t& minute, const uint8_t& second) noexcept
{
	// Calculate time as a fraction of a day
	JDN timeJDN{
		((hour / (double)24.)
		+ (minute / (double)1'440.)
		+ (second / (double)86'400.))
	};

	// Adjust for JDN mid-day start
	if (hour < (uint8_t)12Ui8)
		timeJDN += (JDN).5;
	else
		timeJDN -= (JDN).5;

	return timeJDN;
}
