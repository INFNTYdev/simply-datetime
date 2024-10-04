
#include"simplydt/datetime/datetime.hpp"


//	Datetime : CONSTRUCTORS

Datetime::Datetime(const TimePoint& time_point) noexcept
	: m_julianDayNumber{ EPOCH_JDN }
{
	this->assumeDatetime(time_point);
}

Datetime::Datetime(const Date& date, const Time& time) noexcept
	: m_julianDayNumber{ EPOCH_JDN }
{
	this->assumeDatetime(date, time);
}

Datetime::Datetime(const Date& date) noexcept
	: m_julianDayNumber{
		JulianDateSystem::gregorianToJDN(date.year, date.month, date.day)
	}
{
	//
}

Datetime::Datetime(const JDN& jdn) noexcept
	: m_julianDayNumber{ jdn }
{
	//
}

Datetime::Datetime(JDN&& jdn) noexcept
	: m_julianDayNumber{ std::move(jdn) }
{
	//
}

Datetime::Datetime(const Datetime& dt) noexcept
	: m_julianDayNumber{ dt.m_julianDayNumber }
{
	//
}

Datetime::Datetime(Datetime&& dt) noexcept
	: m_julianDayNumber{ std::move(dt.m_julianDayNumber) }
{
	//
}

Datetime::Datetime() noexcept
	: m_julianDayNumber{ EPOCH_JDN }
{
	//
}


//	Datetime : FREE



//	Datetime : OPERATOR

std::ostream& operator<<(std::ostream& os, const Datetime& dt) noexcept
{
	os << dt.datetimeStr();

	return os;
}

Datetime& Datetime::operator=(const TimePoint& time_point) noexcept
{
	this->assumeDatetime(time_point);

	return *this;
}

Datetime& Datetime::operator=(const Datetime& dt) noexcept
{
	if (this == &dt)
		return *this;

	this->m_julianDayNumber = dt.m_julianDayNumber;

	return *this;
}

Datetime& Datetime::operator=(Datetime&& dt) noexcept
{
	if (this == &dt)
		return *this;

	this->m_julianDayNumber = std::move(dt.m_julianDayNumber);

	return *this;
}

bool Datetime::operator==(const Datetime& dt) noexcept
{
	return this->isEqual(dt);
}

bool Datetime::operator<(const Datetime& dt) noexcept
{
	return this->isBefore(dt);
}

bool Datetime::operator>(const Datetime& dt) noexcept
{
	return this->isAfter(dt);
}

bool Datetime::operator<=(const Datetime& dt) noexcept
{
	return ( this->isBefore(dt) || this->isEqual(dt) );
}

bool Datetime::operator>=(const Datetime& dt) noexcept
{
	return ( this->isAfter(dt) || this->isEqual(dt) );
}

Datetime Datetime::operator+(const Duration& duration) const noexcept
{
	return this->after(duration);
}

Datetime Datetime::operator-(const Duration& duration) const noexcept
{
	switch (duration.isNegative()) {
	case true:
		return Datetime{ (this->m_julianDayNumber + (duration.toJDN() * (JDN)-1.)) };

	default:
		return Datetime{ (this->m_julianDayNumber - duration.toJDN()) };
	}
}

Datetime& Datetime::operator+=(const Duration& duration) noexcept
{
	this->m_julianDayNumber += duration.toJDN();

	return *this;
}

Datetime& Datetime::operator-=(const Duration& duration) noexcept
{
	switch (duration.isNegative()) {
	case true:
		this->m_julianDayNumber += (duration.toJDN() * (JDN)-1.);
		break;

	default:
		this->m_julianDayNumber -= duration.toJDN();
	}

	return *this;
}

//	Datetime : OPERATOR END!



//	Datetime : PUBLIC

uint16_t Datetime::year() const noexcept
{
	return GregorianCalendar::interpretJDNYear(this->m_julianDayNumber);
}

uint8_t Datetime::month() const noexcept
{
	return GregorianCalendar::interpretJDNMonth(this->m_julianDayNumber);
}

uint8_t Datetime::day() const noexcept
{
	return GregorianCalendar::interpretJDNDay(this->m_julianDayNumber);
}

uint8_t Datetime::hour() const noexcept
{
	return CoordinatedUniversalTime::interpretJDNHour(this->m_julianDayNumber);
}

uint8_t Datetime::minute() const noexcept
{
	return CoordinatedUniversalTime::interpretJDNMinute(this->m_julianDayNumber);
}

uint8_t Datetime::second() const noexcept
{
	return CoordinatedUniversalTime::interpretJDNSecond(this->m_julianDayNumber);
}

Datetime::Date Datetime::date() const noexcept
{
	return GregorianCalendar::interpretJDNDate(this->m_julianDayNumber);
}

Datetime::Time Datetime::time() const noexcept
{
	return CoordinatedUniversalTime::interpretJDNTime(this->m_julianDayNumber);
}

bool Datetime::isDefault() const noexcept
{
	return (this->m_julianDayNumber == EPOCH_JDN);
}

const char* Datetime::dayOfWeek() const noexcept
{
	return GregorianCalendar::getDayOfWeek(this->date());
}

const char* Datetime::monthTitle() const noexcept
{
	return GregorianCalendar::getMonthTitle(this->date().month);
}

