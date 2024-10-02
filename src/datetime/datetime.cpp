
#include"simplydt/datetime/datetime.hpp"


//	Datetime : CONSTRUCTORS

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

std::string Datetime::datetimeStr() const noexcept
{
	std::string dtStr;
	dtStr.reserve(21Ui64);

	dtStr = "N/a";

	return dtStr;
}

//	Datetime : PUBLIC END!



//	Datetime : PRIVATE
//	Datetime : PRIVATE END!



//	Datetime : PROTECTED
//	Datetime : PROTECTED END!
