
#ifndef SIMPLYDTLIB_L_DATE_MONTH_H_
#define SIMPLYDTLIB_L_DATE_MONTH_H_



#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/date/date_utility.hpp"


/* Datetime month */
class Month : public DateInterval {

public:
    /* Month translation mode */
    using Trans = Interval<uint16_t>::Trans;

    Month(uint16_t value) noexcept
        : DateInterval{ DateInterval::MONTH, value }
    {
        //
    }

    ~Month() = default;

    /* Returns month literal */
    const char* getName() const noexcept
    {
        return simplydt::getMonth(this->position());
    }

    /* Displace month in provided direction with provided units */
    void displace(Trans trans, uint16_t units) noexcept
    {
        Interval<uint16_t>::displace(trans, units);

        if (!this->hasPrecedingInterval())
            return;

        // Set new threshold on day interval
        uint16_t newDayMax{
            simplydt::getTotalDaysInMonth(
                this->precedingPosition(),// Year value
                this->position()// Month value
            )
        };

        // Need confirmation that this is logic-safe
        this->setSubsequentThreshold(newDayMax);
    }

    /* Increase month value by provided amount of units */
    void increment(uint16_t units = (uint16_t)1U) noexcept
    {
        this->displace(Trans::POSITIVE, units);
    }

    /* Decrease month value by provided amount of units */
    void decrement(uint16_t units = (uint16_t)1U) noexcept
    {
        this->displace(Trans::NEGATIVE, units);
    }

};



#endif // SIMPLYDTLIB_L_DATE_MONTH_H_
