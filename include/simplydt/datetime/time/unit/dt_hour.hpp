
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

    /* Returns hour day phase */
    Phase getPhase() const noexcept
    {
        if (this->position() < (uint16_t)12U)
            return Phase::AM;
        
        return Phase::PM;
    }

    /* Returns hour day phase literal */
    std::string getPhaseStr() const noexcept
    {
        switch (this->getPhase()) {
        case Phase::AM:
            return "AM";
        default:
            return "PM";
        }
    }

    /* Returns 12-hour representation of hour */
    uint16_t standardPosition() const noexcept
    {
        if (this->position() == (uint16_t)0U)
            return (uint16_t)12U;
        
        if (this->position() > (uint16_t)12U)
            return (this->position() - (uint16_t)12U);

        return this->position();
    }

    /* Returns 12-hour string representation of hour */
    std::string toStandardStr() const noexcept
    {
        return std::to_string(this->standardPosition());
    }

    /* Returns 12-hour string representation of hour in double digit format */
    std::string toDoubleDigitStandardStr() const noexcept
    {
        if (this->position() == (uint16_t)0U)
            return toStandardStr();

        if (this->position() < (uint16_t)10U)
            return std::string{ ('0' + this->toStr()) };
        else
            return this->toStandardStr();
    }

};



#endif // SIMPLYDTLIB_L_TIME_HOUR_H_
