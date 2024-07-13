
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
    const char* getTitle() const noexcept
    {
        return simplydt::getMonth(this->position());
    }

    /* Returns total number of days in month */
    uint16_t getTotalDays() const noexcept
    {
        if (!this->hasPrecedingInterval())
            return (uint16_t)0Ui16;
        
        return simplydt::getTotalDaysInMonth(
            this->precedingNode().position(),// Year value
            this->position()// Month value
        );
    }

    /* Set month value */
    bool setPosition(uint16_t pos) noexcept
    {
        if (!Interval<uint16_t>::setPosition(pos))
            return false;

        if (this->hasSubsequentInterval())
            this->updateDayThreshold();

        return true;
    }

    /* Set month value */
    bool setMonth(uint16_t month) noexcept
    {
        return this->setPosition(month);
    }

    /* Displace month in provided direction with provided units */
    void displace(Trans trans, uint16_t units) noexcept
    {
        DateInterval::dateDisplace(trans, units);
    }

    /* Displace month in provided direction with provided units */
    void largeDisplace(Trans trans, size_t units) noexcept
    {
        DateInterval::dateDisplace(trans, units);
    }

    /* Increase month value by provided amount of units */
    void increase(size_t units = (size_t)1Ui64) noexcept
    {
        this->largeDisplace(Trans::POSITIVE, units);
    }

    /* Decrease month value by provided amount of units */
    void decrease(size_t units = (size_t)1Ui64) noexcept
    {
        this->largeDisplace(Trans::NEGATIVE, units);
    }

};



#endif // SIMPLYDTLIB_L_DATE_MONTH_H_
