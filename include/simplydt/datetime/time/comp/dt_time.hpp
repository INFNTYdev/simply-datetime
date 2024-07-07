
#ifndef SIMPLYDTLIB_L_DATETIME_TIME_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_TIME_SEQUENCE_OBJ_H_



#include<chrono>

#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/duration/comp/dt_duration.hpp"
#include"simplydt/datetime/time/comp/dt_stime.hpp"


/* Full time ( HH:MM:SS:MS ) */
class Time : public DatetimeSequence<Hour, Minute, Second, Millisecond> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Hour, Minute, Second, Millisecond>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Hour, Minute, Second, Millisecond>::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using Chrono = std::chrono::time_point<std::chrono::system_clock>;
    /* 12-hr clock time phase */
    using Phase = Hour::Phase;

    /* Time format */
    enum Format {
        MILITARY,// Military time format (24-hour)
        STANDARD,// Standard time format (12-hour)
    };

    /* Time layout */
    enum Layout {
        H_M_S_MS,// (HH:MM:SS:MS) [ Example: 08:30:00:00 ]
        H_M_S_MS_P,// (HH:MM:SS:MS P) [ Example: 08:30:00:00 AM ]
        H_M_S,// (HH:MM:SS) [ Example: 08:30:00 ]
        H_M_S_P,// (HH:MM:SS P) [ Example: 08:30:00 AM ]
        H_M,// (HH:MM) [ Example: 08:30 ]
        H_M_P,// (HH:MM P) [ Example: 08:30 AM ]
    };

    Time(Chrono chrono) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        }
    {
        std::time_t timeT{ std::chrono::system_clock::to_time_t(chrono) };
        std::tm* tm_ptr{ std::localtime(&timeT) };

        // Retrieve time from time point
        uint16_t tmHour{ static_cast<uint16_t>(tm_ptr->tm_hour) };
        uint16_t tmMinute{ static_cast<uint16_t>(tm_ptr->tm_min) };
        uint16_t tmSecond{ static_cast<uint16_t>(tm_ptr->tm_sec) };

        // Set time interval values
        this->getInterval(HOUR_INDEX)->setPosition(tmHour);
        this->getInterval(MINUTE_INDEX)->setPosition(tmMinute);
        this->getInterval(SECOND_INDEX)->setPosition(tmSecond);
    }

    Time(uint16_t hour, uint16_t minute, uint16_t second, uint16_t ms) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second(second),
            Millisecond(ms)
        }
    {
        //
    }

    Time(uint16_t hour, uint16_t minute, uint16_t second) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second(second),
            Millisecond((uint16_t)0U)
        }
    {
        //
    }

    Time(uint16_t hour, uint16_t minute) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        }
    {
        //
    }

    Time(uint16_t hour) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        }
    {
        //
    }

    Time() noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U),
            Millisecond((uint16_t)0U)
        }
    {
        //
    }

    Time(const STime& s_time) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour(s_time.getHour()),
            Minute(s_time.getMinute()),
            Second(s_time.getSecond()),
            Millisecond((uint16_t)0U)
        }
    {
        //
    }

    Time(STime&& s_time) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour(std::move(s_time.getHour())),
            Minute(std::move(s_time.getMinute())),
            Second(std::move(s_time.getSecond())),
            Millisecond((uint16_t)0U)
        }
    {
        //
    }

    virtual ~Time() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Time& time) noexcept
    {
        os << time.timeStr();

        return os;
    }

    Time& operator=(const STime& s_time) noexcept
    {
        this->getInterval(HOUR_INDEX)->setPosition(s_time.hour());
        this->getInterval(MINUTE_INDEX)->setPosition(s_time.minute());
        this->getInterval(SECOND_INDEX)->setPosition(s_time.second());
        this->getInterval(MILLIS_INDEX)->setPosition((uint16_t)0U);

        return *this;
    }

    Time& operator=(STime&& s_time) noexcept
    {
        this->getHour() = std::move(s_time.getHour());
        this->getMinute() = std::move(s_time.getMinute());
        this->getSecond() = std::move(s_time.getSecond());
        this->getInterval(MILLIS_INDEX)->setPosition((uint16_t)0U);

        return *this;
    }

    // ---> DURATION OPERATORS HERE <---

    /* Returns hour of time */
    uint16_t hour() const noexcept
    {
        return this->getInterval(HOUR_INDEX)->position();
    }

    /* Returns minute of time */
    uint16_t minute() const noexcept
    {
        return this->getInterval(MINUTE_INDEX)->position();
    }

    /* Returns second of time */
    uint16_t second() const noexcept
    {
        return this->getInterval(SECOND_INDEX)->position();
    }

    /* Returns millisecond of time */
    uint16_t millisecond() const noexcept
    {
        return this->getInterval(MILLIS_INDEX)->position();
    }

    /* Returns time phase */
    Phase phase() const noexcept
    {
        return this->retrieveHour()->getPhase();
    }

    /* Returns time phase literal */
    std::string phaseStr() const noexcept
    {
        return this->retrieveHour()->getPhaseStr();
    }

    /* Returns time string with provided configuration */
    std::string timeStr(Format format, Layout layout) const noexcept
    {
        std::string time;
        time.reserve((size_t)15ULL);
        time = "";

        char delimiter{ ':' };

        switch (format) {
        case Format::STANDARD:
            time += (this->retrieveHour()->toDoubleDigitStandardStr() + delimiter);
            break;
        default:
            time += (this->retrieveHour()->toDoubleDigitStr() + delimiter);
            break;
        }

        time += this->retrieveMinute()->toDoubleDigitStr();

        switch (layout) {
        case Layout::H_M_S_MS:
            time += (delimiter + this->retrieveSecond()->toDoubleDigitStr());
            time += (delimiter + this->retrieveMillisecond()->toTripleDigitStr());
            break;
        case Layout::H_M_S_MS_P:
            time += (delimiter + this->retrieveSecond()->toDoubleDigitStr());
            time += (delimiter + this->retrieveMillisecond()->toTripleDigitStr());
            time += (' ' + this->phaseStr());
            break;
        case Layout::H_M_S:
            time += (delimiter + this->retrieveSecond()->toDoubleDigitStr());
            break;
        case Layout::H_M_S_P:
            time += (delimiter + this->retrieveSecond()->toDoubleDigitStr());
            time += (' ' + this->phaseStr());
            break;
        case Layout::H_M_P:
            time += (' ' + this->phaseStr());
        }

        return time;
    }

    /* Returns time string with provided configuration */
    std::string timeStr(Layout layout, Format format) const noexcept
    {
        return this->timeStr(format, layout);
    }

    /* Returns time string with provided format */
    std::string timeStr(Format format) const noexcept
    {
        return this->timeStr(format, Layout::H_M_S_MS);
    }

    /* Returns time string with provided layout */
    std::string timeStr(Layout layout) const noexcept
    {
        return this->timeStr(Format::MILITARY, layout);
    }

    /* Returns time string */
    std::string timeStr() const noexcept
    {
        return this->timeStr(Format::MILITARY, Layout::H_M_S_MS);
    }

    /* Returns hour in time */
    Hour& getHour() const noexcept
    {
        return *(this->retrieveHour());
    }

    /* Returns minute in time */
    Minute& getMinute() const noexcept
    {
        return *(this->retrieveMinute());
    }

    /* Returns second in time */
    Second& getSecond() const noexcept
    {
        return *(this->retrieveSecond());
    }

    /* Returns millisend in time */
    Millisecond& getMillisecond() const noexcept
    {
        return *(this->retrieveMillisecond());
    }

    ///* Returns time as standard chronological time point */
    //Chrono toChrono() const noexcept;

    /* Returns copy of full time as standard time */
    STime toSTime() const noexcept
    {
        return STime{ this->hour(), this->minute(), this->second() };
    }

    /* Link time to date instance */
    bool linkDate(Date& date) noexcept
    {
        return this->retrieveHour()->linkPrecedingInterval(date.getDay());
    }

    /* Returns time since day start compressed into provided unit  */
    uint32_t convertedTo(TimeUnit unit) const noexcept
    {
        uint32_t total{ 0 };

        switch (unit) {
        // Hour conversion
        case TimeUnit::HOUR:
            total += (uint32_t)this->hour();
            break;

        // Minute conversion
        case TimeUnit::MINUTE:
            total += ((uint32_t)this->hour() * (uint32_t)60U);
            total += (uint32_t)this->minute();
            break;

        // Second conversion
        case TimeUnit::SECOND:
            total += ((uint32_t)this->hour() * (uint32_t)3'600U);
            total += ((uint32_t)this->minute() * (uint32_t)60U);
            total += (uint32_t)this->second();
            break;

        // Millisecond conversion
        case TimeUnit::MILLISECOND:
            total += ((uint32_t)this->hour() * (uint32_t)3'600'000U);
            total += ((uint32_t)this->minute() * (uint32_t)60'000U);
            total += ((uint32_t)this->second() * (uint32_t)1'000U);
            total += (uint32_t)this->millisecond();
        }

        return total;
    }

    /* Returns total number of seconds from this time until provided time */
    size_t secondsUntil(const Time& time) const noexcept
    {
        size_t totalSeconds{ 0 };

        if (this == &time || *this == time)
            return totalSeconds;

        Time temp{ *this };

        // Accum. seconds
        totalSeconds += (
            temp.getInterval(SECOND_INDEX)->untilPosition(*time.getInterval(SECOND_INDEX))
        );
        temp.getInterval(SECOND_INDEX)->increment(
            temp.getInterval(SECOND_INDEX)->untilPosition(*time.getInterval(SECOND_INDEX))
        );

        // Accum. minutes
        totalSeconds += (
            ((size_t)temp.getInterval(MINUTE_INDEX)->untilPosition(*time.getInterval(MINUTE_INDEX)) * (size_t)60ULL)
        );
        temp.getInterval(MINUTE_INDEX)->increment(
            temp.getInterval(MINUTE_INDEX)->untilPosition(*time.getInterval(MINUTE_INDEX))
        );

        // Accum. hours
        totalSeconds += (
            ((size_t)temp.getInterval(HOUR_INDEX)->untilPosition(*time.getInterval(HOUR_INDEX)) * (size_t)3'600ULL)
        );

        return totalSeconds;
    }

    /* Returns total number of milliseconds from this time until provided time */
    size_t millisecondsUntil(const Time& time) const noexcept
    {
        size_t totalMs{ 0 };

        if (this == &time || *this == time)
            return totalMs;

        Time temp{ *this };

        // Accum. milliseconds
        totalMs += (
            temp.getInterval(MILLIS_INDEX)->untilPosition(*time.getInterval(MILLIS_INDEX))
        );
        temp.getInterval(MILLIS_INDEX)->increment(
            temp.getInterval(MILLIS_INDEX)->untilPosition(*time.getInterval(MILLIS_INDEX))
        );

        // Accum. seconds
        totalMs += (
            ((size_t)temp.getInterval(SECOND_INDEX)->untilPosition(*time.getInterval(SECOND_INDEX)) * (size_t)1'000ULL)
        );
        temp.getInterval(SECOND_INDEX)->increment(
            temp.getInterval(SECOND_INDEX)->untilPosition(*time.getInterval(SECOND_INDEX))
        );

        // Accum. minutes
        totalMs += (
            ((size_t)temp.getInterval(MINUTE_INDEX)->untilPosition(*time.getInterval(MINUTE_INDEX)) * (size_t)60'000ULL)
        );
        temp.getInterval(MINUTE_INDEX)->increment(
            temp.getInterval(MINUTE_INDEX)->untilPosition(*time.getInterval(MINUTE_INDEX))
        );

        // Accum. hours
        totalMs += (
            ((size_t)temp.getInterval(HOUR_INDEX)->untilPosition(*time.getInterval(HOUR_INDEX)) * (size_t)3'600'000ULL)
        );

        return totalMs;
    }

    /* Returns duration between this time and provided time */
    Duration until(const Time& time) const noexcept
    {
        if (this == &time || *this == time)
            return Duration{};

        Duration newDur{ Duration::Sign::POSITIVE };

        newDur.getMillisecond().largeDisplace(
            Duration::Sign::POSITIVE,
            this->millisecondsUntil(time)
        );

        return newDur;
    }

    /* Displace time using provided duration */
    void displace(const Duration& duration) noexcept
    {
        switch (duration.sign()) {
        case Duration::Sign::NEGATIVE:
            return this->getInterval(MILLIS_INDEX)->largeDisplace(
                Duration::Sign::NEGATIVE,
                duration.convertedTo(Duration::TimeUnit::MILLISECOND)
            );
        
        default:
            return this->getInterval(MILLIS_INDEX)->largeDisplace(
                Duration::Sign::POSITIVE,
                duration.convertedTo(Duration::TimeUnit::MILLISECOND)
            );
        }
    }


private:
    static const uint8_t HOUR_INDEX{ 0 };
    static const uint8_t MINUTE_INDEX{ 1 };
    static const uint8_t SECOND_INDEX{ 2 };
    static const uint8_t MILLIS_INDEX{ 3 };

    size_t timeUnitEnumToIndex(TimeUnit time_unit) noexcept
    {
        switch (time_unit) {
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

};



#endif // SIMPLYDTLIB_L_DATETIME_TIME_SEQUENCE_OBJ_H_
