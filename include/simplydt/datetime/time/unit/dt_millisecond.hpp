
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

    std::string toTripleDigitStr() const noexcept
    {
        if (this->position() > (uint16_t)99Ui16)
            return this->toStr();

        if (this->position() < (uint16_t)10Ui16)
            return std::string{ ("00" + this->toStr()) };

        return std::string{ ('0' + this->toStr()) };
    }

};



#endif // SIMPLYDTLIB_L_TIME_MILLISECOND_H_
