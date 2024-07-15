
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

    DatetimeSequence(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) noexcept
        : LinkedSequence<uint16_t, Dt_Interval_T...>{
            static_cast<const LinkedSequence<uint16_t, Dt_Interval_T...>&>(dt_sequence)
        },
        m_datetimeType{ dt_sequence.m_datetimeType }
    {
        //
    }

    DatetimeSequence(DatetimeSequence<Dt_Interval_T...>&& dt_sequence) noexcept
        : LinkedSequence<uint16_t, Dt_Interval_T...>{
            std::forward<LinkedSequence<uint16_t, Dt_Interval_T...>>(
                static_cast<LinkedSequence<uint16_t, Dt_Interval_T...>&&>(dt_sequence)
            )
        },
        m_datetimeType{ std::move(dt_sequence.m_datetimeType) }
    {
        //
    }

    virtual ~DatetimeSequence() noexcept = default;

    DatetimeSequence<Dt_Interval_T...>& operator=(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) noexcept
    {
        if (this == &dt_sequence)
            return *this;
        
        std::vector<Interval<uint16_t>*> thisIntervalVec{ this->getIntervals() };
        std::vector<Interval<uint16_t>*> rhsIntervalVec{ dt_sequence.getIntervals() };

        for (size_t index{ 0 }; index < this->linkSize(); index++) {

            this->getInterval(index)->setPosition(
                dt_sequence.getInterval(index)->position()
            );

        }

        return *this;
    }

    DatetimeSequence<Dt_Interval_T...>& operator=(DatetimeSequence<Dt_Interval_T...>&& dt_sequence) noexcept
    {
        if (this == &dt_sequence)
            return *this;

        LinkedSequence<uint16_t, Dt_Interval_T...>::operator=(
            std::forward<LinkedSequence<uint16_t, Dt_Interval_T...>>(
                std::move(dt_sequence)
            )
        );

        this->m_datetimeType = std::move(dt_sequence.m_datetimeType);

        return *this;
    }
    
    /* Returns true if both date sequences have equally matching datetime intervals */
    bool operator==(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        if (this == &dt_sequence)
            return true;

        // Discrete, but the direction of this loop is important
        for (size_t index{ 0 }; index < this->linkSize(); index++) {

            if (this->getInterval(index)->position() != dt_sequence.getInterval(index)->position())
                return false;

        }

        return true;
    }

    /* Returns true if provided datetime sequence is greater than this one */
    bool operator<(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        return this->isBefore(dt_sequence);
    }

    /* Returns true if provided datetime sequence is less than this one */
    bool operator>(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        return this->isAfter(dt_sequence);
    }
    
    bool operator<=(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        return (this->isBefore(dt_sequence) || this->operator==(dt_sequence));
    }

    bool operator>=(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        return (this->isAfter(dt_sequence) || this->operator==(dt_sequence));
    }

    /* Returns datetime sequence interval at provided position if any */
    Interval<uint16_t>* operator[](size_t index) noexcept
    {
        return this->getInterval(index);
    }

    /* Returns datetime sequence type */
    DatetimeType datetimeType() const noexcept
    {
        return this->m_datetimeType;
    }

    /* Returns true if provided datetime sequence occurs after this one */
    bool isBefore(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        if (this == &dt_sequence)
            return false;

        for (size_t index{ 0 }; index < this->linkSize(); index++) {

            if (this->getInterval(index)->isAfter(*(dt_sequence.getInterval(index))))
                return false;

            if (this->getInterval(index)->isBefore(*(dt_sequence.getInterval(index))))
                return true;

        }

        return false;
    }

    /* Returns true if provided datetime sequence occurs before this one */
    bool isAfter(const DatetimeSequence<Dt_Interval_T...>& dt_sequence) const noexcept
    {
        if (this == &dt_sequence)
            return false;

        for (size_t index{ 0 }; index < this->linkSize(); index++) {

            if (this->getInterval(index)->isBefore(*(dt_sequence.getInterval(index))))
                return false;

            if (this->getInterval(index)->isAfter(*(dt_sequence.getInterval(index))))
                return true;

        }

        return false;
    }


private:
    DatetimeType m_datetimeType;

};



#endif // SIMPLYDTLIB_L_DATE_INTERVAL_SEQUENCE_H_
