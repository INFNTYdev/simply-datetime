
#ifndef SIMPLYDTLIB_L_DATETIME_V_DATETIME_EXTENDED_H_
#define SIMPLYDTLIB_L_DATETIME_V_DATETIME_EXTENDED_H_



#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"
#include"simplydt/datetime/time/comp/virtual/dt_vtime_ex.hpp"


/* Extended datetime (YYYY-mm-dd-HH-MM-SS-MS) */
class VDatetimeEx {

public:
    /* Datetime time unit */
    using Unit = VDate::TimeUnit;
    /* Datetime type */
    using Type = VDate::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
    /* Julian Day Number (JDN) */
    using JDN = double;

    /* Datetime layout */
    enum Layout {
        DATE_TIME,// date - time
        TIME_DATE,// time - date
    };

    VDatetimeEx(const TimePoint& sys_clock) noexcept
        : m_date{ sys_clock },
        m_time{ sys_clock }
    {
        this->linkDatetime();
    }

    VDatetimeEx(const VDate& v_date, const VTimeEx& vtime_ex) noexcept
        : m_date{ v_date },
        m_time{ vtime_ex }
    {
        this->linkDatetime();
    }

    VDatetimeEx(VDate&& v_date, VTimeEx&& vtime_ex) noexcept
        : m_date{ std::forward<VDate>(v_date) },
        m_time{ std::forward<VTimeEx>(vtime_ex) }
    {
        this->linkDatetime();
    }

    VDatetimeEx(const VDate& v_date, VTimeEx&& vtime_ex) noexcept
        : m_date{ v_date },
        m_time{ std::forward<VTimeEx>(vtime_ex) }
    {
        this->linkDatetime();
    }

    VDatetimeEx(VDate&& v_date, const VTimeEx& vtime_ex) noexcept
        : m_date{ std::forward<VDate>(v_date) },
        m_time{ vtime_ex }
    {
        this->linkDatetime();
    }

    VDatetimeEx(const VDate& v_date) noexcept
        : m_date{ v_date },
        m_time{}
    {
        this->linkDatetime();
    }

    VDatetimeEx(VDate&& v_date) noexcept
        : m_date{ std::forward<VDate>(v_date) },
        m_time{}
    {
        this->linkDatetime();
    }

    VDatetimeEx(const VDatetimeEx& vdatetime_ex) noexcept
        : m_date{ vdatetime_ex.m_date },
        m_time{ vdatetime_ex.m_time }
    {
        this->linkDatetime();
    }

    VDatetimeEx(VDatetimeEx&& vdatetime_ex) noexcept
        : m_date{ std::move(vdatetime_ex.m_date) },
        m_time{ std::move(vdatetime_ex.m_time) }
    {
        //
    }

    VDatetimeEx(const VDatetime& v_datetime) noexcept;//   <--- Complete VDatetime first

    VDatetimeEx(VDatetime&& v_datetime) noexcept;//   <--- Complete VDatetime first

    VDatetimeEx() noexcept
        : m_date{},
        m_time{}
    {
        this->linkDatetime();
    }

