
#include"simplydt/common/coord_universal_time/utc_util.hpp"


CoordinatedUniversalTime::UTCTime CoordinatedUniversalTime::interpretJDNTime(const JDN& jdn) noexcept
{
	JDN multi{ .0 };

	if (jdn >= (JDN)1.)
		multi = (jdn - std::floor(jdn));
	else
		multi = jdn;

	if (multi < (JDN).5)
		multi += (JDN).5;
	else if (multi >= (JDN).5)
		multi -= (JDN).5;

	JDN totalSeconds{ (multi * (JDN)86'400.) };

    uint8_t utcHour{ 0 };
    uint8_t utcMinute{ 0 };
    uint8_t utcSecond{ 0 };

    if (totalSeconds) {
        utcHour = static_cast<uint8_t>((totalSeconds / (JDN)3'600.));
        totalSeconds -= ((JDN)utcHour * (JDN)3'600.);
    }

    if (totalSeconds) {
        utcMinute = static_cast<uint8_t>((totalSeconds / (JDN)60.));
        totalSeconds -= ((JDN)utcMinute * (JDN)60.);
    }

    // NOTE: Rounding issue when dealing with 11:59:59 PM
    if (totalSeconds)
        utcSecond = static_cast<uint8_t>(std::round(totalSeconds));

    // Corrects rounding issue when dealing with 11:59:59 PM
    // NOTE: (Temporary until precision update)
    if (utcHour == 23Ui8 && utcMinute == 59Ui8) {
        if (utcSecond == 60Ui8 && multi < (JDN)1.)
            --utcSecond;
    }

    // Adjustments for rounding issues
    if (utcSecond == 60Ui8) {
        utcSecond = 0Ui8;
        utcMinute += 1Ui8;
    }

    if (utcMinute == 60Ui8) {
        utcMinute = 0Ui8;
        utcHour += 1Ui8;
    }

    if (utcHour == 24Ui8)
        utcHour = 0Ui8;

    return UTCTime{
        .hour = utcHour,
        .minute = utcMinute,
        .second = utcSecond
    };
}

uint8_t CoordinatedUniversalTime::interpretJDNHour(const JDN& jdn) noexcept
{
    return interpretJDNTime(jdn).hour;
}

uint8_t CoordinatedUniversalTime::interpretJDNMinute(const JDN& jdn) noexcept
{
    return interpretJDNTime(jdn).minute;
}

uint8_t CoordinatedUniversalTime::interpretJDNSecond(const JDN& jdn) noexcept
{
    return interpretJDNTime(jdn).second;
}

uint8_t CoordinatedUniversalTime::getPhaseIndex(const UTCTime& utc) noexcept
{
    if (utc.hour < 12Ui8)
        return (uint8_t)0Ui8;
    return (uint8_t)1Ui8;
}

const char* CoordinatedUniversalTime::getPhaseStr(const UTCTime& utc) noexcept
{
    return Phases[getPhaseIndex(utc)];
}
