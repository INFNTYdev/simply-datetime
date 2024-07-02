
#ifndef SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_
#define SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_



#include"simplydt/common/sequence/linked_sequence.hpp"


/* Sequence of linked datetime intervals */
template <typename... Dt_Interval_T>
class DatetimeSequence : public LinkedSequence<uint16_t, Dt_Interval_T...> {

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

    DatetimeSequence(DatetimeType dt_type, Dt_Interval_T&&... dt_intervals)
        : LinkedSequence<uint16_t, Dt_Interval_T...>{
            std::forward<Dt_Interval_T&&>(dt_intervals)...
        },
        m_datetimeType{ dt_type }
    {
        //
    }

    ~DatetimeSequence() noexcept = default;

    DatetimeSequence<Dt_Interval_T...>& operator=(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) noexcept;
    DatetimeSequence<Dt_Interval_T...>& operator=(DatetimeSequence<Dt_Interval_T...>&& dt_sequence) noexcept;
    bool operator==(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    bool operator<(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    bool operator>(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    bool operator<=(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    bool operator>=(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    Interval<uint16_t>* operator[](size_t index) noexcept;

    /* Returns datetime sequence type */
    DatetimeType datetimeType() const noexcept
    {
        return this->m_datetimeType;
    }

    /* Returns true if provided datetime sequence occurs after this one */
    bool isBefore(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    /* Returns true if provided datetime sequence occurs before this one */
    bool isAfter(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    /* Returns sequence of differences between this and provided datetime sequence */
    DatetimeSequence<Dt_Interval_T...> getDelta(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept;
    /* Increase value of datetime interval at provided position if any, provided amount of units */
    bool incrementInterval(size_t index, uint16_t units) noexcept;
    /* Decrease value of datetime interval at provided position if any, provided amount of units */
    bool decrementInterval(size_t index, uint16_t units) noexcept;


private:
    DatetimeType m_datetimeType;

};



#endif // SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_
