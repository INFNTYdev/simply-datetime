
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
    const char* getDayOfWeek() noexcept
    {
        if (!this->hasPrecedingInterval())
            return nullptr;
        
        if (!this->getPrecedingInterval()->hasPrecedingInterval())
            return nullptr;
        
        return simplydt::getDayOfWeek(
            this->getPrecedingInterval()->precedingPosition(),// Year value
            this->precedingPosition(),// Month value
            this->position()// Day value
        );
    }

};



#endif // SIMPLYDTLIB_L_DATE_DAY_H_
