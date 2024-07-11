
#ifndef SIMPLYDTLIB_L_DATETIME_STANDARD_TIME_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_STANDARD_TIME_SEQUENCE_OBJ_H_



#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/duration/comp/dt_duration.hpp"


/* Standard time (HH:MM:SS) */
class STime : public DatetimeSequence<Hour, Minute, Second> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Hour, Minute, Second>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Hour, Minute, Second>::DatetimeType;
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
        H_M_S,// (HH:MM:SS) [ Example: 08:30:00 ]
        H_M_S_P,// (HH:MM:SS P) [ Example: 08:30:00 AM ]
        H_M,// (HH:MM) [ Example: 08:30 ]
        H_M_P,// (HH:MM P) [ Example: 08:30 AM ]
    };

    STime(Chrono chrono) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U)
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

    STime(uint16_t hour, uint16_t minute, uint16_t second) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second(second)
        }
    {
        //
    }

    STime(uint16_t hour, uint16_t minute) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second((uint16_t)0U)
        }
    {
        //
    }

    STime(uint16_t hour) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute((uint16_t)0U),
            Second((uint16_t)0U)
        }
    {
        //
    }
    
    STime() noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0U),
            Minute((uint16_t)0U),
            Second((uint16_t)0U)
        }
    {
        //
    }

    virtual ~STime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const STime& s_time) noexcept
    {
        os << s_time.timeStr();

        return os;
    }

    STime& operator=(const Chrono& chrono) noexcept
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

        return *this;
    }

    STime operator+(const Duration& duration) const noexcept
    {
        STime result{ *this };

        result.displace(duration);

        return result;
    }

    STime operator-(const Duration& duration) const noexcept
    {
        STime result{ *this };

        switch (duration.sign()) {
        case Duration::Sign::NEGATIVE:
            // Double negative = positive
            result.positiveDisplace(duration);
            break;

        default:
            result.displace(duration);
        }

        return result;
    }

    STime& operator+=(const Duration& duration) noexcept
    {
        this->displace(duration);

        return *this;
    }

    STime& operator-=(const Duration& duration) noexcept
    {
        switch (duration.sign()) {
        case Duration::Sign::NEGATIVE:
            // Double negative = positive
            this->positiveDisplace(duration);
            break;

        default:
            this->displace(duration);
        }

        return *this;
    }

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
        time.reserve((size_t)11ULL);
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
        return this->timeStr(format, Layout::H_M_S);
    }

    /* Returns time string with provided layout */
    std::string timeStr(Layout layout) const noexcept
    {
        return this->timeStr(Format::MILITARY, layout);
    }

    /* Returns time string */
    std::string timeStr() const noexcept
    {
        return this->timeStr(Format::MILITARY, Layout::H_M_S);
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
        }

        return total;
    }

    /* Returns total number of seconds from this time until provided time */
    size_t secondsUntil(const STime& s_time) const noexcept
    {
        size_t totalSeconds{ 0 };

        if (this == &s_time || *this == s_time)
            return totalSeconds;

        STime temp{ *this };

        // Accum. seconds
        totalSeconds += (
            temp.getInterval(SECOND_INDEX)->untilPosition(*s_time.getInterval(SECOND_INDEX))
        );
        temp.getInterval(SECOND_INDEX)->increment(
            temp.getInterval(SECOND_INDEX)->untilPosition(*s_time.getInterval(SECOND_INDEX))
        );

        // Accum. minutes
        totalSeconds += (
            ((size_t)temp.getInterval(MINUTE_INDEX)->untilPosition(*s_time.getInterval(MINUTE_INDEX)) * (size_t)60ULL)
        );
        temp.getInterval(MINUTE_INDEX)->increment(
            temp.getInterval(MINUTE_INDEX)->untilPosition(*s_time.getInterval(MINUTE_INDEX))
        );

        // Accum. hours
        totalSeconds += (
            ((size_t)temp.getInterval(HOUR_INDEX)->untilPosition(*s_time.getInterval(HOUR_INDEX)) * (size_t)3'600ULL)
        );

        return totalSeconds;
    }

    /* Returns absolute total number of seconds from this time until provided time */
    size_t absSecondsUntil(const STime& s_time) const noexcept
    {
        if (this->isBefore(s_time))
            return this->secondsUntil(s_time);
        else
            return s_time.secondsUntil(*this);
    }

    /* Returns duration between this time and provided time */
    Duration until(const STime& s_time) const noexcept
    {
        if (this == &s_time || *this == s_time)
            return Duration{};

        Duration newDur{ Duration::Sign::POSITIVE };

        newDur.getSecond().largeDisplace(
            Duration::Sign::POSITIVE,
            this->secondsUntil(s_time)
        );

        return newDur;
    }

    /* Displace time using provided duration */
    void displace(const Duration& duration) noexcept
    {
        switch (duration.sign()) {
        case Duration::Sign::NEGATIVE:
            return this->negativeDisplace(duration);
        default:
            return this->positiveDisplace(duration);
        }
    }


private:
    static const uint8_t HOUR_INDEX{ 0 };
    static const uint8_t MINUTE_INDEX{ 1 };
    static const uint8_t SECOND_INDEX{ 2 };

    size_t timeUnitEnumToIndex(TimeUnit time_unit) noexcept
    {
        switch (time_unit) {
        case TimeUnit::HOUR:
            return HOUR_INDEX;
        case TimeUnit::MINUTE:
            return MINUTE_INDEX;
        case TimeUnit::SECOND:
            return SECOND_INDEX;
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

    void positiveDisplace(const Duration& duration) noexcept
    {
        return this->getInterval(SECOND_INDEX)->largeDisplace(
            Duration::Sign::POSITIVE,
            duration.convertedTo(Duration::TimeUnit::SECOND)
        );
    }

    void negativeDisplace(const Duration& duration) noexcept
    {
        return this->getInterval(SECOND_INDEX)->largeDisplace(
            Duration::Sign::NEGATIVE,
            duration.convertedTo(Duration::TimeUnit::SECOND)
        );
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_STANDARD_TIME_SEQUENCE_OBJ_H_
