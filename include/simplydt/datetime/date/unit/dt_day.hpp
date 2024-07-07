
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

    /* Translate day in provided direction with provided units */
	void displace(Trans trans, uint16_t units) noexcept
    {
        // I am not proud of this but I have to for now
        // There has to be a better way to do this...

        if (units <= this->untilThreshold())
            return Interval<uint16_t>::displace(trans, units);

        uint16_t translate{ 0 };

        // This is here to allow new day maximums to be accounted in calcs
        while (units != (uint16_t)0U) {

            translate = (this->untilThreshold() + (uint16_t)1U);

            if (translate > units)
                return Interval<uint16_t>::displace(trans, units);

            Interval<uint16_t>::displace(trans, translate);

            units -= translate;

        }
    }

};



#endif // SIMPLYDTLIB_L_DATE_DAY_H_
