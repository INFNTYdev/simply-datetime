
#ifndef SIMPLYDTLIB_L_DATETIME_V_TIME_SEQUENCE_H_
#define SIMPLYDTLIB_L_DATETIME_V_TIME_SEQUENCE_H_



#include<chrono>
#include<cmath>

#include"simplydt/datetime/sequence/dt_sequence.hpp"
#include"simplydt/datetime/time/unit/dt_hour.hpp"
#include"simplydt/datetime/time/unit/dt_minute.hpp"
#include"simplydt/datetime/time/unit/dt_second.hpp"
#include"simplydt/duration/comp/virtual/dt_vduration.hpp"
#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"


/* Standard time (HH:MM:SS) */
class VTime : public DatetimeSequence<Hour, Minute, Second> {

public:
    /* Datetime time unit */
    using TimeUnit = DatetimeSequence<Hour, Minute, Second>::TimeUnit;
    /* Datetime type */
    using DatetimeType = DatetimeSequence<Hour, Minute, Second>::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    /* 12-hr clock time phase */
    using Phase = Hour::Phase;
    /* Julian Day Number (JDN) */
    using JDN = double;

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

    VTime(const TimePoint& sys_clock) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0Ui16),
            Minute((uint16_t)0Ui16),
            Second((uint16_t)0Ui16)
        }
    {
        this->populateIntervalPointers();

        this->assumeTimePoint(sys_clock);
    }

    VTime(uint16_t hour, uint16_t minute, uint16_t second) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second(second)
        }
    {
        this->populateIntervalPointers();
    }

    VTime(uint16_t hour, uint16_t minute) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute(minute),
            Second((uint16_t)0Ui16)
        }
    {
        this->populateIntervalPointers();
    }

    explicit VTime(uint16_t hour) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(hour),
            Minute((uint16_t)0Ui16),
            Second((uint16_t)0Ui16)
        }
    {
        this->populateIntervalPointers();
    }

    explicit VTime(const JDN& jdn) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0Ui16),
            Minute((uint16_t)0Ui16),
            Second((uint16_t)0Ui16)
        }
    {
        this->populateIntervalPointers();

        this->assumeJDN(jdn);
    }

    VTime(const VTime& v_time) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour(v_time.hour()),
            Minute(v_time.minute()),
            Second(v_time.second())
        }
    {
        this->populateIntervalPointers();
    }

    VTime(VTime&& v_time) noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            static_cast<DatetimeSequence<Hour, Minute, Second>&&>(v_time)
        }
    {
        this->populateIntervalPointers();
    }
    
    VTime() noexcept
        : DatetimeSequence<Hour, Minute, Second>{
            DatetimeType::TIME_DATETIME,
            Hour((uint16_t)0Ui16),
            Minute((uint16_t)0Ui16),
            Second((uint16_t)0Ui16)
        }
    {
        this->populateIntervalPointers();
    }

    virtual ~VTime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VTime& v_time) noexcept
    {
        os << v_time.timeStr();

        return os;
    }

    VTime& operator=(const VTime& v_time) noexcept
    {
        if (this == &v_time || *this == v_time)
            return *this;

        this->getInterval(HOUR_INDEX)->setPosition(v_time.hour());
        this->getInterval(MINUTE_INDEX)->setPosition(v_time.minute());
        this->getInterval(SECOND_INDEX)->setPosition(v_time.second());

        return *this;
    }

    VTime& operator=(VTime&& v_time) noexcept
    {
        if (this == &v_time)
            return *this;
        
        DatetimeSequence<Hour, Minute, Second>::operator=(
            static_cast<DatetimeSequence<Hour, Minute, Second>&&>(v_time)
        );

        this->populateIntervalPointers();

        return *this;
    }

    VTime& operator=(const TimePoint& sys_clock) noexcept
    {
        std::time_t timeT{ std::chrono::system_clock::to_time_t(sys_clock) };
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

    bool operator==(const VTime& v_time) const noexcept
    {
        if (this == &v_time)
            return true;
        
        return DatetimeSequence<Hour, Minute, Second>::operator==(v_time);
    }

    bool operator==(const TimePoint& sys_clock) const noexcept
    {
        uint16_t tpHour{ 0 };
        uint16_t tpMinute{ 0 };
        uint16_t tpSecond{ 0 };

        this->interpretTimePointTime(sys_clock, tpHour, tpMinute, tpSecond);

        if (this->hour() != tpHour)
            return false;
        
        if (this->minute() != tpMinute)
            return false;
        
        if (this->second() != tpSecond)
            return false;
        
        return true;
    }

    bool operator<(const VTime& v_time) const noexcept
    {
        if (this == &v_time)
            return false;

        return DatetimeSequence<Hour, Minute, Second>::operator<(v_time);
    }

    bool operator<(const TimePoint& sys_clock) const noexcept
    {
        uint16_t tpHour{ 0 };
        uint16_t tpMinute{ 0 };
        uint16_t tpSecond{ 0 };

        this->interpretTimePointTime(sys_clock, tpHour, tpMinute, tpSecond);

        if (this->hour() > tpHour)
            return false;
        else if (this->hour() < tpHour)
            return true;
        
        if (this->minute() > tpMinute)
            return false;
        else if (this->minute() < tpMinute)
            return true;
        
        if (this->second() >= tpSecond)
            return false;
        
        return true;
    }

    bool operator>(const VTime& v_time) const noexcept
    {
        if (this == &v_time)
            return false;

        return DatetimeSequence<Hour, Minute, Second>::operator>(v_time);
    }

    bool operator>(const TimePoint& sys_clock) const noexcept
    {
        uint16_t tpHour{ 0 };
        uint16_t tpMinute{ 0 };
        uint16_t tpSecond{ 0 };

        this->interpretTimePointTime(sys_clock, tpHour, tpMinute, tpSecond);

        if (this->hour() < tpHour)
            return false;
        else if (this->hour() > tpHour)
            return true;
        
        if (this->minute() < tpMinute)
            return false;
        else if (this->minute() > tpMinute)
            return true;
        
        if (this->second() <= tpSecond)
            return false;
        
        return true;
    }

    bool operator<=(const VTime& v_time) const noexcept
    {
        return DatetimeSequence<Hour, Minute, Second>::operator<=(v_time);
    }

    bool operator<=(const TimePoint& sys_clock) const noexcept
    {
        return (this->operator<(sys_clock) || this->operator==(sys_clock));
    }

    bool operator>=(const VTime& v_time) const noexcept
    {
        return DatetimeSequence<Hour, Minute, Second>::operator>=(v_time);
    }

    bool operator>=(const TimePoint& sys_clock) const noexcept
    {
        return (this->operator>(sys_clock) || this->operator==(sys_clock));
    }

    VTime operator+(const VDuration& v_duration) const noexcept
    {
        VTime result{ *this };

        result.displace(v_duration);

        return result;
    }

    VTime operator-(const VDuration& v_duration) const noexcept
    {
        VTime result{ *this };

        switch (v_duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            result.positiveDisplace(v_duration);
            break;

        default:
            result.displace(v_duration);
        }

        return result;
    }

    VTime& operator+=(const VDuration& v_duration) noexcept
    {
        this->displace(v_duration);

        return *this;
    }

    VTime& operator-=(const VDuration& v_duration) noexcept
    {
        switch (v_duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            // Double negative = positive
            this->positiveDisplace(v_duration);
            break;

        default:
            this->displace(v_duration);
        }

        return *this;
    }

    /* Returns true if time is equal to start of day (midnight) */
    bool isZero() const noexcept
    {
        return (
            this->hourRef().isAtStart()
            && this->minuteRef().isAtStart()
            && this->secondRef().isAtStart()
        );
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
        return this->hourRef().getPhase();
    }

    /* Returns time phase literal */
    std::string phaseStr() const noexcept
    {
        return this->hourRef().getPhaseStr();
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
            time += (this->hourRef().toDoubleDigitStandardStr() + delimiter);
            break;
        default:
            time += (this->hourRef().toDoubleDigitStr() + delimiter);
            break;
        }

        time += this->minuteRef().toDoubleDigitStr();

        switch (layout) {
        case Layout::H_M_S:
            time += (delimiter + this->secondRef().toDoubleDigitStr());
            break;
        case Layout::H_M_S_P:
            time += (delimiter + this->secondRef().toDoubleDigitStr());
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
    const Hour& hourRef() const noexcept
    {
        return *(this->m_hour_ptr);
    }

    /* Returns minute in time */
    const Minute& minuteRef() const noexcept
    {
        return *(this->m_minute_ptr);
    }

    /* Returns second in time */
    const Second& secondRef() const noexcept
    {
        return *(this->m_second_ptr);
    }

    /* Returns hour in time */
    Hour* getHour() const noexcept
    {
        return this->m_hour_ptr;
    }

    /* Returns minute in time */
    Minute* getMinute() const noexcept
    {
        return m_minute_ptr;
    }

    /* Returns second in time */
    Second* getSecond() const noexcept
    {
        return this->m_second_ptr;
    }

    /* Returns time as fractional Julian Day Number (JDN) */
    JDN toJulianDayNumber() const noexcept
    {
        // Calculate time as a fraction of a day
        double timeJDN{
            ((this->hour() / (double)24.)
            + (this->minute() / (double)1'440.)
            + (this->second() / (double)86'400.))
        };

        // Adjust for JDN system starting at noon
        if (this->hour() >= (uint16_t)12Ui16)
            timeJDN -= (double).5;
        else if (this->hour() < (uint16_t)12Ui16)
            timeJDN += (double).5;

        return timeJDN;
    }

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
            total += ((uint32_t)this->hour() * (uint32_t)60Ui32);
            total += (uint32_t)this->minute();
            break;

        // Second conversion
        case TimeUnit::SECOND:
            total += ((uint32_t)this->hour() * (uint32_t)3'600Ui32);
            total += ((uint32_t)this->minute() * (uint32_t)60Ui32);
            total += (uint32_t)this->second();
            break;

        // Millisecond conversion
        case TimeUnit::MILLISECOND:
            total += ((uint32_t)this->hour() * (uint32_t)3'600'000Ui32);
            total += ((uint32_t)this->minute() * (uint32_t)60'000Ui32);
            total += ((uint32_t)this->second() * (uint32_t)1'000Ui32);
        }

        return total;
    }

    /* Returns total number of hours from this time until provided time */
    uint8_t hoursUntil(const VTime& v_time) const noexcept
    {
        if (this == &v_time || this->hour() == v_time.hour())
            return (uint8_t)0Ui8;

        double thisHour{ this->toJulianDayNumber() * (double)24. };
        double paramHour{ v_time.toJulianDayNumber() * (double)24. };
        double difference{ .0 };

        if (this->isAfter(v_time))
            difference = std::floor(thisHour - paramHour);
        else
            difference = std::floor(paramHour - thisHour);
        
        if (difference < (double).0)
            difference += (double)24.;
        
        return static_cast<uint8_t>(difference);
    }

    /* Returns total number of minutes from this time until provided time */
    uint16_t minutesUntil(const VTime& v_time) const noexcept
    {
        if (this == &v_time || *this == v_time)
            return (uint16_t)0Ui16;

        double thisMinutes{ this->toJulianDayNumber() * (double)1'440. };
        double paramMinutes{ v_time.toJulianDayNumber() * (double)1'440. };
        double difference{ .0 };

        if (this->isAfter(v_time))
            difference = std::floor(thisMinutes - paramMinutes);
        else
            difference = std::floor(paramMinutes - thisMinutes);
        
        if (difference < (double).0)
            difference += (double)1'440.;
        
        return static_cast<uint16_t>(difference);
    }

    /* Returns total number of seconds from this time until provided time */
    uint32_t secondsUntil(const VTime& v_time) const noexcept
    {
        if (this == &v_time || *this == v_time)
            return (uint32_t)0Ui32;

        double thisSeconds{ this->toJulianDayNumber() * (double)86'400. };
        double paramSeconds{ v_time.toJulianDayNumber() * (double)86'400. };
        double difference{ .0 };

        if (this->isAfter(v_time))
            difference = std::floor(thisSeconds - paramSeconds);
        else
            difference = std::floor(paramSeconds - thisSeconds);
        
        if (difference < (double).0)
            difference += (double)86'400.;
        
        return static_cast<uint32_t>(difference);
    }

    /* Returns duration between this time and provided time */
    VDuration until(const VTime& v_time) const noexcept
    {
        if (this == &v_time || *this == v_time)
            return VDuration{};

        VDuration newDur{ VDuration::Sign::POSITIVE };

        newDur.getSecond()->largeDisplace(
            VDuration::Sign::POSITIVE,
            this->secondsUntil(v_time)
        );

        return newDur;
    }

    /* Increase time by provided amount of seconds */
    void increase(uint32_t secs) noexcept;// <--- Incomplete

    /* Increase time interval by provided amount of units */
    void increase(TimeUnit interval, uint32_t units) noexcept;// <--- Incomplete

    /* Decrease time by provided amount of seconds */
    void decrease(uint32_t secs) noexcept;// <--- Incomplete

    /* Decrease time interval by provided amount of units */
    void decrease(TimeUnit interval, uint32_t units) noexcept;// <--- Incomplete

    /* Displace time using provided duration */
    void displace(const VDuration& v_duration) noexcept
    {
        switch (v_duration.sign()) {
        case VDuration::Sign::NEGATIVE:
            return this->negativeDisplace(v_duration);
        
        default:
            return this->positiveDisplace(v_duration);
        }
    }

    /* Reset time to start of day (midnight) */
    void reset() noexcept
    {
        if (this->isZero())
            return;

        this->getInterval(HOUR_INDEX)->reset();
        this->getInterval(MINUTE_INDEX)->reset();
        this->getInterval(SECOND_INDEX)->reset();
    }


private:
    static const uint8_t HOUR_INDEX{ 0 };
    static const uint8_t MINUTE_INDEX{ 1 };
    static const uint8_t SECOND_INDEX{ 2 };

    Hour* m_hour_ptr;
    Minute* m_minute_ptr;
    Second* m_second_ptr;

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

    void interpretTimePointTime(const TimePoint& time_point,
        uint16_t& hour, uint16_t& minute, uint16_t& second) const noexcept
    {
        // DEBUG: Somehow tm_hour is returning 19 on epoch hour???
        // (new control flow acknowledges)
        if (time_point == TimePoint{}) {// If provided time point is equal to epoch
            hour = (uint16_t)23Ui16;
            minute = (uint16_t)59Ui16;
            second = (uint16_t)59Ui16;

            return;
        }

        std::time_t timeT{ std::chrono::system_clock::to_time_t(time_point) };
        std::tm* tm_ptr{ std::localtime(&timeT) };
        
        // Retrieve time from time point
        hour = static_cast<uint16_t>(tm_ptr->tm_hour);
        minute = static_cast<uint16_t>(tm_ptr->tm_min);
        second = static_cast<uint16_t>(tm_ptr->tm_sec);
    }

    void interpretJDNTime(JDN jdn,
        uint16_t& hr, uint16_t& min, uint16_t& sec) const noexcept
    {
        // Standard JDN implementation (fraction only)
        // JDN Zero time: 0.5 (00h:00m)
        // JDN noon time: 0.0 (12h:00m)

        // Fraction portion of JDN only
        if (jdn >= (double)1.)
            jdn -= (std::floor(jdn));

        if (jdn < (JDN)0.5)
            jdn += (JDN)0.5;
        else if (jdn >= (JDN)0.5)
            jdn -= (JDN)0.5;

        double totalSeconds{ (jdn * (double)86'400.) };

        if (totalSeconds) {
            hr = static_cast<uint16_t>((totalSeconds / (double)3'600.));
            totalSeconds -= ((double)hr * (double)3'600.);
        }

        if (totalSeconds) {
            min = static_cast<uint16_t>((totalSeconds / (double)60.));
            totalSeconds -= ((double)min * (double)60.);
        }

        if (totalSeconds)
            sec = static_cast<uint16_t>(std::round(totalSeconds));

        // Adjustments for rounding issues
        if (sec == (uint16_t)60Ui16) {
            sec = (uint16_t)0Ui16;
            min += (uint16_t)1Ui16;
        }

        if (min == (uint16_t)60Ui16) {
            min = (uint16_t)0Ui16;
            hr += (uint16_t)1Ui16;
        }

        if (hr == (uint16_t)24Ui16)
            hr = (uint16_t)0Ui16;
    }

    void assumeTimePoint(const TimePoint& time_point) noexcept
    {
        uint16_t tmHour{ 0 };
        uint16_t tmMinute{ 0 };
        uint16_t tmSecond{ 0 };

        this->interpretTimePointTime(time_point, tmHour, tmMinute, tmSecond);

        // Set time interval values
        this->getInterval(HOUR_INDEX)->setPosition(tmHour);
        this->getInterval(MINUTE_INDEX)->setPosition(tmMinute);
        this->getInterval(SECOND_INDEX)->setPosition(tmSecond);
    }

    void assumeJDN(const JDN& jdn) noexcept
    {
        uint16_t tmHour{ 0 };
        uint16_t tmMinute{ 0 };
        uint16_t tmSecond{ 0 };

        this->interpretJDNTime(jdn, tmHour, tmMinute, tmSecond);

        // Set time interval values
        this->getInterval(HOUR_INDEX)->setPosition(tmHour);
        this->getInterval(MINUTE_INDEX)->setPosition(tmMinute);
        this->getInterval(SECOND_INDEX)->setPosition(tmSecond);
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

    void positiveDisplace(const VDuration& v_duration) noexcept
    {
        return this->getInterval(SECOND_INDEX)->largeDisplace(
            VDuration::Sign::POSITIVE,
            v_duration.convertedTo(VDuration::TimeUnit::SECOND)
        );
    }

    void negativeDisplace(const VDuration& v_duration) noexcept
    {
        return this->getInterval(SECOND_INDEX)->largeDisplace(
            VDuration::Sign::NEGATIVE,
            v_duration.convertedTo(VDuration::TimeUnit::SECOND)
        );
    }

    void populateIntervalPointers() noexcept
    {
        this->m_hour_ptr = this->retrieveHour();
        this->m_minute_ptr = this->retrieveMinute();
        this->m_second_ptr = this->retrieveSecond();
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_V_TIME_SEQUENCE_H_
