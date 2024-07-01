
#ifndef SIMPLYDTLIB_L_TIME_MILLISECOND_H_
#define SIMPLYDTLIB_L_TIME_MILLISECOND_H_



#include"simplydt/datetime/time/time_interval.hpp"


/* Datetime millisecond */
class Millisecond : public TimeInterval {
    
public:
    /* Millisecond translation mode */
    using Trans = Interval<uint16_t>::Trans;

    Millisecond(uint16_t value) noexcept
        : TimeInterval{ TimeInterval::MILLISECOND, value }
    {
        //
    }

    ~Millisecond() = default;

};



#endif // SIMPLYDTLIB_L_TIME_MILLISECOND_H_
