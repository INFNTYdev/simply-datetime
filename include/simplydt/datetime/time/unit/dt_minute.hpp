
#ifndef SIMPLYDTLIB_L_TIME_MINUTE_H_
#define SIMPLYDTLIB_L_TIME_MINUTE_H_



#include"simplydt/datetime/time/time_interval.hpp"


/* Datetime minute */
class Minute : public TimeInterval {
    
public:
    /* Minute translation mode */
    using Trans = Interval<uint16_t>::Trans;

    Minute(uint16_t value) noexcept
        : TimeInterval{ TimeInterval::MINUTE, value }
    {
        //
    }

    ~Minute() = default;

};



#endif // SIMPLYDTLIB_L_TIME_MINUTE_H_