uint8_t Datetime::dowIndex() const noexcept
{
	return GregorianCalendar::getDayOfWeekIndex(this->date());
}

uint8_t Datetime::monthIndex() const noexcept
{
	return GregorianCalendar::getMonthIndex(this->date().month);
}

std::string Datetime::datetimeStr() const noexcept	// <- INCOMPLETE!
{
	std::string dtStr;
	dtStr.reserve(21Ui64);

	dtStr = "N/a";

	return dtStr;
}

bool Datetime::isBefore(const Datetime& dt) const noexcept
{
	Date thisDate{ this->date() };
	Date thatDate{ dt.date() };

	if (GregorianCalendar::isBefore(thatDate, thisDate))
		return true;
	else if (GregorianCalendar::isAfter(thatDate, thisDate))
		return false;

	return CoordinatedUniversalTime::isBefore(dt.time(), this->time());
}

bool Datetime::isAfter(const Datetime& dt) const noexcept
{
	Date thisDate{ this->date() };
	Date thatDate{ dt.date() };

	if (GregorianCalendar::isAfter(thatDate, thisDate))
		return true;
	else if (GregorianCalendar::isBefore(thatDate, thisDate))
		return false;

	return CoordinatedUniversalTime::isAfter(dt.time(), this->time());
}

bool Datetime::isEqual(const Datetime& dt) const noexcept
{
	if (!GregorianCalendar::isEqual(this->date(), dt.date()))
		return false;

	return CoordinatedUniversalTime::isEqual(this->time(), dt.time());
}

uint32_t Datetime::daysUntil(const Datetime& dt) const noexcept
{
	JDN difference{
		(std::floor(dt.m_julianDayNumber) - std::floor(this->m_julianDayNumber))
	};

	if (difference < (JDN)0.)
		difference *= (JDN)-1.;

	return static_cast<uint32_t>(std::floor(difference));
}

uint32_t Datetime::hoursUntil(const Datetime& dt) const noexcept
{
	JDN difference{ (dt.m_julianDayNumber - this->m_julianDayNumber) };

	if (difference < (JDN)0.)
		difference *= (JDN)-1.;

	uint32_t hours{ static_cast<uint32_t>(difference * (JDN)24.) };

	return hours;
}

uint32_t Datetime::minutesUntil(const Datetime& dt) const noexcept
{
	JDN difference{ (dt.m_julianDayNumber - this->m_julianDayNumber) };

	if (difference < (JDN)0.)
		difference *= (JDN)-1.;

	uint32_t minutes{ static_cast<uint32_t>(difference * (JDN)1'440.) };

	return minutes;
}

uint32_t Datetime::secondsUntil(const Datetime& dt) const noexcept
{
	JDN difference{ (dt.m_julianDayNumber - this->m_julianDayNumber) };

	if (difference < (JDN)0.)
		difference *= (JDN)-1.;

	uint32_t seconds{ static_cast<uint32_t>(difference * (JDN)86'400.) };

	return seconds;
}

Duration Datetime::until(const Datetime& dt) const noexcept
{
	return Duration{ (dt.m_julianDayNumber - this->m_julianDayNumber) };
}

Datetime Datetime::after(const Duration& duration) const noexcept
{
	return Datetime{ (this->m_julianDayNumber + duration.toJDN()) };
}

Datetime::JDN Datetime::toJDN() const noexcept
{
	return this->m_julianDayNumber;
}

//Datetime::TimePoint Datetime::toTimePoint() const noexcept	<- INCOMPLETE!
//{
//	//
//}

void Datetime::displace(const Duration& duration) noexcept
{
	this->m_julianDayNumber += duration.toJDN();
}

void Datetime::reset() noexcept
{
	this->m_julianDayNumber = EPOCH_JDN;
}

//	Datetime : PUBLIC END!



//	Datetime : PRIVATE

void Datetime::assumeDatetime(const Date& date, const Time& time) noexcept
{
	this->m_julianDayNumber = (
		JulianDateSystem::gregorianToJDN(date.year, date.month, date.day)
		+ CoordinatedUniversalTime::timeInDay(time.hour, time.minute, time.second)
	);
}

void Datetime::assumeDatetime(const TimePoint& time_point) noexcept
{
	std::time_t timeT{ std::chrono::system_clock::to_time_t(time_point) };
	std::tm* tm_ptr{ std::localtime(&timeT) };

	// Retrieve datetime from time point
	uint16_t year = static_cast<uint16_t>(tm_ptr->tm_year);// tm_year only measures years since 1900
	uint8_t month = static_cast<uint8_t>(tm_ptr->tm_mon);
	uint8_t day = static_cast<uint8_t>(tm_ptr->tm_mday);
	uint8_t hour = static_cast<uint8_t>(tm_ptr->tm_hour);
	uint8_t minute = static_cast<uint8_t>(tm_ptr->tm_min);
	uint8_t second = static_cast<uint8_t>(tm_ptr->tm_sec);

	year += 1900Ui16;
	month += 1Ui8;

	this->m_julianDayNumber = (
		JulianDateSystem::gregorianToJDN(year, month, day)
		+ CoordinatedUniversalTime::timeInDay(hour, minute, second)
	);
}

//	Datetime : PRIVATE END!



//	Datetime : PROTECTED
//	Datetime : PROTECTED END!
