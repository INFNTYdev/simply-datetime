
#ifndef SIMPLYDTLIB_L_DATETIME_V_TIME_SEQUENCE_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_V_TIME_SEQUENCE_OBJ_H_



#include<chrono>
#include<cmath>

#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/datetime/time/unit/dt_millisecond.hpp"
#include"simplydt/duration/comp/dt_vduration.hpp"
//#include"simplydt/datetime/time/comp/dt_vtime.hpp"


/* Extended time ( HH:MM:SS:MS ) */
class VTimeEx : public DatetimeSequence<Hour, Minute, Second, Millisecond> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Hour, Minute, Second, Millisecond>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Hour, Minute, Second, Millisecond>::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    /* 12-hr clock time phase */
    using Phase = Hour::Phase;
    /* Julian Day Number (JDN) */
    using JDN = double;

    /* Time format */
    enum Format {
        MILITARY,// Military format (24-hour clock)
        STANDARD,// Standard format (12-hour clock)
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

    VTimeEx(TimePoint chrono) noexcept
        : DatetimeSequence<Hour, Minute, Second, Millisecond>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0Ui16),
            Minute((uint16_t)0Ui16),
            Second((uint16_t)0Ui16),
            Millisecond((uint16_t)0Ui16)
        }
    {
        uint16_t tmHour{ 23 };
        uint16_t tmMinute{ 59 };
        uint16_t tmSecond{ 59 };

        // DEBUG: Somehow tm_hour is returning 19 on epoch hour?
        // New control flow acknowledges
        if (chrono != TimePoint{}) {// If provided time point is not equal to epoch
            std::time_t timeT{ std::chrono::system_clock::to_time_t(chrono) };
            std::tm* tm_ptr{ std::localtime(&timeT) };

            // Retrieve time from time point
            tmHour = static_cast<uint16_t>(tm_ptr->tm_hour);
            tmMinute = static_cast<uint16_t>(tm_ptr->tm_min);
            tmSecond = static_cast<uint16_t>(tm_ptr->tm_sec);
        }

        // Set time interval values
        this->getInterval(HOUR_INDEX)->setPosition(tmHour);
        this->getInterval(MINUTE_INDEX)->setPosition(tmMinute);
        this->getInterval(SECOND_INDEX)->setPosition(tmSecond);
    }

    VTimeEx(uint16_t hour, uint16_t minute, uint16_t second, uint16_t ms) noexcept
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

    VTimeEx(uint16_t hour, uint16_t minute, uint16_t second) noexcept
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

    VTimeEx(uint16_t hour, uint16_t minute) noexcept
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

    explicit VTimeEx(uint16_t hour) noexcept
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

    explicit VTimeEx(const JDN& jdn) noexcept;//    <--- INCOMPLETE!!!

    // VTimeEx(const VTime& v_time) noexcept
    //     : DatetimeSequence<Hour, Minute, Second, Millisecond>{//    <--- INCOMPLETE!!!
    //         DatetimeType::TIME_DATETIME,
    //         Hour(v_time.getHour()),
    //         Minute(v_time.getMinute()),
    //         Second(v_time.getSecond()),
    //         Millisecond((uint16_t)0U)
    //     }
    // {
    //     //
    // }

    VTimeEx(const VTimeEx& vtime_ex) noexcept;//    <--- INCOMPLETE!!!

    VTimeEx(VTimeEx&& vtime_ex) noexcept;//    <--- INCOMPLETE!!!

    VTimeEx() noexcept
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

    virtual ~VTimeEx() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VTimeEx& vtime_ex) noexcept
    {
        os << vtime_ex.timeStr();

        return os;
    }

    VTimeEx& operator=(const VTimeEx& vtime_ex) noexcept;//    <--- INCOMPLETE!!!

    VTimeEx& operator=(VTimeEx&& vtime_ex) noexcept;//    <--- INCOMPLETE!!!

    // VTimeEx& operator=(const VTime& v_time) noexcept//    <--- INCOMPLETE!!!
    // {
    //     this->getInterval(HOUR_INDEX)->setPosition(v_time.hour());
    //     this->getInterval(MINUTE_INDEX)->setPosition(v_time.minute());
    //     this->getInterval(SECOND_INDEX)->setPosition(v_time.second());
    //     this->getInterval(MILLIS_INDEX)->setPosition((uint16_t)0U);

    //     return *this;
    // }

    VTimeEx& operator=(const TimePoint& chrono) noexcept//    <--- INCOMPLETE!!! (review this)
    {
        uint16_t tmHour{ 23 };
        uint16_t tmMinute{ 59 };
        uint16_t tmSecond{ 59 };

        // DEBUG: Somehow tm_hour is returning 19 on epoch hour?
        // If-statement below acknowledges
        if (chrono != TimePoint{}) {// If this is not equal to the epoch
            std::time_t timeT{ std::chrono::system_clock::to_time_t(chrono) };
            std::tm* tm_ptr{ std::localtime(&timeT) };

            // Retrieve time from time point
            tmHour = static_cast<uint16_t>(tm_ptr->tm_hour);
            tmMinute = static_cast<uint16_t>(tm_ptr->tm_min);
            tmSecond = static_cast<uint16_t>(tm_ptr->tm_sec);
        }

        // Set time interval values
        this->getInterval(HOUR_INDEX)->setPosition(tmHour);
        this->getInterval(MINUTE_INDEX)->setPosition(tmMinute);
        this->getInterval(SECOND_INDEX)->setPosition(tmSecond);

        return *this;
    }

    bool operator==(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    //bool operator==(const VTime& v_time) const noexcept;//    <--- INCOMPLETE!!!

    bool operator==(const TimePoint& sys_clock) const noexcept;//    <--- INCOMPLETE!!!

    bool operator<(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    //bool operator<(const VTime& v_time) const noexcept;//    <--- INCOMPLETE!!!

    bool operator<(const TimePoint& time_point) const noexcept;//    <--- INCOMPLETE!!!

    bool operator>(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    //bool operator>(const VTime& v_time) const noexcept;//    <--- INCOMPLETE!!!

    bool operator>(const TimePoint& time_point) const noexcept;//    <--- INCOMPLETE!!!

    bool operator<=(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    //bool operator<=(const VTime& v_time) const noexcept;//    <--- INCOMPLETE!!!

    bool operator<=(const TimePoint& time_point) const noexcept;//    <--- INCOMPLETE!!!

    bool operator>=(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    //bool operator>=(const VTime& v_time) const noexcept;//    <--- INCOMPLETE!!!

    bool operator>=(const TimePoint& time_point) const noexcept;//    <--- INCOMPLETE!!!

    VTimeEx operator+(const VDuration& v_duration) const noexcept
    {
        VTimeEx temp{ *this };

        temp.displace(v_duration);

        return temp;
    }

    VTimeEx operator-(const VDuration& duration) const noexcept
    {
        VTimeEx temp{ *this };

        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            temp.positiveDisplace(duration);
            break;

        default:
            temp.negativeDisplace(duration);
        }

        return temp;
    }

    VTimeEx& operator+=(const VDuration& duration) noexcept
    {
        this->displace(duration);

        return *this;
    }

    VTimeEx& operator-=(const VDuration& duration) noexcept
    {
        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            this->positiveDisplace(duration);
            break;

        default:
            this->negativeDisplace(duration);
        }

        return *this;
    }

    /* Returns true if time is equal to start of day (midnight) */
    bool isZero() const noexcept;//    <--- INCOMPLETE!!!

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

    const Hour& hourRef() const noexcept;//    <--- INCOMPLETE!!!

    const Minute& minuteRef() const noexcept;//    <--- INCOMPLETE!!!

    const Second& secondRef() const noexcept;//    <--- INCOMPLETE!!!

    const Millisecond& msRef() const noexcept;//    <--- INCOMPLETE!!!

    /* Returns hour in time */
    Hour* getHour() const noexcept//    <--- INCOMPLETE!!!
    {
        return this->m_hour_ptr;
    }

    /* Returns minute in time */
    Minute* getMinute() const noexcept//    <--- INCOMPLETE!!!
    {
        return m_minute_ptr;
    }

    /* Returns second in time */
    Second* getSecond() const noexcept//    <--- INCOMPLETE!!!
    {
        return this->m_second_ptr;
    }

    /* Returns millisend in time */
    Millisecond* getMs() const noexcept//    <--- INCOMPLETE!!!
    {
        return this->m_millisecond_ptr;
    }

    // /* Returns copy of full time as standard time */
    // STime toVTime() const noexcept//    <--- INCOMPLETE!!!
    // {
    //     return STime{ this->hour(), this->minute(), this->second() };
    // }

    /* Link time to date instance */
    bool linkDate(VDate& v_date) noexcept
    {
        return this->getHour()->linkPrecedingInterval(*v_date.getDay());
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

    /* Returns total number of hours from this time until provided time */
    uint32_t hoursUntil(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    /* Returns total number of minutes from this time until provided time */
    uint32_t minutesUntil(const VTimeEx& vtime_ex) const noexcept;//    <--- INCOMPLETE!!!

    /* Returns total number of seconds from this time until provided time */
    size_t secondsUntil(const VTimeEx& vtime_ex) const noexcept
    {
        size_t totalSeconds{ 0 };

        if (this == &vtime_ex || *this == vtime_ex)
            return totalSeconds;

        VTimeEx temp{ *this };

        // Accum. seconds
        totalSeconds += (
            temp.getInterval(SECOND_INDEX)->untilPosition(*vtime_ex.getInterval(SECOND_INDEX))
        );
        temp.getInterval(SECOND_INDEX)->increment(
            temp.getInterval(SECOND_INDEX)->untilPosition(*vtime_ex.getInterval(SECOND_INDEX))
        );

        // Accum. minutes
        totalSeconds += (
            ((size_t)temp.getInterval(MINUTE_INDEX)->untilPosition(*vtime_ex.getInterval(MINUTE_INDEX)) * (size_t)60ULL)
        );
        temp.getInterval(MINUTE_INDEX)->increment(
            temp.getInterval(MINUTE_INDEX)->untilPosition(*vtime_ex.getInterval(MINUTE_INDEX))
        );

        // Accum. hours
        totalSeconds += (
            ((size_t)temp.getInterval(HOUR_INDEX)->untilPosition(*vtime_ex.getInterval(HOUR_INDEX)) * (size_t)3'600ULL)
        );

        return totalSeconds;
    }

    /* Returns absolute total number of milliseconds from this time until provided time */
    size_t msUntil(const VTimeEx& time) const noexcept
    {
        size_t totalMs{ 0 };

        if (this == &time || *this == time)
            return totalMs;

        VTimeEx temp{ *this };

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
    VDuration until(const VTimeEx& time) const noexcept
    {
        if (this == &time || *this == time)
            return VDuration{};

        VDuration newDur{ VDuration::Sign::POSITIVE };

        newDur.getMs()->largeDisplace(
            VDuration::Sign::POSITIVE,
            this->msUntil(time)
        );

        return newDur;
    }

    /* Displace time using provided duration */
    void displace(const VDuration& duration) noexcept
    {
        switch (duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            return this->negativeDisplace(duration);
        
        default:
            return this->positiveDisplace(duration);
        }
    }


private:
    static const uint8_t HOUR_INDEX{ 0 };
    static const uint8_t MINUTE_INDEX{ 1 };
    static const uint8_t SECOND_INDEX{ 2 };
    static const uint8_t MILLIS_INDEX{ 3 };

    Hour* m_hour_ptr;
    Minute* m_minute_ptr;
    Second* m_second_ptr;
    Millisecond* m_millisecond_ptr;

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

    void interpretTimePointTime(const TimePoint& time_point,//    <--- INCOMPLETE!!!
        uint16_t& year, uint16_t& month, uint16_t& day) const noexcept
    {
        //
    }

    void interpretJDNTime(const JDN& jdn,//    <--- INCOMPLETE!!!
        uint16_t& hr, uint16_t& min, uint16_t& sec, uint16_t& ms) const noexcept
    {
        // Standard JDN implementation
        // JDN Zero time: 0.0 (00h:00m)
        // JDN noon time: 0.5 (12h:00m)

        //
    }

    void assumeTimePoint(const TimePoint& time_point) noexcept;//    <--- INCOMPLETE!!!

    void assumeJDN(const JDN& jdn) noexcept;//    <--- INCOMPLETE!!!

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
        return this->getInterval(MILLIS_INDEX)->largeDisplace(
            VDuration::Sign::POSITIVE,
            duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
        );
    }

    void negativeDisplace(const VDuration& duration) noexcept
    {
        return this->getInterval(MILLIS_INDEX)->largeDisplace(
            VDuration::Sign::NEGATIVE,
            duration.convertedTo(VDuration::TimeUnit::MILLISECOND)
        );
    }

    void populateIntervalPointers() noexcept
    {
        this->m_hour_ptr = this->retrieveHour();
        this->m_minute_ptr = this->retrieveMinute();
        this->m_second_ptr = this->retrieveSecond();
        this->m_millisecond_ptr = this->retrieveMillisecond();
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_V_TIME_SEQUENCE_OBJ_H_
