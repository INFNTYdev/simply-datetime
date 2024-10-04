
#include"simplydt/duration/duration.hpp"


//	Duration : CONSTRUCTORS

Duration::Duration(const ChronoDuration& chrono_duration) noexcept
	: m_duration{ 0. }
{
	this->m_duration = (static_cast<JDN>(chrono_duration.count()) / (JDN)86'400.);
}

Duration::Duration(const JDN& duration) noexcept
	: m_duration{ duration }
{
	//
}

Duration::Duration(JDN&& duration) noexcept
	: m_duration{ std::move(duration) }
{
	//
}

Duration::Duration(const Duration& duration) noexcept
	: m_duration{ duration.m_duration }
{
	//
}

Duration::Duration(Duration&& duration) noexcept
	: m_duration{ std::move(duration.m_duration) }
{
	//
}

Duration::Duration() noexcept
	: m_duration{ 0. }
{
	//
}


//	Duration : FREE



//	Duration : OPERATOR

std::ostream& operator<<(std::ostream& os, const Duration& duration) noexcept
{
	os << duration.durationStr(Duration::Layout::SIGN_D_H_M_S);

	return os;
}

Duration& Duration::operator=(const ChronoDuration& chrono_duration) noexcept
{
	this->m_duration = (static_cast<JDN>(chrono_duration.count()) / (JDN)86'400.);

	return *this;
}

Duration& Duration::operator=(const Duration& duration) noexcept
{
	if (this == &duration)
		return *this;

	this->m_duration = duration.m_duration;

	return *this;
}

Duration& Duration::operator=(Duration&& duration) noexcept
{
	if (this == &duration)
		return *this;

	this->m_duration = std::move(duration.m_duration);

	return *this;
}

bool Duration::operator==(const Duration& duration) const noexcept
{
	return this->isEqual(duration);
}

bool Duration::operator<(const Duration& duration) const noexcept
{
	return this->isShorterThan(duration);
}

bool Duration::operator>(const Duration& duration) const noexcept
{
	return this->isLongerThan(duration);
}

bool Duration::operator<=(const Duration& duration) const noexcept
{
	return (this->isShorterThan(duration) || this->isEqual(duration));
}

bool Duration::operator>=(const Duration& duration) const noexcept
{
	return (this->isLongerThan(duration) || this->isEqual(duration));
}

Duration Duration::operator+(const Duration& duration) const noexcept
{
	return Duration{ (this->m_duration + duration.m_duration) };
}

Duration Duration::operator-(const Duration& duration) const noexcept
{
	switch (duration.isNegative()) {
	case true:
		return Duration{ (this->m_duration + (duration.m_duration * (JDN)-1.)) };

	default:
		return Duration{ (this->m_duration - duration.m_duration) };
	}
}

Duration Duration::operator*(const JDN& multiplier) const noexcept
{
	return Duration{ (this->m_duration * multiplier) };
}

double Duration::operator/(const Duration& duration) const noexcept
{
	return (this->m_duration / duration.m_duration);
}

Duration Duration::operator%(const Duration& duration) const noexcept
{
	JDN quotient{ (this->m_duration / duration.m_duration) };

	return Duration{ (this->m_duration - (duration.m_duration * quotient)) };
}

Duration& Duration::operator+=(const Duration& duration) noexcept
{
	this->m_duration += duration.m_duration;

	return *this;
}

Duration& Duration::operator-=(const Duration& duration) noexcept
{
	switch (duration.isNegative()) {
	case true:
		this->m_duration = (this->m_duration + (duration.m_duration * (JDN)-1.));
		break;

	default:
		this->m_duration = (this->m_duration - duration.m_duration);
	}

	return *this;
}

Duration& Duration::operator*=(const double& multiplier) noexcept
{
	this->m_duration *= multiplier;

	return *this;
}

Duration& Duration::operator%=(const Duration& duration) noexcept
{
	JDN quotient{ std::floor(this->m_duration / duration.m_duration) };

	this->m_duration = (this->m_duration - (duration.m_duration * quotient));

	return *this;
}

//	Duration : OPERATOR END!



//	Duration : PUBLIC

bool Duration::isZero() const noexcept
{
	return (this->m_duration == (JDN)0.);
}

bool Duration::isNegative() const noexcept
{
	return (this->m_duration < (JDN)0.);
}

char Duration::signChar() const noexcept
{
	switch (this->isNegative()) {
	case true:
		return '-';

	default:
		return '+';
	}
}

uint32_t Duration::days() const noexcept
{
	switch (this->isNegative()) {
	case true:
		return static_cast<uint32_t>(this->m_duration * (JDN)-1.);

	default:
		return static_cast<uint32_t>(this->m_duration);
	}
}

uint8_t Duration::hour() const noexcept
{
	JDN fracOfDay{ 0. };

	switch (this->isNegative()) {
	case true:
		fracOfDay = (
			(this->m_duration * (JDN)-1.) - std::floor((this->m_duration * (JDN)-1.))
		);
		break;

	default:
		fracOfDay = (this->m_duration - std::floor(this->m_duration));
	}

	uint8_t currentHr{ static_cast<uint8_t>(fracOfDay * (JDN)24.) };

	return currentHr;
}

uint8_t Duration::minute() const noexcept
{
	JDN fracOfDay{ 0. };

	switch (this->isNegative()) {
	case true:
		fracOfDay = (
			(this->m_duration * (JDN)-1.) - std::floor((this->m_duration * (JDN)-1.))
		);
		break;

	default:
		fracOfDay = (this->m_duration - std::floor(this->m_duration));
	}

	uint8_t currentMin{
		static_cast<uint8_t>((fracOfDay * (JDN)1'440.) - ((JDN)this->hour() * (JDN)60.))
	};

	return currentMin;
}

uint8_t Duration::second() const noexcept
{
	JDN fracOfDay{ 0. };

	switch (this->isNegative()) {
	case true:
		fracOfDay = (
			(this->m_duration * (JDN)-1.) - std::floor((this->m_duration * (JDN)-1.))
		);
		break;

	default:
		fracOfDay = (this->m_duration - std::floor(this->m_duration));
	}

	uint8_t currentSec{
		static_cast<uint8_t>(
			(fracOfDay * (JDN)86'400.) - ((JDN)this->hour() * (JDN)3'600.) - ((JDN)this->minute() * (JDN)60.)
		)
	};

	return currentSec;
}

std::string Duration::getUnitLiteral(Unit t_unit) const noexcept
{
	switch (t_unit) {
	case Unit::DAY:
		return std::string{ (std::to_string(this->days()) + " days") };

	case Unit::HOUR:
		return std::string{ (std::to_string(this->hour()) + " hours") };

	case Unit::MINUTE:
		return std::string{ (std::to_string(this->minute()) + " minutes") };

	// Seconds unit literal
	default:
		return std::string{ (std::to_string(this->second()) + " seconds") };
	}
}

Duration::ElapsedTime Duration::elapsedTime() const noexcept
{
	switch (this->isNegative()) {
	case true:
		return ElapsedTime{
			.negative = true,
			.days = this->days(),
			.hour = this->hour(),
			.minute = this->minute(),
			.second = this->second()
		};

	default:
		return ElapsedTime{
			.negative = false,
			.days = this->days(),
			.hour = this->hour(),
			.minute = this->minute(),
			.second = this->second()
		};
	}
}

uint32_t Duration::convertedTo(Unit t_unit) const noexcept
{
	switch (t_unit) {
	case Unit::DAY:
		return static_cast<uint32_t>(this->m_duration);

	case Unit::HOUR:
		return static_cast<uint32_t>(this->m_duration * (JDN)24.);

	case Unit::MINUTE:
		return static_cast<uint32_t>(this->m_duration * (JDN)1'440.);

	// Convert to seconds
	default:
		return static_cast<uint32_t>(this->m_duration * (JDN)86'400.);
	}
}

std::string Duration::durationStr(Layout layout) const noexcept
{
	std::string durStr{};
	durStr.reserve(21Ui64);

	char delimiter{ ':' };

	ElapsedTime elapsed{ this->elapsedTime() };

	// Handle duration sign character if applicable
	switch (layout) {
	case Layout::SIGN_D_H_M_S:
	case Layout::SIGN_D_H_M:
	case Layout::SIGN_D_H:
	case Layout::SIGN_L_D_H_M_S:
	case Layout::SIGN_L_D_H_M:
	case Layout::SIGN_L_D_H:
		durStr += this->signChar();
	}

	// Handle base duration string
	switch (layout) {
	case Layout::SIGN_L_D_H_M_S:
	case Layout::L_D_H_M_S:
	case Layout::SIGN_L_D_H_M:
	case Layout::L_D_H_M:
	case Layout::SIGN_L_D_H:
	case Layout::L_D_H:
		durStr.reserve(46Ui64);
		delimiter = ',';
		durStr += (this->getUnitLiteral(Unit::DAY) + delimiter + ' ');
		durStr += this->getUnitLiteral(Unit::HOUR);
		break;

	default:
		durStr += (std::to_string(elapsed.days) + delimiter);
		durStr += this->toDoubleDigitStr(elapsed.hour);
	}

	// Handle numerical duration string layouts
	switch (layout) {
	case Layout::SIGN_D_H_M:
	case Layout::D_H_M:
		durStr += (delimiter + this->toDoubleDigitStr(elapsed.minute));
		break;

	case Layout::SIGN_D_H_M_S:
	case Layout::D_H_M_S:
		durStr += (delimiter + this->toDoubleDigitStr(elapsed.minute));
		durStr += (delimiter + this->toDoubleDigitStr(elapsed.second));
		break;
	}

	// Handle literal duration string layouts
	switch (layout) {
	case Layout::SIGN_L_D_H_M:
	case Layout::L_D_H_M:
		durStr += delimiter;
		durStr += ' ';
		durStr += this->getUnitLiteral(Unit::MINUTE);
		break;

	case Layout::SIGN_L_D_H_M_S:
	case Layout::L_D_H_M_S:
		durStr += delimiter;
		durStr += ' ';
		durStr += this->getUnitLiteral(Unit::MINUTE);
		durStr += delimiter;
		durStr += ' ';
		durStr += this->getUnitLiteral(Unit::SECOND);
	}

	return durStr;
}

std::string Duration::durationStr() const noexcept
{
	return this->durationStr(Layout::SIGN_D_H_M_S);
}

bool Duration::isShorterThan(const Duration& duration) const noexcept
{
	ElapsedTime thisElapsed{ this->elapsedTime() };
	ElapsedTime thatElapsed{ duration.elapsedTime() };

	if (thisElapsed.days < thatElapsed.days)
		return true;
	else if (thisElapsed.days > thatElapsed.days)
		return false;

	if (thisElapsed.hour < thatElapsed.hour)
		return true;
	else if (thisElapsed.hour > thatElapsed.hour)
		return false;

	if (thisElapsed.minute < thatElapsed.minute)
		return true;
	else if (thisElapsed.minute > thatElapsed.minute)
		return false;

	if (thisElapsed.second < thatElapsed.second)
		return true;
	else
		return false;
}

bool Duration::isLongerThan(const Duration& duration) const noexcept
{
	ElapsedTime thisElapsed{ this->elapsedTime() };
	ElapsedTime thatElapsed{ duration.elapsedTime() };

	if (thisElapsed.days > thatElapsed.days)
		return true;
	else if (thisElapsed.days < thatElapsed.days)
		return false;

	if (thisElapsed.hour > thatElapsed.hour)
		return true;
	else if (thisElapsed.hour < thatElapsed.hour)
		return false;

	if (thisElapsed.minute > thatElapsed.minute)
		return true;
	else if (thisElapsed.minute < thatElapsed.minute)
		return false;

	if (thisElapsed.second > thatElapsed.second)
		return true;
	else
		return false;
}

bool Duration::isEqual(const Duration& duration) const noexcept
{
	ElapsedTime thisElapsed{ this->elapsedTime() };
	ElapsedTime thatElapsed{ duration.elapsedTime() };

	if (thisElapsed.negative != thatElapsed.negative)
		return false;

	if (thisElapsed.days != thatElapsed.days)
		return false;

	if (thisElapsed.hour != thatElapsed.hour)
		return false;

	if (thisElapsed.minute != thatElapsed.minute)
		return false;

	if (thisElapsed.second != thatElapsed.second)
		return false;

	return true;
}

uint32_t Duration::daysUntil(const Duration& duration) const noexcept
{
	JDN difference{
		(std::floor(duration.m_duration) - std::floor(this->m_duration))
	};

	if (difference < (JDN)0.)
		difference *= (JDN)-1.;

	return static_cast<uint32_t>(std::floor(difference));
}

uint32_t Duration::hoursUntil(const Duration& duration) const noexcept
{
	JDN thisHours{ std::floor(this->m_duration * (JDN)24.) };
	JDN thatHours{ std::floor(duration.m_duration * (JDN)24.) };

	JDN hrDiff{ (thatHours - thisHours) };

	if (hrDiff < (JDN)0.)
		hrDiff *= (JDN)-1.;

	return static_cast<uint32_t>(hrDiff);
}

uint32_t Duration::minutesUntil(const Duration& duration) const noexcept
{
	JDN thisMinutes{ std::floor(this->m_duration * (JDN)1'440.) };
	JDN thatMinutes{ std::floor(duration.m_duration * (JDN)1'440.) };

	JDN minDiff{ (thatMinutes - thisMinutes) };

	if (minDiff < (JDN)0.)
		minDiff *= (JDN)-1.;

	return static_cast<uint32_t>(minDiff);
}

uint32_t Duration::secondsUntil(const Duration& duration) const noexcept
{
	JDN thisSeconds{ std::floor(this->m_duration * (JDN)86'400.) };
	JDN thatSeconds{ std::floor(duration.m_duration * (JDN)86'400.) };

	JDN secDiff{ (thatSeconds - thisSeconds) };

	if (secDiff < (JDN)0.)
		secDiff *= (JDN)-1.;

	return static_cast<uint32_t>(secDiff);
}

Duration::JDN Duration::toJDN() const noexcept
{
	return this->m_duration;
}

Duration::ChronoDuration Duration::toChronoDuration() const noexcept
{
	ChronoDuration duration{ this->convertedTo(Unit::SECOND) };

	return duration;
}

void Duration::displace(const Duration& duration) noexcept
{
	this->m_duration += duration.m_duration;
}

void Duration::reset() noexcept
{
	this->m_duration = (JDN)0.;
}

//	Duration : PUBLIC END!



//	Duration : PRIVATE

std::string Duration::toDoubleDigitStr(const uint8_t& numeric) const noexcept
{
	if (numeric > 9Ui8)
		return std::to_string(numeric);
	else
		return std::string{ ("0" + std::to_string(numeric)) };
}

//	Duration : PRIVATE END!



//	Duration : PROTECTED
//	Duration : PROTECTED END!
