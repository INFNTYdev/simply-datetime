
#ifndef SIMPLYDTLIB_L_DATETIME_V_DATETIME_EXTENDED_H_
#define SIMPLYDTLIB_L_DATETIME_V_DATETIME_EXTENDED_H_



#include"simplydt/datetime/date/comp/virtual/dt_vdate.hpp"
#include"simplydt/datetime/time/comp/virtual/dt_vtime_ex.hpp"
#include"simplydt/datetime/comp/virtual/vdatetime.hpp"


/* Extended virtualized datetime (YYYY-mm-dd-HH-MM-SS-MS) */
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

    inline static const JDN EPOCH_JDN = (VDate::EPOCH_JDN + (double).5);
    inline static const JDN MAX_JDN = ((VDate::MAX_JDN + (JDN)1.) + (double).49999999);

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

    explicit VDatetimeEx(const JDN& jdn) noexcept
        : m_date{ jdn },
        m_time{ jdn }
    {
        // Normalize time if invalid JDN
        // (Date will normalize on invalid JDN)
        if (jdn < EPOCH_JDN)
            this->m_time.reset();

        if (jdn > MAX_JDN) {
            this->m_time.getHour()->setPosition(11);
            this->m_time.getMinute()->setPosition(59);
            this->m_time.getSecond()->setPosition(59);
            this->m_time.getMs()->setPosition(999);
        }

        this->linkDatetime();
    }

    VDatetimeEx(const VDatetime& v_datetime) noexcept;//      <--- INCOMPLETE!

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

    VDatetimeEx& operator=(const VDatetime& v_datetime) noexcept;//      <--- INCOMPLETE!

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

    bool operator==(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator==(const VDate& v_date) const noexcept
    {
        if (this->m_date != v_date)
            return false;

        return true;
    }

    bool operator==(const VTimeEx& vtime_ex) const noexcept
    {
        if (this->m_time != vtime_ex)
            return false;

        return true;
    }

    bool operator==(const TimePoint& sys_clock) const noexcept
    {
        if (this->m_date != sys_clock)
            return false;

        if (this->m_time != sys_clock)
            return false;

        return true;
    }

    bool operator<(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return this->isBefore(vdatetime_ex);
    }

    bool operator<(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator<(const VDate& v_date) const noexcept
    {
        return this->isBefore(v_date);
    }

    bool operator<(const VTimeEx& vtime_ex) const noexcept
    {
        return (this->m_time < vtime_ex);
    }
    
    bool operator<(const TimePoint& sys_clock) const noexcept
    {
        return this->isBefore(sys_clock);
    }

    bool operator>(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return this->isAfter(vdatetime_ex);
    }

    bool operator>(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator>(const VDate& v_date) const noexcept
    {
        return this->isAfter(v_date);
    }

    bool operator>(const VTimeEx& vtime_ex) const noexcept
    {
        return (this->m_time > vtime_ex);
    }

    bool operator>(const TimePoint& sys_clock) const noexcept
    {
        return this->isAfter(sys_clock);
    }

    bool operator<=(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return (this->isBefore(vdatetime_ex) || this->operator==(vdatetime_ex));
    }

    bool operator<=(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator<=(const VDate& v_date) const noexcept
    {
        return (this->isBefore(v_date) || this->operator==(v_date));
    }

    bool operator<=(const VTimeEx& vtime_ex) const noexcept
    {
        return (this->m_time < vtime_ex || this->m_time == vtime_ex);
    }

    bool operator<=(const TimePoint& sys_clock) const noexcept
    {
        return (this->isBefore(sys_clock) || this->operator==(sys_clock));
    }

    bool operator>=(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return (this->isAfter(vdatetime_ex) || this->operator==(vdatetime_ex));
    }

    bool operator>=(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    bool operator>=(const VDate& v_date) const noexcept
    {
        return (this->isAfter(v_date) || this->operator==(v_date));
    }

    bool operator>=(const VTimeEx& vtime_ex) const noexcept
    {
        return (this->m_time > vtime_ex || this->m_time == vtime_ex);
    }

    bool operator>=(const TimePoint& sys_clock) const noexcept
    {
        return (this->isAfter(sys_clock) || this->operator==(sys_clock));
    }

    VDatetimeEx operator+(const VDuration& v_duration) const noexcept
    {
        VDatetimeEx temp{ *this };

        (*temp.getTime()) += v_duration;

        return temp;
    }

    VDatetimeEx operator-(const VDuration& v_duration) const noexcept
    {
        VDatetimeEx temp{ *this };

        (*temp.getTime()) -= v_duration;

        return temp;
    }

    VDatetimeEx& operator+=(const VDuration& v_duration) noexcept
    {
        this->m_time += v_duration;

        return *this;
    }

    VDatetimeEx& operator-=(const VDuration& v_duration) noexcept
    {
        this->m_time -= v_duration;

        return *this;
    }

    /* Returns true if datetime represents epoch datetime */
    bool isEpoch() const noexcept
    {
        return (this->m_date.isEpoch() && this->m_time.isZero());
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

    /* Returns internal datetime date */
    const VDate& date() const noexcept
    {
        return this->m_date;
    }

    /* Returns internal datetime time */
    const VTimeEx& time() const noexcept
    {
        return this->m_time;
    }

    /* Returns pointer to internal datetime date */
    VDate* getDate() noexcept
    {
        return &this->m_date;
    }

    /* Returns pointer to internal datetime time */
    VTimeEx* getTime() noexcept
    {
        return &this->m_time;
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

    /* Returns datetime day-of-week index */
    uint8_t dowIndex() const noexcept;//      <--- INCOMPLETE!

    /* Returns datetime month literal */
    const char* monthTitle() const noexcept
    {
        return this->m_date.monthTitle();
    }

    /* Returns datetime month index */
    uint8_t monthIndex() const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return false;
        
        if (this->m_date.isAfter(vdatetime_ex.m_date))
            return false;
        else if (this->m_date.isBefore(vdatetime_ex.m_date))
            return true;
        
        if (this->m_time.isAfter(vdatetime_ex.m_time))
            return false;

        return true;
    }

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const VDate& v_date) const noexcept
    {
        if (&this->m_date == &v_date || this->m_date == v_date)
            return false;
        
        if (this->m_date.isAfter(v_date))
            return false;

        return true;
    }

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const TimePoint& sys_clock) const noexcept
    {
        if (this->m_date > sys_clock)
            return false;
        else if (this->m_date < sys_clock)
            return true;

        if (this->m_time >= sys_clock)
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
        else if (this->m_date.isAfter(vdatetime_ex.m_date))
            return true;

        if (this->m_time.isBefore(vdatetime_ex.m_time))
            return false;

        return true;
    }

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const VDate& v_date) const noexcept
    {
        if (&this->m_date == &v_date || this->m_date == v_date)
            return false;
        
        if (this->m_date.isBefore(v_date))
            return false;

        return true;
    }

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const TimePoint& sys_clock) const noexcept
    {
        if (this->m_date < sys_clock)
            return false;
        else if (this->m_date > sys_clock)
            return true;

        if (this->m_time <= sys_clock)
            return false;

        return true;
    }

    /* Returns datetime as Julian Day Number (JDN) */
    JDN toJulianDayNumber() const noexcept
    {
        return (
            (JDN)this->m_date.trueJulianDayNumber() + this->m_time.rawJulianDayNumber()
        );
    }

    // /* Returns standard datetime copy of this datetime */
    // VDatetime toVDatetime() const noexcept//      <--- INCOMPLETE!
    // {
    //     return VDatetime{
    //         this->m_date,
    //         VTime(
    //             this->hour(),
    //             this->minute(),
    //             this->second()
    //         )
    //     };
    // }

    /* Returns datetime as standard library system clock time point */
    TimePoint toTimePoint() const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of days from this datetime to provided datetime */
    uint32_t daysUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        return this->m_date.daysUntil(vdatetime_ex.m_date);
    }

    /* Returns absolute total number of days from this datetime to provided datetime */
    uint32_t daysUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of days from this datetime to provided date */
    uint32_t daysUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of days from this datetime to provided datetime */
    uint32_t daysUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const VDatetimeEx& vdatetime_ex) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided date */
    uint32_t hoursUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    // /* Returns absolute total number of minutes from this datetime to provided datetime */
    // size_t minutesUntil(const VDatetimeEx& vdatetime_ex) const noexcept//      <--- INCOMPLETE!
    // {
    //     size_t dayMinutes{ (this->daysUntil(vdatetime_ex) * (size_t)1'440ULL) };

    //     //

    //     return dayMinutes;
    // }

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of minutes from this datetime to provided date */
    uint32_t minutesUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    // /* Returns absolute total number of seconds from this datetime to provided datetime */
    // size_t secondsUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    // {
    //     size_t totalSeconds{ 0 };

    //     if (this == &vdatetime_ex || *this == vdatetime_ex)
    //         return totalSeconds;

    //     std::pair<const VDatetimeEx*, const VDatetimeEx*> dtRef{
    //         nullptr, nullptr// (high, low)
    //     };

    //     if (this->isAfter(vdatetime_ex)) {
    //         dtRef.first = this;
    //         dtRef.second = &vdatetime_ex;
    //     }
    //     else {
    //         dtRef.first = &vdatetime_ex;
    //         dtRef.second = this;
    //     }

    //     VDatetimeEx temp{ (*dtRef.second) };

    //     // Accum. seconds
    //     totalSeconds += (
    //         temp.vtime_ex().getSecond().untilPosition(dtRef.first->vtime_ex().getSecond())
    //     );
    //     temp.getTime()->getSecond().increment(
    //         temp.vtime_ex().getSecond().untilPosition(
    //             dtRef.first->vtime_ex().getSecond()
    //         )
    //     );

    //     // Accum. minutes
    //     totalSeconds += (
    //         ((size_t)temp.vtime_ex().getMinute().untilPosition(dtRef.first->vtime_ex().getMinute()) * (size_t)60ULL)
    //     );
    //     temp.getTime()->getMinute().increment(
    //         temp.vtime_ex().getMinute().untilPosition(
    //             dtRef.first->vtime_ex().getMinute()
    //         )
    //     );

    //     // Accum. hours
    //     totalSeconds += (
    //         ((size_t)temp.vtime_ex().getHour().untilPosition(dtRef.first->vtime_ex().getHour()) * (size_t)3'600ULL)
    //     );
    //     temp.getTime()->getHour().increment(
    //         temp.vtime_ex().getHour().untilPosition(
    //             dtRef.first->vtime_ex().getHour()
    //         )
    //     );

    //     // Accum. days
    //     totalSeconds += (
    //         ((size_t)temp.v_date().daysUntil(dtRef.first->v_date()) * (size_t)86'400ULL)
    //     );

    //     return totalSeconds;
    // }

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of seconds from this datetime to provided date */
    size_t secondsUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    // /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    // size_t millisecondsUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    // {
    //     size_t totalMs{ 0 };

    //     if (this == &vdatetime_ex || *this == vdatetime_ex)
    //         return totalMs;

    //     std::pair<const VDatetimeEx*, const VDatetimeEx*> dtRef{
    //         nullptr, nullptr// (high, low)
    //     };

    //     if (this->isAfter(vdatetime_ex)) {
    //         dtRef.first = this;
    //         dtRef.second = &vdatetime_ex;
    //     }
    //     else {
    //         dtRef.first = &vdatetime_ex;
    //         dtRef.second = this;
    //     }

    //     VDatetimeEx temp{ (*dtRef.second) };

    //     // Accum. milliseconds
    //     totalMs += (
    //         temp.vtime_ex().getMillisecond().untilPosition(
    //             dtRef.first->vtime_ex().getMillisecond()
    //         )
    //     );
    //     temp.getTime()->getMillisecond().increment(
    //         temp.vtime_ex().getMillisecond().untilPosition(
    //             dtRef.first->vtime_ex().getMillisecond()
    //         )
    //     );

    //     // Accum. seconds
    //     totalMs += (
    //         ((size_t)temp.vtime_ex().getSecond().untilPosition(dtRef.first->vtime_ex().getSecond()) * (size_t)1'000ULL)
    //     );
    //     temp.getTime()->getSecond().increment(
    //         temp.vtime_ex().getSecond().untilPosition(
    //             dtRef.first->vtime_ex().getSecond()
    //         )
    //     );

    //     // Accum. minutes
    //     totalMs += (
    //         ((size_t)temp.vtime_ex().getMinute().untilPosition(dtRef.first->vtime_ex().getMinute()) * (size_t)60'000ULL)
    //     );
    //     temp.getTime()->getMinute().increment(
    //         temp.vtime_ex().getMinute().untilPosition(
    //             dtRef.first->vtime_ex().getMinute()
    //         )
    //     );

    //     // Accum. hours
    //     totalMs += (
    //         ((size_t)temp.vtime_ex().getHour().untilPosition(dtRef.first->vtime_ex().getHour()) * (size_t)3'600'000ULL)
    //     );
    //     temp.getTime()->getHour().increment(
    //         temp.vtime_ex().getHour().untilPosition(
    //             dtRef.first->vtime_ex().getHour()
    //         )
    //     );

    //     // Accum. days
    //     totalMs += (
    //         ((size_t)temp.v_date().daysUntil(dtRef.first->v_date()) * (size_t)86'400'000ULL)
    //     );

    //     return totalMs;
    // }

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t msUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of milliseconds from this datetime to provided date */
    size_t msUntil(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t millisecondsUntil(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    // /* Returns duration from this datetime to provided datetime */
    // VDuration until(const VDatetimeEx& vdatetime_ex) const noexcept
    // {
    //     if (this == &vdatetime_ex || *this == vdatetime_ex)
    //         return VDuration{};
        
    //     VDuration result{};
    //     result.getMs().largeDisplace(
    //         VDuration::Sign::POSITIVE,
    //         this->millisecondsUntil(vdatetime_ex)
    //     );

    //     if (this->isAfter(vdatetime_ex) && result.sign() != VDuration::Sign::NEGATIVE)
    //         result.invert();

    //     return result;
    // }

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns duration from this datetime to provided date */
    VDuration until(const VDate& v_date) const noexcept;//      <--- INCOMPLETE!

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const TimePoint& sys_clock) const noexcept;//      <--- INCOMPLETE!

    /* Displace datetime using provided duration */
    void displace(const VDuration& v_duration) noexcept
    {
        // NOTE: Ends up using .dateDisplace() loop, fix this!
        this->m_time.displace(v_duration);
    }

    /* Reset datetime to epoch */
    void reset() noexcept;//      <--- INCOMPLETE!


private:
    VDate m_date;
    VTimeEx m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_V_DATETIME_EXTENDED_H_
