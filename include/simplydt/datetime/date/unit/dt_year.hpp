
#ifndef SIMPLYDTLIB_L_DATE_YEAR_H_
#define SIMPLYDTLIB_L_DATE_YEAR_H_



#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/date/date_utility.hpp"


/* Datetime year */
class Year : public DateInterval {

public:
    /* Year translation mode */
    using Trans = Interval<uint16_t>::Trans;

    Year(uint16_t value) noexcept
        : DateInterval{ DateInterval::YEAR, value }
    {
        // There are still ways to get around this maybe?
        if (this->position() < YEAR_MIN)
            this->setPosition(YEAR_MIN);
    }

    ~Year() = default;

	static const uint16_t YEAR_MIN{ 1900 };// Standard library is limitting factor

    /* Returns true if year is a leap year */
    bool isLeapYear() const noexcept
    {
        return simplydt::isLeapYear(this->position());
    }

    /* Returns total number of days in year */
    uint16_t getTotalDays() const noexcept
    {
        return simplydt::getTotalDaysInYear(this->position());
    }

    /* Returns year in century */
    uint16_t getYearInCentury() const noexcept
    {
        return simplydt::getYearInCentury(this->position());
    }
    
    /* Set year value */
    bool setPosition(uint16_t pos) noexcept
    {
        if (pos < YEAR_MIN)
            return false;

        return Interval<uint16_t>::setPosition(pos);
    }

    /* Set year value */
    bool setYear(uint16_t pos) noexcept
    {
        return this->setPosition(pos);
    }

    /* Displace year in provided direction with provided units */
    void displace(Trans trans, uint16_t units) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(trans, units) < YEAR_MIN)
            return;

        return DateInterval::dateDisplace(trans, units);
    }

    /* Displace year in provided direction with provided units */
    void largeDisplace(Trans trans, size_t units) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(trans, units) < YEAR_MIN)
            return;

        return DateInterval::dateDisplace(trans, units);
    }

    /* Increase year value by provided amount of units */
    void increase(size_t units = (size_t)1Ui64) noexcept
    {
        // Year does not respond to requests below the minimum
        // (this is for a year that intends to overflows)
        if (this->getExpectedPosition(Trans::POSITIVE, units) < YEAR_MIN)
            return;

        this->largeDisplace(Trans::POSITIVE, units);
    }

    /* Decrease year value by provided amount of units */
    void decrease(size_t units = (size_t)1Ui64) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(Trans::NEGATIVE, units) < YEAR_MIN)
            return;

        this->largeDisplace(Trans::NEGATIVE, units);
    }


private:
    uint16_t getExpectedPosition(Trans trans, size_t units) const noexcept
    {
        Interval<uint16_t>::LargeTransResult destination{
            this->calculateLargeTranslation(trans, units)
        };

        return destination.second;
    }

};



#endif // SIMPLYDTLIB_L_DATE_YEAR_H_
