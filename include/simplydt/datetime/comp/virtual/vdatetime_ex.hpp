
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

    inline static const JDN EPOCH_JDN = ((JDN)VDate::EPOCH_JDN + (JDN).5);
    inline static const JDN MAX_JDN = ((JDN)VDate::MAX_JDN + (JDN)1.49999999);

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
    uint32_t daysUntil(const VDate& v_date) const noexcept
    {
        return this->m_date.daysUntil(v_date);
    }

    /* Returns absolute total number of days from this datetime to provided datetime */
    uint32_t daysUntil(const TimePoint& sys_clock) const noexcept
    {
        return this->m_date.daysUntil(sys_clock);
    }

    //* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        uint32_t total{ 0 };

        if (this == &vdatetime_ex)
            return total;

        total += (this->daysUntil(vdatetime_ex) * (uint32_t)24Ui32);
        
        if (this->m_time.isBefore(vdatetime_ex.m_time) || total == (uint32_t)0Ui32)
            total += this->m_time.hoursUntil(vdatetime_ex.m_time);
        else if (this->m_time.isAfter(vdatetime_ex.m_time))
            total -= this->m_time.hoursUntil(vdatetime_ex.m_time);

        return total;
    }

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of hours from this datetime to provided date */
    uint32_t hoursUntil(const VDate& v_date) const noexcept
    {
        uint32_t total{ 0 };

        total += (this->daysUntil(v_date) * (uint32_t)24Ui32);

        if (this->m_time.hour() == (uint16_t)0Ui16)
            return total;

        VTimeEx implicitTime{};// 00:00:00 AM

        if (!total)
            total += this->m_time.hoursUntil(implicitTime);
        else
            total -= this->m_time.hoursUntil(implicitTime);

        return total;
    }

    /* Returns absolute total number of hours from this datetime to provided datetime */
    uint32_t hoursUntil(const TimePoint& sys_clock) const noexcept
    {
        uint32_t total{ 0 };

        total += (this->daysUntil(sys_clock) * (uint32_t)24Ui32);

        if (this->m_time < sys_clock || total == (uint32_t)0Ui32)
            total += this->m_time.hoursUntil(sys_clock);
        else if (this->m_time > sys_clock)
            total -= this->m_time.hoursUntil(sys_clock);

        return total;
    }

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const VDatetimeEx& vdatetime_ex) const noexcept//      <--- INCOMPLETE!
    {
        uint32_t total{ 0 };

        if (this == &vdatetime_ex)
            return total;

        total += (this->daysUntil(vdatetime_ex) * (uint32_t)1'440Ui32);

        if (this->m_time.isBefore(vdatetime_ex.m_time) || total == (uint32_t)0Ui32)
            total += this->m_time.minutesUntil(vdatetime_ex.m_time);
        else if (this->m_time.isAfter(vdatetime_ex.m_time))
            total -= this->m_time.minutesUntil(vdatetime_ex.m_time);

        return total;
    }

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of minutes from this datetime to provided date */
    uint32_t minutesUntil(const VDate& v_date) const noexcept
    {
        uint32_t total{ 0 };

        total += (this->daysUntil(v_date) * (uint32_t)1'440Ui32);

        if (
            this->m_time.hour() == (uint16_t)0Ui16
            && this->m_time.minute() == (uint16_t)0Ui16
        ) {
            return total;
        }

        VTimeEx implicitTime{};// 00:00:00 AM

        if (!total)
            total += this->m_time.minutesUntil(implicitTime);
        else
            total -= this->m_time.minutesUntil(implicitTime);

        return total;
    }

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    uint32_t minutesUntil(const TimePoint& sys_clock) const noexcept
    {
        uint32_t total{ 0 };

        total += (this->daysUntil(sys_clock) * (uint32_t)1'440Ui32);

        if (this->m_time < sys_clock || total == (uint32_t)0Ui32)
            total += this->m_time.minutesUntil(sys_clock);
        else if (this->m_time > sys_clock)
            total -= this->m_time.minutesUntil(sys_clock);

        return total;
    }

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        size_t total{ 0 };

        if (this == &vdatetime_ex)
            return total;

        total += ((size_t)this->daysUntil(vdatetime_ex) * (size_t)86'400Ui64);

        if (this->m_time.isBefore(vdatetime_ex.m_time) || total == (size_t)0Ui64)
            total += this->m_time.secondsUntil(vdatetime_ex.m_time);
        else if (this->m_time.isAfter(vdatetime_ex.m_time))
            total -= this->m_time.secondsUntil(vdatetime_ex.m_time);

        return total;
    }

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of seconds from this datetime to provided date */
    size_t secondsUntil(const VDate& v_date) const noexcept
    {
        size_t total{ 0 };

        total += ((size_t)this->daysUntil(v_date) * (size_t)86'400Ui64);

        if (
            this->m_time.hour() == (uint16_t)0Ui16
            && this->m_time.minute() == (uint16_t)0Ui16
            && this->m_time.second() == (uint16_t)0Ui16
        ) {
            return total;
        }

        VTimeEx implicitTime{};// 00:00:00 AM

        if (!total)
            total += this->m_time.secondsUntil(implicitTime);
        else
            total -= this->m_time.secondsUntil(implicitTime);

        return total;
    }

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const TimePoint& sys_clock) const noexcept
    {
        size_t total{ 0 };

        total += ((size_t)this->daysUntil(sys_clock) * (size_t)86'400Ui64);

        if (this->m_time < sys_clock || total == (size_t)0Ui64)
            total += this->m_time.secondsUntil(sys_clock);
        else if (this->m_time > sys_clock)
            total -= this->m_time.secondsUntil(sys_clock);

        return total;
    }

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t msUntil(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        size_t total{ 0 };

        if (this == &vdatetime_ex)
            return total;

        total += ((size_t)this->daysUntil(vdatetime_ex) * (size_t)86'400'000Ui64);

        if (this->m_time.isBefore(vdatetime_ex.m_time) || total == (size_t)0Ui64)
            total += this->m_time.msUntil(vdatetime_ex.m_time);
        else if (this->m_time.isAfter(vdatetime_ex.m_time))
            total -= this->m_time.msUntil(vdatetime_ex.m_time);

        return total;
    }

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t msUntil(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns absolute total number of milliseconds from this datetime to provided date */
    size_t msUntil(const VDate& v_date) const noexcept
    {
        size_t total{ 0 };

        total += ((size_t)this->daysUntil(v_date) * (size_t)86'400'000Ui64);

        if (this->m_time.isZero())
            return total;

        VTimeEx implicitTime{};// 00:00:00:000 AM

        if (!total)
            total += this->m_time.msUntil(implicitTime);
        else
            total -= this->m_time.msUntil(implicitTime);

        return total;
    }

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t msUntil(const TimePoint& sys_clock) const noexcept
    {
        size_t total{ 0 };
        
        total += ((size_t)this->daysUntil(sys_clock) * (size_t)86'400'000Ui64);

        if (this->m_time < sys_clock || total == (size_t)0Ui64)
            total += this->m_time.msUntil(sys_clock);
        else if (this->m_time > sys_clock)
            total -= this->m_time.msUntil(sys_clock);

        return total;
    }

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const VDatetimeEx& vdatetime_ex) const noexcept
    {
        if (this == &vdatetime_ex || *this == vdatetime_ex)
            return VDuration{};
        
        VDuration difference{};

        difference.getMs()->largeDisplace(
            VDuration::Sign::POSITIVE,
            this->msUntil(vdatetime_ex)
        );

        if (this->isAfter(vdatetime_ex))
            difference.invert();

        return difference;
    }

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const VDatetime& v_datetime) const noexcept;//      <--- INCOMPLETE!

    /* Returns duration from this datetime to provided date */
    VDuration until(const VDate& v_date) const noexcept
    {
        VDuration difference{ this->m_date.until(v_date) };

        if (difference.sign() == VDuration::Sign::POSITIVE) {
            difference.getMs()->largeDisplace(
                VDuration::Sign::NEGATIVE,
                this->m_time.convertedTo(VTimeEx::TimeUnit::MILLISECOND)
            );
        }
        else if (difference.sign() == VDuration::Sign::NEGATIVE) {
            difference.getMs()->largeDisplace(
                VDuration::Sign::POSITIVE,
                this->m_time.convertedTo(VTimeEx::TimeUnit::MILLISECOND)
            );
        }

        return difference;
    }

    /* Returns duration from this datetime to provided datetime */
    VDuration until(const TimePoint& sys_clock) const noexcept
    {
        VDuration difference{};

        difference.getMs()->largeDisplace(
            VDuration::Sign::POSITIVE,
            this->msUntil(sys_clock)
        );

        if (this->isAfter(sys_clock))
            difference.invert();

        return difference;
    }

    /* Displace datetime using provided duration */
    void displace(const VDuration& v_duration) noexcept
    {
        // NOTE: Ends up using .dateDisplace() loop, fix this!
        this->m_time.displace(v_duration);
    }

    /* Reset datetime to epoch */
    void reset() noexcept
    {
        this->m_time.reset();
        this->m_date.reset();
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
