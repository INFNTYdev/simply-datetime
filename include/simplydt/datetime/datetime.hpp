
#ifndef SIMPLYDTLIB_L_DATETIME_H_
#define SIMPLYDTLIB_L_DATETIME_H_



#include<chrono>
#include<iostream>
#include"simplydt/common/gregorian_calendar/gregorian_util.hpp"
#include"simplydt/common/coord_universal_time/utc_util.hpp"
#include"simplydt/duration/duration.hpp"


/* Standard datetime (YYYY/MM/dd HH:MM:SS) */
class Datetime {

public:
	/* Standard library chronological time point (system clock) */
	using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
	/* Julian Day Number (JDN) */
	using JDN = JulianDateSystem::JDN;
	/* Gregorian calendar date */
	using Date = GregorianCalendar::GregorianDate;
	/* Date layouts */
	using DateLayout = GregorianCalendar::DateLayout;
	/* Date formats */
	using DateFormat = GregorianCalendar::DateFormat;
	/* Time layouts */
	using TimeLayout = CoordinatedUniversalTime::TimeLayout;
	/* Time formats */
	using TimeFormat = CoordinatedUniversalTime::TimeFormat;
	/* Standard UTC time */
	using Time = CoordinatedUniversalTime::UTCTime;

	/* Datetime string layout */
	enum Layout {
		DATE_TIME,// date - time [Example: 01/01/1970 00:00:00 AM]
		TIME_DATE,// time - date [Example: 00:00:00 AM 01/01/1970]
	};

	/* Minimum representable date (01/01/0 00:00:00 AM) */
	inline static const JDN MIN_JDN{ 1'721'057.5 };
	/* Standard library epoch date (01/01/1970 00:00:00 AM) */
	inline static const JDN EPOCH_JDN{ 2'440'587.5 };
	/* Maximum representable date (12/31/65535 11:59:59 PM) */
	inline static const JDN MAX_JDN{ 25'657'591.49999999 };

	Datetime(const TimePoint& time_point) noexcept;

	Datetime(const Date& date, const Time& time) noexcept;

	Datetime(const Date& date) noexcept;

	explicit Datetime(const JDN& jdn) noexcept;

	explicit Datetime(JDN&& jdn) noexcept;

	Datetime(const Datetime& dt) noexcept;

	Datetime(Datetime&& dt) noexcept;

	Datetime() noexcept;

	~Datetime() = default;

	friend std::ostream& operator<<(std::ostream& os, const Datetime& dt) noexcept;

	Datetime& operator=(const TimePoint& time_point) noexcept;

	Datetime& operator=(const Datetime& dt) noexcept;

	Datetime& operator=(Datetime&& dt) noexcept;

	bool operator==(const Datetime& dt) noexcept;

	bool operator<(const Datetime& dt) noexcept;

	bool operator>(const Datetime& dt) noexcept;

	bool operator<=(const Datetime& dt) noexcept;

	bool operator>=(const Datetime& dt) noexcept;

	/* Add duration to datetime */
	Datetime operator+(const Duration& duration) const noexcept;

	/* Subtract duration from datetime */
	Datetime operator-(const Duration& duration) const noexcept;

	/* Increase datetime by duration */
	Datetime& operator+=(const Duration& duration) noexcept;

	/* Decrease datetime by duration */
	Datetime& operator-=(const Duration& duration) noexcept;

	/* Returns datetime year */
	uint16_t year() const noexcept;

	/* Returns datetime month */
	uint8_t month() const noexcept;

	/* Returns datetime day */
	uint8_t day() const noexcept;

	/* Returns datetime hour */
	uint8_t hour() const noexcept;

	/* Returns datetime minute */
	uint8_t minute() const noexcept;

	/* Returns datetime second */
	uint8_t second() const noexcept;

	/* Returns datetime date */
	Date date() const noexcept;

	/* Returns datetime time */
	Time time() const noexcept;

	/* Returns true if datetime is default datetime */
	bool isDefault() const noexcept;

	/* Returns datetime day-of-week literal */
	const char* dayOfWeek() const noexcept;

	/* Returns datetime month literal */
	const char* monthTitle() const noexcept;

	/* Returns index of datetime day-of-week */
	uint8_t dowIndex() const noexcept;

	/* Returns index of datetime month */
	uint8_t monthIndex() const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(Layout layout, DateFormat d_format,
		DateLayout d_layout, TimeFormat t_format, TimeLayout t_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(DateFormat d_format, DateLayout d_layout,
		TimeFormat t_format, TimeLayout t_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(DateFormat d_format, DateLayout d_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(TimeFormat t_format, TimeLayout t_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(DateFormat d_format, TimeFormat t_format) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(DateLayout d_layout, TimeLayout t_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(DateFormat d_format) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(DateLayout d_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(TimeFormat t_format) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(TimeLayout t_layout) const noexcept;

	/* Returns datetime string in provided layout */
	std::string datetimeStr(Layout layout) const noexcept;

	/* Returns datetime string */
	std::string datetimeStr() const noexcept;

	/* Returns true if provided datetime occurs after this one */
	bool isBefore(const Datetime& dt) const noexcept;

	/* Returns true if provided datetime occurs before this one */
	bool isAfter(const Datetime& dt) const noexcept;

	/* Returns true if provided datetime matches this one */
	bool isEqual(const Datetime& dt) const noexcept;

	/* Returns absolute total number of days between this datetime and provided */
	uint32_t daysUntil(const Datetime& dt) const noexcept;

	/* Returns absolute total number of hours between this datetime and provided */
	uint32_t hoursUntil(const Datetime& dt) const noexcept;

	/* Returns absolute total number of minutes between this datetime and provided */
	uint32_t minutesUntil(const Datetime& dt) const noexcept;

	/* Returns absolute total number of seconds between this datetime and provided */
	uint32_t secondsUntil(const Datetime& dt) const noexcept;

	/* Returns duration of time between this datetime and provided */
	Duration until(const Datetime& dt) const noexcept;

	/* Returns datetime after the provided duration from this point */
	Datetime after(const Duration& duration) const noexcept;

	/* Returns datetime as Julian Day Number (JDN) */
	JDN toJDN() const noexcept;

	/* Returns datetime as statndard library system clock time point */
	//TimePoint toTimePoint() const noexcept;//		<- INCOMPLETE!

	/* Alter datetime with provided duration */
	void displace(const Duration& duration) noexcept;

	/* Reset datetime to standard library epoch */
	void reset() noexcept;


private:
	JDN m_julianDayNumber;

	void assumeDatetime(const Date& date, const Time& time) noexcept;

	void assumeDatetime(const TimePoint& time_point) noexcept;

};



#endif // SIMPLYDTLIB_L_DATETIME_H_