    ~VDatetimeEx() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const VDatetimeEx& vdatetime_ex) noexcept
    {
        os << vdatetime_ex.datetimeStr();

        return os;
    }

    VDatetimeEx& operator=(const VDatetimeEx& vdatetime_ex) noexcept
    {
        if (this == &vdatetime_ex)
            return *this;
        
        this->m_date = vdatetime_ex.m_date;
        this->m_time = vdatetime_ex.m_time;

        this->linkDatetime();

        return *this;
    }

    VDatetimeEx& operator=(VDatetimeEx&& vdatetime_ex) noexcept
    {
        if (this == &vdatetime_ex)
            return *this;
        
        this->m_date = std::move(vdatetime_ex.m_date);
        this->m_time = std::move(vdatetime_ex.m_time);

        return *this;
    }

    VDatetimeEx& operator=(const VDatetime& v_datetime) noexcept;//   <--- Complete VDatetime first

    VDatetimeEx& operator=(VDatetime&& v_datetime) noexcept;//   <--- Complete VDatetime first

    VDatetimeEx& operator=(const TimePoint& sys_clock) noexcept
    {
        this->m_date = sys_clock;
        this->m_time = sys_clock;

        return *this;
    }

    bool operator==(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        if (this == &vdatetime_ex)
            return true;
        
        if (this->m_date != vdatetime_ex.m_date)
            return false;
        
        if (this->m_time != vdatetime_ex.m_time)
            return false;

        return true;
    }

    bool operator==(const VDatetime& v_datetime) const noexcept;//   <--- Complete VDatetime first

    bool operator<(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return this->isBefore(vdatetime_ex);
    }

    bool operator>(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return this->isAfter(vdatetime_ex);
    }

    bool operator<=(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return (this->isBefore(vdatetime_ex) || this->operator==(vdatetime_ex));
    }

    bool operator>=(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return (this->isAfter(vdatetime_ex) || this->operator==(vdatetime_ex));
    }

    VDatetimeEx operator+(const VDuration& duration) const noexcept
    {
        VDatetimeEx result{ *this };

        result.displace(duration);

        return result;
    }

    VDatetimeEx operator-(const VDuration& duration) const noexcept
    {
        VDatetimeEx result{ *this };

        (*result.getTime()) -= duration;

        return result;
    }

    VDatetimeEx& operator+=(const VDuration& duration) noexcept
    {
        this->m_time += duration;

        return *this;
    }

    VDatetimeEx& operator-=(const VDuration& duration) noexcept
    {
        this->m_time -= duration;

        return *this;
    }

    /* Returns datetime year */
    uint16_t year() const noexcept
    {
        return this->m_date.year();
    }

    /* Returns datetime month */
    uint16_t month() const noexcept
    {
        return this->m_date.month();
    }

    /* Returns datetime day */
    uint16_t day() const noexcept
    {
        return this->m_date.day();
    }

    /* Returns datetime hour */
    uint16_t hour() const noexcept
    {
        return this->m_time.hour();
    }

    /* Returns datetime minute */
    uint16_t minute() const noexcept
    {
        return this->m_time.minute();
    }

    /* Returns datetime second */
    uint16_t second() const noexcept
    {
        return this->m_time.second();
    }

    /* Returns datetime millisecond */
    uint16_t millisecond() const noexcept
    {
        return this->m_time.millisecond();
    }

    /* Datetime date object */
    const VDate& v_date() const noexcept
    {
        return this->m_date;
    }

    /* Datetime time object */
    const VTimeEx& vtime_ex() const noexcept
    {
        return this->m_time;
    }

    /* Returns datetime hour of day phase */
    Hour::Phase hourPhase() const noexcept
    {
        return this->m_time.phase();
    }

    /* Returns datetime hour of day phase literal */
    std::string hourPhaseStr() const noexcept
    {
        return this->m_time.phaseStr();
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Layout layout, VDate::Format date_format, VDate::Layout date_layout,
        VTimeEx::Format time_format, VTimeEx::Layout time_layout) const noexcept
    {
        std::string datetimeString;
        datetimeString.reserve((size_t)30ULL);
        datetimeString = "";

        switch (layout) {
        case Layout::TIME_DATE:
            datetimeString += (this->m_time.timeStr(time_format, time_layout) + ' ');
            datetimeString += this->m_date.dateStr(date_format, date_layout);

            return datetimeString;

        default:
            datetimeString += (this->m_date.dateStr(date_format, date_layout) + ' ');
            datetimeString += this->m_time.timeStr(time_format, time_layout);

            return datetimeString;
        }
    }
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VDate::Layout date_layout,
        VTimeEx::Format time_format, VTimeEx::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            date_layout,// Date layout
            time_format,// Time format
            time_layout// Time layout
        );
    }
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VDate::Layout date_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            date_layout,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTimeEx::Format time_format, VTimeEx::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            VDate::Format::RECORD,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            time_format,// Time format
            time_layout// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format, VTimeEx::Format time_format) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            time_format,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Layout date_layout, VTimeEx::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            VDate::Format::RECORD,// Date format
            date_layout,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            time_layout// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Format date_format) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VDate::Layout date_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            VDate::Format::RECORD,// Date format
            date_layout,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTimeEx::Format time_format) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            VDate::Format::RECORD,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            time_format,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(VTimeEx::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            VDate::Format::RECORD,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            time_layout// Time layout
        );
    }
    
    /* Returns datetime string in provided layout */
    std::string datetimeStr(Layout layout) const noexcept
    {
        return this->datetimeStr(
            layout,// Datetime object layout
            VDate::Format::RECORD,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string */
    std::string datetimeStr() const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            VDate::Format::RECORD,// Date format
            VDate::Layout::M_D_YYYY,// Date layout
            VTimeEx::Format::MILITARY,// Time format
            VTimeEx::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime day-of-week literal */
    const char* dayOfWeek() const noexcept
    {
        return this->m_date.dayOfWeek();
    }

    /* Returns datetime month literal */
    const char* monthTitle() const noexcept
    {
        return this->m_date.monthTitle();
    }

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return false;
        
        if (this->m_date.isAfter(vdatetime_ex.m_date))
            return false;
        
        if (this->m_time.isAfter(vdatetime_ex.m_time))
            return false;

        return true;
    }

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const VDate& v_date) const noexcept
    {
        if (&this->m_date == &v_date || this->m_date == v_date)
            return false;
        
        if (this->m_date.isAfter(v_date))
            return false;

        return true;
    }

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return false;
        
        if (this->m_date.isBefore(vdatetime_ex.m_date))
            return false;
        
        if (this->m_time.isBefore(vdatetime_ex.m_time))
            return false;

        return true;
    }

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const VDate& v_date) const noexcept
    {
        if (&this->m_date == &v_date || this->m_date == v_date)
            return false;
        
        if (this->m_date.isBefore(v_date))
            return false;

        return true;
    }

    /* Returns pointer to datetime date */
    VDate* getDate() noexcept
    {
        return &this->m_date;
    }

    /* Returns pointer to datetime time */
    VTimeEx* getTime() noexcept
    {
        return &this->m_time;
    }

    /* Returns standard datetime copy of this datetime */
    VDatetime toSDatetime() const noexcept
    {
        return VDatetime{
            this->m_date,
            VTime(
                this->hour(),
                this->minute(),
                this->second()
            )
        };
    }

    /* Returns absolute total number of days from this datetime to provided datetime */
    size_t daysUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return this->m_date.daysUntil(vdatetime_ex.m_date);
    }

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    size_t minutesUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        size_t dayMinutes{ (this->daysUntil(vdatetime_ex) * (size_t)1'440ULL) };

        //

        return dayMinutes;// <--- THIS IS INCOMPLETE!
    }

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        size_t totalSeconds{ 0 };

        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return totalSeconds;

        std::pair<const VDatetimeEx*, const VDatetimeEx*> dtRef{
            nullptr, nullptr// (high, low)
        };

        if (this->isAfter(vdatetime_ex)) {
            dtRef.first = this;
            dtRef.second = &vdatetime_ex;
        }
        else {
            dtRef.first = &vdatetime_ex;
            dtRef.second = this;
        }

        VDatetimeEx temp{ (*dtRef.second) };

        // Accum. seconds
        totalSeconds += (
            temp.vtime_ex().getSecond().untilPosition(dtRef.first->vtime_ex().getSecond())
        );
        temp.getTime()->getSecond().increment(
            temp.vtime_ex().getSecond().untilPosition(
                dtRef.first->vtime_ex().getSecond()
            )
        );

        // Accum. minutes
        totalSeconds += (
            ((size_t)temp.vtime_ex().getMinute().untilPosition(dtRef.first->vtime_ex().getMinute()) * (size_t)60ULL)
        );
        temp.getTime()->getMinute().increment(
            temp.vtime_ex().getMinute().untilPosition(
                dtRef.first->vtime_ex().getMinute()
            )
        );

        // Accum. hours
        totalSeconds += (
            ((size_t)temp.vtime_ex().getHour().untilPosition(dtRef.first->vtime_ex().getHour()) * (size_t)3'600ULL)
        );
        temp.getTime()->getHour().increment(
            temp.vtime_ex().getHour().untilPosition(
                dtRef.first->vtime_ex().getHour()
            )
        );

        // Accum. days
        totalSeconds += (
            ((size_t)temp.v_date().daysUntil(dtRef.first->v_date()) * (size_t)86'400ULL)
        );

        return totalSeconds;
    }

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t millisecondsUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        size_t totalMs{ 0 };

        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return totalMs;

        std::pair<const VDatetimeEx*, const VDatetimeEx*> dtRef{
            nullptr, nullptr// (high, low)
        };

        if (this->isAfter(vdatetime_ex)) {
            dtRef.first = this;
            dtRef.second = &vdatetime_ex;
        }
        else {
            dtRef.first = &vdatetime_ex;
            dtRef.second = this;
        }

        VDatetimeEx temp{ (*dtRef.second) };

        // Accum. milliseconds
        totalMs += (
            temp.vtime_ex().getMillisecond().untilPosition(
                dtRef.first->vtime_ex().getMillisecond()
            )
        );
        temp.getTime()->getMillisecond().increment(
            temp.vtime_ex().getMillisecond().untilPosition(
                dtRef.first->vtime_ex().getMillisecond()
            )
        );

        // Accum. seconds
        totalMs += (
            ((size_t)temp.vtime_ex().getSecond().untilPosition(dtRef.first->vtime_ex().getSecond()) * (size_t)1'000ULL)
        );
        temp.getTime()->getSecond().increment(
            temp.vtime_ex().getSecond().untilPosition(
                dtRef.first->vtime_ex().getSecond()
            )
        );

        // Accum. minutes
        totalMs += (
            ((size_t)temp.vtime_ex().getMinute().untilPosition(dtRef.first->vtime_ex().getMinute()) * (size_t)60'000ULL)
        );
        temp.getTime()->getMinute().increment(
            temp.vtime_ex().getMinute().untilPosition(
                dtRef.first->vtime_ex().getMinute()
            )
        );

        // Accum. hours
        totalMs += (
            ((size_t)temp.vtime_ex().getHour().untilPosition(dtRef.first->vtime_ex().getHour()) * (size_t)3'600'000ULL)
        );
        temp.getTime()->getHour().increment(
            temp.vtime_ex().getHour().untilPosition(
                dtRef.first->vtime_ex().getHour()
            )
        );

        // Accum. days
        totalMs += (
            ((size_t)temp.v_date().daysUntil(dtRef.first->v_date()) * (size_t)86'400'000ULL)
        );

        return totalMs;
    }

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return VDuration{};
        
        VDuration result{};
        result.getMs().largeDisplace(
            VDuration::Sign::POSITIVE,
            this->millisecondsUntil(vdatetime_ex)
        );

        if (this->isAfter(vdatetime_ex) && result.sign() != VDuration::Sign::NEGATIVE)
            result.invert();

        return result;
    }

    /* Returns standard library chronological time point of this datetime */
    TimePoint toChrono() const noexcept
    {
        TimePoint timePoint{};

        VDatetimeEx epoch{ TimePoint{} };
        VDuration sinceEpoch{ epoch.until(*this) };

        timePoint = (timePoint + sinceEpoch.toChronoDuration());

        return timePoint;
    }

    /* Displace datetime using provided duration */
    void displace(const VDuration& duration) noexcept
    {
        this->m_time.displace(duration);
    }


private:
    VDate m_date;
    VTimeEx m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_V_DATETIME_EXTENDED_H_
