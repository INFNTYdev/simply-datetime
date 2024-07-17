
#ifndef SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_



#include<chrono>

#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/duration/unit/dur_unit_def.hpp"
#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"


/* Virtual time duration ( dd:HH:MM:SS:MS ) */
class VDuration : public DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::DatetimeType;
    /* Duration direction sign */
    using Sign = Interval<uint16_t>::Trans;
    /* Standard library chronological duration (64-bit) */
    using ChronoDuration = std::chrono::duration<size_t>;

    /* Duration layout */
    enum Layout {
        SIGN_D_H_M_S_MS,// ( +/- dd:HH:MM:SS:MS ) [ Example: +124:08:30:00:00 ]
        D_H_M_S_MS,// ( dd:HH:MM:SS:MS ) [ Example: 124:08:30:00:00 ]
        SIGN_D_H_M_S,// ( +/- dd:HH:MM:SS ) [ Example: -124:08:30:00 ]
        D_H_M_S,// ( dd:HH:MM:SS ) [ Example: 124:08:30:00 ]
        SIGN_D_H_M,// ( +/- dd:HH:MM ) [ Example: +124:08:30 ]
        D_H_M,// ( dd:HH:MM ) [ Example: 124:08:30 ]
        SIGN_D_H,// ( +/- dd:HH ) [ Example: +124:08 ]
        D_H,// ( dd:HH ) [ Example: 124:08 ]
    };

    VDuration(Sign sign, uint16_t days, uint16_t hour, uint16_t minute, uint16_t second, uint16_t ms) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute(minute),
            Second(second),
            Millisecond(ms)
        },
        m_directionSign{ sign }
    {
        //
    }

    VDuration(uint16_t days, uint16_t hour, uint16_t minute, uint16_t second, uint16_t ms) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute(minute),
            Second(second),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ Sign::POSITIVE }
    {
        //
    }

    VDuration(Sign sign, uint16_t days, uint16_t hour, uint16_t minute, uint16_t second) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute(minute),
            Second(second),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ sign }
    {
        //
    }
    
    VDuration(uint16_t days, uint16_t hour, uint16_t minute, uint16_t second) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute(minute),
            Second(second),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ Sign::POSITIVE }
    {
        //
    }

    VDuration(Sign sign, uint16_t days, uint16_t hour, uint16_t minute) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute(minute),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ sign }
    {
        //
    }
    
    VDuration(uint16_t days, uint16_t hour, uint16_t minute) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute(minute),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ Sign::POSITIVE }
    {
        //
    }

    VDuration(Sign sign, uint16_t days, uint16_t hour) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ sign }
    {
        //
    }
    
    VDuration(uint16_t days, uint16_t hour) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour(hour),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ Sign::POSITIVE }
    {
        //
    }

    VDuration(Sign sign, uint16_t days) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ sign }
    {
        //
    }

    explicit VDuration(uint16_t days) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, days),
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ Sign::POSITIVE }
    {
        //
    }

    explicit VDuration(Sign sign) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, (uint16_t)0U),
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ sign }
    {
        //
    }

    VDuration(const ChronoDuration& chrono_duration) noexcept;//   <--- INCOMPLETE!

    VDuration() noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            DatetimeType::DURATION_DATETIME,
            ArbDay((uint16_t)0U, (uint16_t)0U, (uint16_t)0U),
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        },
        m_directionSign{ Sign::POSITIVE }
    {
        //
    }

    VDuration(const VDuration& duration) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{ duration },
        m_directionSign{ duration.m_directionSign }
    {
        //
    }

    VDuration(VDuration&& duration) noexcept
        : DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>{
            std::forward<DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>>(
                static_cast<DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>&&>(duration)
            )
        },
        m_directionSign{ std::move(duration.m_directionSign) }
    {
        //
    }

    ~VDuration() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VDuration& duration) noexcept
    {
        os << duration.durationStr();

        return os;
    }

    VDuration& operator=(const VDuration& duration) noexcept
    {
        if (this == &duration)
            return *this;
        
        DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::operator=(duration);
        this->m_directionSign = duration.m_directionSign;

        return *this;
    }

    VDuration& operator=(VDuration&& duration) noexcept
    {
        if (this == &duration)
            return *this;
        
        DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::operator=(
            std::forward<DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>>(
                static_cast<DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>&&>(duration)
            )
        );
        this->m_directionSign = duration.m_directionSign;

        return *this;
    }

    VDuration& operator=(const ChronoDuration& chrono_duration) noexcept;//   <--- INCOMPLETE!

    bool operator==(const VDuration& duration) const noexcept
    {
        if (this == &duration)
            return true;

        if (this->m_directionSign != duration.m_directionSign)
            return false;

        return DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::operator==(duration);
    }

    bool operator<(const VDuration& duration) const noexcept
    {
        return this->isShorterThan(duration);
    }

    bool operator>(const VDuration& duration) const noexcept
    {
        return this->isLongerThan(duration);
    }

    bool operator<=(const VDuration& duration) const noexcept
    {
        return (this->isShorterThan(duration) || this->operator==(duration));
    }

    bool operator>=(const VDuration& duration) const noexcept
    {
        return (this->isLongerThan(duration) || this->operator==(duration));
    }

    VDuration operator+(const VDuration& duration) const noexcept
    {
        VDuration result{ *this };

        result.displace(duration);

        return result;
    }

    VDuration operator-(const VDuration& duration) const noexcept
    {
        VDuration result{ *this };

        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            result.positiveDisplace(duration);
            break;

        default:
            result.displace(duration);
        }

        return result;
    }

    VDuration& operator+=(const VDuration& duration) noexcept
    {
        this->displace(duration);

        return *this;
    }

    VDuration& operator-=(const VDuration& duration) noexcept
    {
        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            this->positiveDisplace(duration);
            break;

        default:
            this->displace(duration);
        }

        return *this;
    }

    /* Returns product of this duration and integer */
    VDuration operator*(const long long int& integer) const noexcept
    {
        // Determine multiplicand effect
        bool negativeMultiplicand{ (integer < 0LL) };

        size_t product{ 0 };

        // Obtain product
        if (negativeMultiplicand)
            product = (this->convertedTo(VDuration::TimeUnit::MILLISECOND) * (size_t)(integer * -1LL));
        else
            product = (this->convertedTo(VDuration::TimeUnit::MILLISECOND) * integer);

        // Provide product to duration
        VDuration result{};
        result.getInterval(MILLIS_INDEX)->largeDisplace(VDuration::Sign::POSITIVE, product);

        // Negative duration multiplied by positive number
        if (this->m_directionSign == Sign::NEGATIVE && !negativeMultiplicand)
            result.invert();
        
        // Positive duration multiplied by negative number
        if (this->m_directionSign == Sign::POSITIVE && negativeMultiplicand)
            result.invert();

        return result;
    }

    /* Multiply duration by provided integer */
    VDuration& operator*=(const long long int& integer) noexcept
    {
        // Determine multiplicand effect
        bool negativeMultiplicand{ (integer < 0LL) };

        size_t product{ 0 };

        size_t millisecs{ this->convertedTo(VDuration::TimeUnit::MILLISECOND) };

        // Obtain product
        if (negativeMultiplicand)
            product = (millisecs * (size_t)(integer * -1LL));
        else
            product = (millisecs * integer);
        
        // Handle zero product
        if (product == (size_t)0ULL) {
            this->getInterval(MILLIS_INDEX)->largeDisplace(
                VDuration::Sign::NEGATIVE,
                millisecs
            );

            if (this->m_directionSign == Sign::NEGATIVE)
                this->invert();
            
            return *this;
        }

        // Deduct this pre-existing milliseconds
        product -= millisecs;

        // Provide product to this
        this->getInterval(MILLIS_INDEX)->largeDisplace(
            VDuration::Sign::POSITIVE,
            product
        );

        // Handle this duration sign
        if (this->m_directionSign == Sign::NEGATIVE && negativeMultiplicand)
            this->invert();// Double negative = positive
        else if (this->m_directionSign == Sign::POSITIVE && negativeMultiplicand)
            this->invert();

        return *this;
    }

    /* Returns quotient of this duration and provided duration as quantity */
    long long int operator/(const VDuration& duration) const noexcept
    {
        // Determine division effect
        bool negativeQuotient{
            ((this->sign() == Sign::NEGATIVE && duration.sign() == Sign::POSITIVE)
            || (this->sign() == Sign::POSITIVE && duration.sign() == Sign::NEGATIVE))
        };

        size_t dividend{ this->convertedTo(VDuration::TimeUnit::MILLISECOND) };
        size_t divisor{ duration.convertedTo(VDuration::TimeUnit::MILLISECOND) };

        // Divide by zero error
        if (divisor == (size_t)0ULL)
            return (long long int)0LL;

        // Overflow will never occur with 16-bit based duration intervals
        long long int quotient{ (long long)(dividend / divisor) };

        if (negativeQuotient)
            quotient *= -1LL;

        return quotient;
    }

    /* Returns modulus of this duration and provided duration as duration */
    VDuration operator%(const VDuration& duration) const noexcept
    {
        long long int multiplicand{ *this / duration };

        // NOTE: <--- This is temporary until more thought
        if (multiplicand == (long long)0LL)
            return VDuration{};
        
        // No remainder
        if ((duration * multiplicand) == *this)
            return VDuration{};

        return (duration * multiplicand).until(*this);
    }

    VDuration& operator%=(const VDuration& duration) noexcept
    {
        long long int multiplicand{ *this / duration };

        // NOTE: <--- This is temporary until more thought (zero multiplicand)
        if (multiplicand == (long long)0LL || (duration * multiplicand) == *this) {
            this->getInterval(MILLIS_INDEX)->largeDisplace(
                VDuration::Sign::NEGATIVE,
                this->convertedTo(VDuration::TimeUnit::MILLISECOND)
            );

            if (this->m_directionSign == Sign::NEGATIVE)
                this->invert();
            
            return *this;
        }

        this->operator=((duration * multiplicand).until(*this));

        return *this;
    }

    /* Returns duration elapsed days */
    uint16_t days() const noexcept
    {
        return this->getInterval(ARBDAY_INDEX)->position();
    }

    /* Returns duration hours */
    uint16_t hour() const noexcept
    {
        return this->getInterval(HOUR_INDEX)->position();
    }

    /* Returns duration minutes */
    uint16_t minute() const noexcept
    {
        return this->getInterval(MINUTE_INDEX)->position();
    }

    /* Returns duration seconds */
    uint16_t second() const noexcept
    {
        return this->getInterval(SECOND_INDEX)->position();
    }

    /* Returns duration milliseconds */
    uint16_t millisecond() const noexcept
    {
        return this->getInterval(MILLIS_INDEX)->position();
    }

    /* Returns duration direction sign */
    Sign sign() const noexcept
    {
        return this->m_directionSign;
    }

    /* Returns duration direction sign character literal */
    char signChar() const noexcept
    {
        switch (this->m_directionSign) {
        case Sign::NEGATIVE:
            return '-';
        default:
            return '+';
        }
    }

    /* Returns duration string with provided format */
    std::string durationStr(Layout layout) const noexcept
    {
        std::string duration;
        duration.reserve((size_t)25ULL);
        duration = "";

        char delimiter{ ':' };

        switch (layout) {
        case Layout::SIGN_D_H_M_S_MS:
        case Layout::SIGN_D_H_M_S:
        case Layout::SIGN_D_H_M:
        case Layout::SIGN_D_H:
            duration += this->signChar();
            duration += (this->getInterval(ARBDAY_INDEX)->toStr() + delimiter);
            duration += this->retrieveHour()->toDoubleDigitStr();
            break;

        default:
            duration += (this->getInterval(ARBDAY_INDEX)->toStr() + delimiter);
            duration += this->retrieveHour()->toDoubleDigitStr();
        }

        switch (layout) {
        case Layout::SIGN_D_H_M:
        case Layout::D_H_M:
            duration += (delimiter + this->retrieveMinute()->toDoubleDigitStr());
            break;

        case Layout::SIGN_D_H_M_S:
        case Layout::D_H_M_S:
            duration += (delimiter + this->retrieveMinute()->toDoubleDigitStr());
            duration += (delimiter + this->retrieveSecond()->toDoubleDigitStr());
            break;

        case Layout::SIGN_D_H_M_S_MS:
        case Layout::D_H_M_S_MS:
            duration += (delimiter + this->retrieveMinute()->toDoubleDigitStr());
            duration += (delimiter + this->retrieveSecond()->toDoubleDigitStr());
            duration += (delimiter + this->retrieveMillisecond()->toTripleDigitStr());
            break;
        }

        return duration;
    }

    /* Returns duration string */
    std::string durationStr() const noexcept
    {
        return this->durationStr(Layout::SIGN_D_H_M_S_MS);
    }

    /* Returns arbitrary day in duration */
    ArbDay& getDays() const noexcept
    {
        return *(this->retrieveDays());
    }

    /* Returns hour in duration */
    Hour& getHour() const noexcept
    {
        return *(this->retrieveHour());
    }

    /* Returns minute in duration */
    Minute& getMinute() const noexcept
    {
        return *(this->retrieveMinute());
    }

    /* Returns second in duration */
    Second& getSecond() const noexcept
    {
        return *(this->retrieveSecond());
    }

    /* Returns millisecond in duration */
    Millisecond& getMillisecond() const noexcept
    {
        return *(this->retrieveMillisecond());
    }

    /* Returns true if provided duration is longer than this one */
    bool isShorterThan(const VDuration& duration) const noexcept
    {
        if (this == &duration)
            return false;

        if (this->m_directionSign == Sign::POSITIVE && duration.m_directionSign == Sign::NEGATIVE)
            return false;
        
        if (this->m_directionSign == Sign::NEGATIVE && duration.m_directionSign == Sign::POSITIVE)
            return true;

        return this->isBefore(duration);
    }

    /* Returns true if provided duration is shorter than this one */
    bool isLongerThan(const VDuration& duration) const noexcept
    {
        if (this == &duration)
            return false;

        if (this->m_directionSign == Sign::POSITIVE && duration.m_directionSign == Sign::NEGATIVE)
            return true;
        
        if (this->m_directionSign == Sign::NEGATIVE && duration.m_directionSign == Sign::POSITIVE)
            return false;

        return this->isAfter(duration);
    }

    /* Returns elapsed duration compressed into provided unit  */
    size_t convertedTo(TimeUnit unit) const noexcept
    {
        size_t total{ 0 };

        switch (unit) {
        case TimeUnit::DAY:
            total += this->days();
            break;

        case TimeUnit::HOUR:
            total += ((size_t)this->days() * (size_t)24ULL);
            total += this->hour();
            break;

        case TimeUnit::MINUTE:
            total += ((size_t)this->days() * (size_t)1'440ULL);
            total += ((size_t)this->hour() * (size_t)60ULL);
            total += this->minute();
            break;

        case TimeUnit::SECOND:
            total += ((size_t)this->days() * (size_t)86'400ULL);
            total += ((size_t)this->hour() * (size_t)3'600ULL);
            total += ((size_t)this->minute() * (size_t)60ULL);
            total += this->second();
            break;

        case TimeUnit::MILLISECOND:
            total += ((size_t)this->days() * (size_t)86'400'000ULL);
            total += ((size_t)this->hour() * (size_t)3'600'000ULL);
            total += ((size_t)this->minute() * (size_t)60'000ULL);
            total += ((size_t)this->second() * (size_t)1'000ULL);
            total += this->millisecond();
        }

        return total;
    }

    /* Returns durations as standard chronological duration */
    std::chrono::duration<size_t> toChronoDuration() const noexcept
    {
        std::chrono::duration<size_t> duration{
            this->convertedTo(VDuration::TimeUnit::SECOND)
        };

        return duration;
    }

    /* Returns absolute total number of seconds from this duration until provided duration */
    size_t secondsUntil(const VDuration& duration) const noexcept
    {
        size_t totalSeconds{ 0 };

        if (this == &duration || *this == duration)
            return totalSeconds;

        std::pair<const VDuration*, const VDuration*> durationRef{ nullptr, nullptr };// (high, low)

        if (this->isLongerThan(duration)) {
            durationRef.first = this;
            durationRef.second = &duration;
        }
        else {
            durationRef.first = &duration;
            durationRef.second = this;
        }
        
        size_t longSeconds{ durationRef.first->convertedTo(TimeUnit::SECOND) };
        size_t shortSeconds{ durationRef.second->convertedTo(TimeUnit::SECOND) };

        totalSeconds = (longSeconds - shortSeconds);

        return totalSeconds;
    }

    /* Returns absolute total number of milliseconds from this duration until provided duration */
    size_t millisecondsUntil(const VDuration& duration) const noexcept
    {
        size_t totalMs{ 0 };

        if (this == &duration || *this == duration)
            return totalMs;

        std::pair<const VDuration*, const VDuration*> durationRef{ nullptr, nullptr };// (high, low)

        if (this->isLongerThan(duration)) {
            durationRef.first = this;
            durationRef.second = &duration;
        }
        else {
            durationRef.first = &duration;
            durationRef.second = this;
        }
        
        size_t longMs{ durationRef.first->convertedTo(TimeUnit::MILLISECOND) };
        size_t shortMs{ durationRef.second->convertedTo(TimeUnit::MILLISECOND) };

        totalMs = (longMs - shortMs);

        return totalMs;
    }

    /* Returns duration from this to provided duration */
    VDuration until(const VDuration& duration) const noexcept
    {
        if (this == &duration || *this == duration)
            return VDuration{};

        if (this->isLongerThan(duration)) {
            VDuration newDur{ Sign::NEGATIVE };

            newDur.getMillisecond().largeDisplace(
                Sign::POSITIVE,
                this->millisecondsUntil(duration)
            );

            return newDur;
        }
        else {
            VDuration newDur{ Sign::POSITIVE };

            newDur.getMillisecond().largeDisplace(
                Sign::POSITIVE,
                this->millisecondsUntil(duration)
            );

            return newDur;
        }
    }

    /* Displace duration using provided duration */
    void displace(const VDuration& duration) noexcept
    {
        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            return this->negativeDisplace(duration);
        default:
            return this->positiveDisplace(duration);
        }
    }

    /* Invert duration direction sign */
    void invert() noexcept
    {
        switch (this->m_directionSign) {
        case Sign::POSITIVE:
            this->m_directionSign = Sign::NEGATIVE;
            return;
        default:
            this->m_directionSign = Sign::POSITIVE;
            return;
        }
    }


private:
    static const uint8_t ARBDAY_INDEX{ 0 };
    static const uint8_t HOUR_INDEX{ 1 };
    static const uint8_t MINUTE_INDEX{ 2 };
    static const uint8_t SECOND_INDEX{ 3 };
    static const uint8_t MILLIS_INDEX{ 4 };

    Sign m_directionSign;

    size_t timeUnitEnumToIndex(TimeUnit time_unit) noexcept
    {
        switch (time_unit) {
        case TimeUnit::DAY:
            return ARBDAY_INDEX;
        case TimeUnit::HOUR:
            return HOUR_INDEX;
        case TimeUnit::MINUTE:
            return MINUTE_INDEX;
        case TimeUnit::SECOND:
            return SECOND_INDEX;
        case TimeUnit::MILLISECOND:
            return MILLIS_INDEX;
        default:
            return this->linkSize();// Results in nullptr interval
        }
    }

    TimeUnit indexToTimeUnitEnum(size_t index) noexcept
    {
        switch (index) {
        case ARBDAY_INDEX:
            return TimeUnit::DAY;
        case HOUR_INDEX:
            return TimeUnit::HOUR;
        case MINUTE_INDEX:
            return TimeUnit::MINUTE;
        case SECOND_INDEX:
            return TimeUnit::SECOND;
        case MILLIS_INDEX:
            return TimeUnit::MILLISECOND;
        default:
            return TimeUnit::ARB;
        }
    }

    ArbDay* retrieveDays() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(ARBDAY_INDEX) };

        return static_cast<ArbDay*>(rawInterval);
    }

    Hour* retrieveHour() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(HOUR_INDEX) };

        return static_cast<Hour*>(rawInterval);
    }

    Minute* retrieveMinute() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(MINUTE_INDEX) };

        return static_cast<Minute*>(rawInterval);
    }

    Second* retrieveSecond() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(SECOND_INDEX) };

        return static_cast<Second*>(rawInterval);
    }

    Millisecond* retrieveMillisecond() const noexcept
    {
        Interval<uint16_t>* rawInterval{ this->getInterval(MILLIS_INDEX) };

        return static_cast<Millisecond*>(rawInterval);
    }

    void positiveDisplace(const VDuration& duration) noexcept
    {
        // Handle opposing duration signs
        if (this->sign() == Sign::NEGATIVE) {
            if (this->isAfter(duration)) {
                // Short positive duration being added to this longer negative duration
                return this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::NEGATIVE,
                    duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
                );
            }

            if (this->isBefore(duration)) {
                // Long positive duration being added to this shorter negative duration
                size_t difference{
                    (duration.convertedTo(VDuration::TimeUnit::MILLISECOND) - this->convertedTo(VDuration::TimeUnit::MILLISECOND))
                };

                // NOTE: Instead, we should be finding our way from current position
                this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::NEGATIVE,
                    this->convertedTo(VDuration::TimeUnit::MILLISECOND)
                );

                this->m_directionSign = Sign::POSITIVE;

                return this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::POSITIVE,
                    difference
                );
            }

            if (DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::operator==(duration)) {
                // Equal positive duration being added to this negative duration
                return this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::NEGATIVE,
                    duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
                );
            }
        }

        // Normal displace
        return this->getInterval(MILLIS_INDEX)->largeDisplace(
            VDuration::Sign::POSITIVE,
            duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
        );
    }

    void negativeDisplace(const VDuration& duration) noexcept
    {
        // Handle opposing duration signs
        if (this->sign() == Sign::POSITIVE) {
            if (this->isAfter(duration)) {
                // Short negative duration being added to this longer positive duration
                return this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::NEGATIVE,
                    duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
                );
            }

            if (this->isBefore(duration)) {
                // Long negative duration being added to this shorter positive duration
                size_t difference{
                    (duration.convertedTo(VDuration::TimeUnit::MILLISECOND) - this->convertedTo(VDuration::TimeUnit::MILLISECOND))
                };

                // NOTE: Instead, we should be finding our way from current position
                this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::NEGATIVE,
                    this->convertedTo(VDuration::TimeUnit::MILLISECOND)
                );

                this->m_directionSign = Sign::NEGATIVE;

                return this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::POSITIVE,
                    difference
                );
            }

            if (DatetimeSequence<ArbDay, Hour, Minute, Second, Millisecond>::operator==(duration)) {
                // Equal negative duration being added to this positive duration
                return this->getInterval(MILLIS_INDEX)->largeDisplace(
                    VDuration::Sign::NEGATIVE,
                    duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
                );
            }
        }

        // Normal displace
        return this->getInterval(MILLIS_INDEX)->largeDisplace(
            VDuration::Sign::POSITIVE,
            duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
        );
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_DURATION_SEQUENCE_OBJ_H_
