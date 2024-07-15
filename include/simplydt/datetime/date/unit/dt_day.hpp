
#ifndef SIMPLYDTLIB_L_DATE_DAY_H_
#define SIMPLYDTLIB_L_DATE_DAY_H_



#include"simplydt/datetime/date/date_interval.hpp"
#include"simplydt/datetime/date/date_utility.hpp"


/* Datetime day */
class Day : public DateInterval {

public:
    /* Day translation mode */
    using Trans = Interval<uint16_t>::Trans;

    Day(uint16_t value) noexcept
        : DateInterval{ DateInterval::DAY, value }
    {
        //
    }

    ~Day() = default;

    /* Returns days day-of-week literal if linked in a date */
    const char* getDayOfWeek() const noexcept
    {
        if (!this->hasPrecedingInterval())
            return nullptr;
        
        if (!this->precedingNode().hasPrecedingInterval())
            return nullptr;
        
        return simplydt::getDayOfWeek(
            this->precedingNode().precedingNode().position(),// Year value
            this->precedingNode().position(),// Month value
            this->position()// Day value
        );
    }

    /* Set day value */
    bool setDay(uint16_t day) noexcept
    {
        return this->setPosition(day);
    }

    /* Translate day in provided direction with provided units */
    void displace(Trans trans, uint16_t units) noexcept
    {
        if (this->untilThreshold() >= units)
            return Interval<uint16_t>::displace(trans, units);

        DateInterval::dateDisplace(trans, units);
    }

    /* Translate day in provided direction with provided units */
    void largeDisplace(Trans trans, size_t units) noexcept
    {
        DateInterval::dateDisplace(trans, units);
    }

    /* Increase day provided number of units */
    void increase(size_t units = (size_t)1Ui64) noexcept
    {
        this->largeDisplace(Trans::POSITIVE, units);
    }

    /* Decrease day provided number of units */
    void decrease(size_t units = (size_t)1Ui64) noexcept
    {
        this->largeDisplace(Trans::NEGATIVE, units);
    }

};



#endif // SIMPLYDTLIB_L_DATE_DAY_H_
