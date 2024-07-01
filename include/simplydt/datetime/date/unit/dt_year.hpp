
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
    
    /* Set year value */
    template <typename UInt_T>
    bool setPosition(UInt_T pos) noexcept
    {
        if ((size_t)pos < (size_t)YEAR_MIN)
            return false;

        return Interval<uint16_t>::setPosition(pos);
    }

    /* Displace year in provided direction with provided units */
    void displace(Trans trans, uint16_t units) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(trans, units) < YEAR_MIN)
            return;

        Interval<uint16_t>::displace(trans, units);

        if (!this->hasSubsequentInterval())
            return;
        
        if (!this->getSubsequentInterval()->hasSubsequentInterval())
            return;

        // Set new threshold on day interval
        uint16_t newDayMax{
            simplydt::getTotalDaysInMonth(
                this->position(),// Year value
                this->subsequentPosition()// Month value
            )
        };

        // Need confirmation that this is logic-safe
        this->getSubsequentInterval()->setSubsequentThreshold(newDayMax);
    }

    /* Increase year value by provided amount of units */
    void increment(uint16_t units = (uint16_t)1U) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(Trans::POSITIVE, units) < YEAR_MIN)
            return;

        this->displace(Trans::POSITIVE, units);
    }

    /* Decrease year value by provided amount of units */
    void decrement(uint16_t units = (uint16_t)1U) noexcept
    {
        // Year does not respond to requests below the minimum
        if (this->getExpectedPosition(Trans::NEGATIVE, units) < YEAR_MIN)
            return;

        this->displace(Trans::NEGATIVE, units);
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
