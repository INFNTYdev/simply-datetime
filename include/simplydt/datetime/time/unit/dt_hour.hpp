
#ifndef SIMPLYDTLIB_L_TIME_HOUR_H_
#define SIMPLYDTLIB_L_TIME_HOUR_H_



#include"simplydt/datetime/time/time_interval.hpp"


/* Datetime hour */
class Hour : public TimeInterval {
    
public:
    /* Hour translation mode */
    using Trans = Interval<uint16_t>::Trans;

    /* Hour time phase */
    enum Phase { AM, PM };

    Hour(uint16_t value) noexcept
        : TimeInterval{ TimeInterval::HOUR, value }
    {
        //
    }

    ~Hour() = default;

};



#endif // SIMPLYDTLIB_L_TIME_HOUR_H_
