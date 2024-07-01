
#ifndef SIMPLYDTLIB_L_DATE_YEAR_H_
#define SIMPLYDTLIB_L_DATE_YEAR_H_



#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/date/date_utility.hpp"


class Year : public DateInterval {

public:
    using Trans = Interval<uint16_t>::Trans;

    Year(uint16_t value) noexcept
        : DateInterval{ DateInterval::YEAR, value }
    {
        // There are still ways to get around this!
        if (this->position() < YEAR_MIN)
            this->setPosition(YEAR_MIN);
    }

    ~Year() = default;

	static const uint16_t YEAR_MIN{ 1700 };

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
    
    template <typename UInt_T>
    bool setPosition(UInt_T pos) noexcept
    {
        if ((size_t)pos < (size_t)YEAR_MIN)
            return false;

        return Interval<uint16_t>::setPosition(pos);
    }

    void displace(Trans trans, uint16_t units) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(trans, units) < YEAR_MIN)
            return;

        Interval<uint16_t>::displace(trans, units);
    }

    void increment(uint16_t units = (uint16_t)1U) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(Trans::POSITIVE, units) < YEAR_MIN)
            return;

        Interval<uint16_t>::increment(units);
    }

    void decrement(uint16_t units = (uint16_t)1U) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(Trans::NEGATIVE, units) < YEAR_MIN)
            return;

        Interval<uint16_t>::decrement(units);
    }


private:
    uint16_t getExpectedPosition(Trans trans, uint16_t units) const noexcept
    {
        Interval<uint16_t>::TransResult destination{
            this->calculateTranslation(trans, units)
        };

        return destination.second;
    }

};



#endif // SIMPLYDTLIB_L_DATE_YEAR_H_
