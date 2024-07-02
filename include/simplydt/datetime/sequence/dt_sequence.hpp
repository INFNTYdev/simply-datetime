
#ifndef SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_
#define SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_



#include"simplydt/common/sequence/linked_sequence.hpp"


/* Sequence of linked datetime intervals */
template <typename... Interval_T>
class DatetimeSequence : public LinkedSequence<uint16_t, Interval_T...> {

public:
    /* Datetime time unit */
    enum TimeUnit {
        ARB,// Arbitrary time unit
        YEAR,// Year time unit
        MONTH,// Month time unit
        DAY,// Day time unit
        HOUR,// Hour time unit
        MINUTE,// Minute time unit
        SECOND,// Second time unit
        MILLISECOND,// Millisecond time unit
    };

    /* Datetime type */
    enum DatetimeType {
        ARB_DATETIME,// Arbitrary datetime type
        DATE_DATETIME,// Date type
        TIME_DATETIME,// Time type
        DATETIME,// Full datetime type
        STANDARD_DATETIME,// Standard datetime type
        DURATION_DATETIME,// Duration datetime type
    };

    DatetimeSequence(DatetimeType dt_type, Interval_T&&... dt_intervals)
        : LinkedSequence<uint16_t, Interval_T...>{
            std::forward<Interval_T&&>(dt_intervals)...
        },
        m_datetimeType{ dt_type }
    {
        //
    }

    ~DatetimeSequence() noexcept = default;

    /* Returns datetime sequence type */
    DatetimeType datetimeType() const noexcept
    {
        return this->m_datetimeType;
    }


private:
    DatetimeType m_datetimeType;

};



#endif // SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_
