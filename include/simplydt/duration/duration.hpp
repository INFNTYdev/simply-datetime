
#ifndef SIMPLYDTLIB_L_DURATION_H_
#define SIMPLYDTLIB_L_DURATION_H_



#include<chrono>
#include<cmath>
#include"simplydt/common/gregorian_calendar/gregorian_util.hpp"
#include"simplydt/common/coord_universal_time/utc_util.hpp"


/* Measurement of time (d:HH:MM:SS) */
class Duration {

public:
	/* Standard library chronological duration (64-bit) */
	using ChronoDuration = std::chrono::duration<size_t>;
	/* Julian Day Number (JDN) */
	using JDN = JulianDateSystem::JDN;
	/* Gregorian calendar date */
	using Date = GregorianCalendar::GregorianDate;
	/* Standard UTC time */
	using Time = CoordinatedUniversalTime::UTCTime;

	/* Elapsed time */
	typedef struct _ELAPSED_TIME_STRUCT {
		const bool negative;
		const uint32_t days;
		const uint8_t hour;
		const uint8_t minute;
		const uint8_t second;
	} ElapsedTime;

	/* Duration string layout */
	enum Layout {
		SIGN_D_H_M_S,// ( +/- dd:HH:MM:SS ) [ Example: -124:08:30:00 ]
		D_H_M_S,// ( dd:HH:MM:SS ) [ Example: 124:08:30:00 ]
		SIGN_D_H_M,// ( +/- dd:HH:MM ) [ Example: +124:08:30 ]
		D_H_M,// ( dd:HH:MM ) [ Example: 124:08:30 ]
		SIGN_D_H,// ( +/- dd:HH ) [ Example: +124:08 ]
		D_H,// ( dd:HH ) [ Example: 124:08 ]
		SIGN_L_D_H_M_S,// [ Example: +124 days, 8 hours, 0 minutes, 30 seconds ]
		L_D_H_M_S,// [ Example: 124 days, 8 hours, 0 minutes, 30 seconds ]
		SIGN_L_D_H_M,// [ Example: -124 days, 8 hours, 0 minutes ]
		L_D_H_M,// [ Example: 124 days, 8 hours, 0 minutes ]
		SIGN_L_D_H,// [ Example: +124 days, 8 hours ]
		L_D_H,// [ Example: 124 days, 8 hours ]
	};

	/* Time units */
	enum Unit {
		DAY,
		HOUR,
		MINUTE,
		SECOND
	};

	/* Absolute maximum duration accumulation (|32,768 days| 88 years) */
	inline static const JDN MAX_DURATION{ 32'768. };

	Duration(const ChronoDuration& chrono_duration) noexcept;

	explicit Duration(const JDN& duration) noexcept;

	Duration(const Duration& duration) noexcept;

	Duration(Duration&& duration) noexcept;

	Duration() noexcept;

	~Duration() noexcept = default;

	friend std::ostream& operator<<(std::ostream& os, const Duration& duration) noexcept;

	Duration& operator=(const ChronoDuration& chrono_duration) noexcept;

	Duration& operator=(const Duration& duration) noexcept;

	Duration& operator=(Duration&& duration) noexcept;

	bool operator==(const Duration& duration) const noexcept;

	bool operator<(const Duration& duration) const noexcept;

	bool operator>(const Duration& duration) const noexcept;

	bool operator<=(const Duration& duration) const noexcept;

	bool operator>=(const Duration& duration) const noexcept;

	/* Sum two durations */
	Duration operator+(const Duration& duration) const noexcept;

	/* Subtract two durations */
	Duration operator-(const Duration& duration) const noexcept;

	/* Returns product of this duration multiplied by provided multiplier */
	Duration operator*(const JDN& multiplier) const noexcept;

	/* Returns decimal quotient of this duration divided by another */
	double operator/(const Duration& duration) const noexcept;

	/* Returns remaining duration of duration division */
	Duration operator%(const Duration& duration) const noexcept;

	/* Add to duration */
	Duration& operator+=(const Duration& duration) noexcept;

	/* Subtract from duration */
	Duration& operator-=(const Duration& duration) noexcept;

	/* Multiply duration */
	Duration& operator*=(const double& multiplier) noexcept;

	/* Modulus duration */
	Duration& operator%=(const Duration& duration) noexcept;

	/* Returns true if duration has no elapsed time */
	bool isZero() const noexcept;

	/* Returns true if duration is negative elapsed time */
	bool isNegative() const noexcept;

	/* Returns duration magnitude sign literal */
	char signChar() const noexcept;

	/* Returns absolute elapsed days */
	uint32_t days() const noexcept;

	/* Returns hours portion */
	uint8_t hour() const noexcept;

	/* Returns minutes portion */
	uint8_t minute() const noexcept;

	/* Returns seconds portion */
	uint8_t second() const noexcept;

	/* Returns duration unit literal */
	std::string getUnitLiteral(Unit t_unit) const noexcept;

	/* Returns elapsed time */
	ElapsedTime elapsedTime() const noexcept;

	/* Returns elapsed duration compressed into single time unit */
	uint32_t convertedTo(Unit t_unit) const noexcept;

	/* Returns duration string in provided format */
	std::string durationStr(Layout layout) const noexcept;

	/* Returns duration string */
	std::string durationStr() const noexcept;

	/* Returns true if provided duration is longer than this one */
	bool isShorterThan(const Duration& duration) const noexcept;

	/* Returns true if provided duration is shorter than this one */
	bool isLongerThan(const Duration& duration) const noexcept;

	/* Returns true if provided datetime matches this one */
	bool isEqual(const Duration& duration) const noexcept;

	/* Returns absolute total number of days between this duration and provided */
	uint32_t daysUntil(const Duration& duration) const noexcept;

	/* Returns absolute total number of hours between this duration and provided */
	uint32_t hoursUntil(const Duration& duration) const noexcept;

	/* Returns absolute total number of minutes between this duration and provided */
	uint32_t minutesUntil(const Duration& duration) const noexcept;

	/* Returns absolute total number of seconds between this duration and provided */
	uint32_t secondsUntil(const Duration& duration) const noexcept;

	/* Returns duration as a fraction of days */
	JDN toJDN() const noexcept;

	/* Returns duration as standard library chronological duration */
	ChronoDuration toChronoDuration() const noexcept;

	/* Alter duration with provided duration */
	void displace(const Duration& duration) noexcept;

	/* Reset duration to zero */
	void reset() noexcept;


private:
	JDN m_duration;

	std::string toDoubleDigitStr(const uint8_t& numeric) const noexcept;

};



#endif // SIMPLYDTLIB_L_DURATION_H_
