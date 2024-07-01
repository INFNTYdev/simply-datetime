
#ifndef SIMPLYDTLIB_L_TIME_SECOND_H_
#define SIMPLYDTLIB_L_TIME_SECOND_H_



#include"simplydt/datetime/time/time_interval.hpp"


/* Datetime second */
class Second : public TimeInterval {
    
public:
    /* Second translation mode */
    using Trans = Interval<uint16_t>::Trans;

    Second(uint16_t value) noexcept
        : TimeInterval{ TimeInterval::SECOND, value }
    {
        //
    }

    ~Second() = default;

};



#endif // SIMPLYDTLIB_L_TIME_SECOND_H_
