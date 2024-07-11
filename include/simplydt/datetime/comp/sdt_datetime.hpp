
#ifndef SIMPLYDTLIB_L_DATETIME_OBJ_H_
#define SIMPLYDTLIB_L_DATETIME_OBJ_H_



#include"simplydt/datetime/date/comp/dt_date.hpp"
#include"simplydt/datetime/time/comp/dt_time.hpp"
#include"simplydt/datetime/comp/sdt_sdatetime.hpp"


/* Full datetime (YYYY-mm-dd-HH-MM-SS-MS) */
class Datetime {

public:
    /* Datetime time unit */
    using Unit = Date::TimeUnit;
    /* Datetime type */
    using Type = Date::DatetimeType;
    /* Standard library chronological time point (system clock) */
    using Chrono = std::chrono::time_point<std::chrono::system_clock>;

    /* Datetime layout */
    enum Layout {
        DATE_TIME,// date - time
        TIME_DATE,// time - date
    };

    Datetime(const Chrono& chrono) noexcept
        : m_date{ chrono },
        m_time{ chrono }
    {
        this->linkDatetime();
    }

    Datetime(const Date& date, const Time& time) noexcept
        : m_date{ date },
        m_time{ time }
    {
        this->linkDatetime();
    }

    Datetime(Date&& date, Time&& time) noexcept
        : m_date{ std::forward<Date>(date) },
        m_time{ std::forward<Time>(time) }
    {
        this->linkDatetime();
    }

    Datetime(const Date& date, Time&& time) noexcept
        : m_date{ date },
        m_time{ std::forward<Time>(time) }
    {
        this->linkDatetime();
    }

    Datetime(Date&& date, const Time& time) noexcept
        : m_date{ std::forward<Date>(date) },
        m_time{ time }
    {
        this->linkDatetime();
    }

    Datetime(const Date& date) noexcept
        : m_date{ date },
        m_time{}
    {
        this->linkDatetime();
    }

    Datetime(Date&& date) noexcept
        : m_date{ std::forward<Date>(date) },
        m_time{}
    {
        this->linkDatetime();
    }

    Datetime(const Datetime& datetime) noexcept
        : m_date{ datetime.m_date },
        m_time{ datetime.m_time }
    {
        this->linkDatetime();
    }

    Datetime(Datetime&& datetime) noexcept
        : m_date{ std::move(datetime.m_date) },
        m_time{ std::move(datetime.m_time) }
    {
        //
    }

    Datetime(const SDatetime& s_datetime) noexcept;//   <--- Complete SDatetime first

    Datetime(SDatetime&& s_datetime) noexcept;//   <--- Complete SDatetime first

    Datetime() noexcept
        : m_date{},
        m_time{}
    {
        this->linkDatetime();
    }

    ~Datetime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Datetime& datetime) noexcept
    {
        os << datetime.datetimeStr();

        return os;
    }

    Datetime& operator=(const Datetime& datetime) noexcept
    {
        if (this == &datetime)
            return *this;
        
        this->m_date = datetime.m_date;
        this->m_time = datetime.m_time;

        this->linkDatetime();

        return *this;
    }

    Datetime& operator=(Datetime&& datetime) noexcept
    {
        if (this == &datetime)
            return *this;
        
        this->m_date = std::move(datetime.m_date);
        this->m_time = std::move(datetime.m_time);

        return *this;
    }

    Datetime& operator=(const SDatetime& s_datetime) noexcept;//   <--- Complete SDatetime first

    Datetime& operator=(SDatetime&& s_datetime) noexcept;//   <--- Complete SDatetime first

    Datetime& operator=(const Chrono& chrono) noexcept
    {
        this->m_date = chrono;
        this->m_time = chrono;

        return *this;
    }

    bool operator==(const Datetime& datetime) const noexcept
    {
        if (this == &datetime)
            return true;
        
        if (this->m_date != datetime.m_date)
            return false;
        
        if (this->m_time != datetime.m_time)
            return false;

        return true;
    }

    bool operator==(const SDatetime& s_datetime) const noexcept;//   <--- Complete SDatetime first

    bool operator<(const Datetime& datetime) const noexcept
    {
        return this->isBefore(datetime);
    }

    bool operator>(const Datetime& datetime) const noexcept
    {
        return this->isAfter(datetime);
    }

    bool operator<=(const Datetime& datetime) const noexcept
    {
        return (this->isBefore(datetime) || this->operator==(datetime));
    }

    bool operator>=(const Datetime& datetime) const noexcept
    {
        return (this->isAfter(datetime) || this->operator==(datetime));
    }

    Datetime operator+(const Duration& duration) const noexcept
    {
        Datetime result{ *this };

        result.displace(duration);

        return result;
    }

    Datetime operator-(const Duration& duration) const noexcept
    {
        Datetime result{ *this };

        (*result.getTime()) -= duration;

        return result;
    }

    Datetime& operator+=(const Duration& duration) noexcept
    {
        this->m_time += duration;

        return *this;
    }

    Datetime& operator-=(const Duration& duration) noexcept
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
    const Date& date() const noexcept
    {
        return this->m_date;
    }

    /* Datetime time object */
    const Time& time() const noexcept
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
    std::string datetimeStr(Layout layout, Date::Format date_format, Date::Layout date_layout,
        Time::Format time_format, Time::Layout time_layout) const noexcept
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
    std::string datetimeStr(Date::Format date_format, Date::Layout date_layout,
        Time::Format time_format, Time::Layout time_layout) const noexcept
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
    std::string datetimeStr(Date::Format date_format, Date::Layout date_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            date_layout,// Date layout
            Time::Format::MILITARY,// Time format
            Time::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Time::Format time_format, Time::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            Date::Format::RECORD,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            time_format,// Time format
            time_layout// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, Time::Format time_format) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            time_format,// Time format
            Time::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Layout date_layout, Time::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            Date::Format::RECORD,// Date format
            date_layout,// Date layout
            Time::Format::MILITARY,// Time format
            time_layout// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            date_format,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            Time::Format::MILITARY,// Time format
            Time::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Layout date_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            Date::Format::RECORD,// Date format
            date_layout,// Date layout
            Time::Format::MILITARY,// Time format
            Time::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Time::Format time_format) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            Date::Format::RECORD,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            time_format,// Time format
            Time::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Time::Layout time_layout) const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            Date::Format::RECORD,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            Time::Format::MILITARY,// Time format
            time_layout// Time layout
        );
    }
    
    /* Returns datetime string in provided layout */
    std::string datetimeStr(Layout layout) const noexcept
    {
        return this->datetimeStr(
            layout,// Datetime object layout
            Date::Format::RECORD,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            Time::Format::MILITARY,// Time format
            Time::Layout::H_M_S_MS// Time layout
        );
    }

    /* Returns datetime string */
    std::string datetimeStr() const noexcept
    {
        return this->datetimeStr(
            Layout::DATE_TIME,// Datetime object layout
            Date::Format::RECORD,// Date format
            Date::Layout::M_D_YYYY,// Date layout
            Time::Format::MILITARY,// Time format
            Time::Layout::H_M_S_MS// Time layout
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
    bool isBefore(const Datetime& datetime) const noexcept
    {
        if (this == &datetime || *this == datetime)
            return false;
        
        if (this->m_date.isAfter(datetime.m_date))
            return false;
        
        if (this->m_time.isAfter(datetime.m_time))
            return false;

        return true;
    }

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const Date& date) const noexcept
    {
        if (&this->m_date == &date || this->m_date == date)
            return false;
        
        if (this->m_date.isAfter(date))
            return false;

        return true;
    }

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const Datetime& datetime) const noexcept
    {
        if (this == &datetime || *this == datetime)
            return false;
        
        if (this->m_date.isBefore(datetime.m_date))
            return false;
        
        if (this->m_time.isBefore(datetime.m_time))
            return false;

        return true;
    }

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const Date& date) const noexcept
    {
        if (&this->m_date == &date || this->m_date == date)
            return false;
        
        if (this->m_date.isBefore(date))
            return false;

        return true;
    }

    /* Returns pointer to datetime date */
    Date* getDate() noexcept
    {
        return &this->m_date;
    }

    /* Returns pointer to datetime time */
    Time* getTime() noexcept
    {
        return &this->m_time;
    }

    /* Returns standard datetime copy of this datetime */
    SDatetime toSDatetime() const noexcept
    {
        return SDatetime{
            this->m_date,
            STime(
                this->hour(),
                this->minute(),
                this->second()
            )
        };
    }

    /* Returns absolute total number of days from this datetime to provided datetime */
    size_t daysUntil(const Datetime& datetime) const noexcept
    {
        return this->m_date.daysUntil(datetime.m_date);
    }

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    size_t minutesUntil(const Datetime& datetime) const noexcept
    {
        size_t dayMinutes{ (this->daysUntil(datetime) * (size_t)1'440ULL) };

        //

        return dayMinutes;// <--- THIS IS INCOMPLETE!
    }

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const Datetime& datetime) const noexcept
    {
        size_t totalSeconds{ 0 };

        if (this == &datetime || *this == datetime)
            return totalSeconds;

        std::pair<const Datetime*, const Datetime*> dtRef{
            nullptr, nullptr// (high, low)
        };

        if (this->isAfter(datetime)) {
            dtRef.first = this;
            dtRef.second = &datetime;
        }
        else {
            dtRef.first = &datetime;
            dtRef.second = this;
        }

        Datetime temp{ (*dtRef.second) };

        // Accum. seconds
        totalSeconds += (
            temp.time().getSecond().untilPosition(dtRef.first->time().getSecond())
        );
        temp.getTime()->getSecond().increment(
            temp.time().getSecond().untilPosition(
                dtRef.first->time().getSecond()
            )
        );

        // Accum. minutes
        totalSeconds += (
            ((size_t)temp.time().getMinute().untilPosition(dtRef.first->time().getMinute()) * (size_t)60ULL)
        );
        temp.getTime()->getMinute().increment(
            temp.time().getMinute().untilPosition(
                dtRef.first->time().getMinute()
            )
        );

        // Accum. hours
        totalSeconds += (
            ((size_t)temp.time().getHour().untilPosition(dtRef.first->time().getHour()) * (size_t)3'600ULL)
        );
        temp.getTime()->getHour().increment(
            temp.time().getHour().untilPosition(
                dtRef.first->time().getHour()
            )
        );

        // Accum. days
        totalSeconds += (
            ((size_t)temp.date().daysUntil(dtRef.first->date()) * (size_t)86'400ULL)
        );

        return totalSeconds;
    }

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t millisecondsUntil(const Datetime& datetime) const noexcept
    {
        size_t totalMs{ 0 };

        if (this == &datetime || *this == datetime)
            return totalMs;

        std::pair<const Datetime*, const Datetime*> dtRef{
            nullptr, nullptr// (high, low)
        };

        if (this->isAfter(datetime)) {
            dtRef.first = this;
            dtRef.second = &datetime;
        }
        else {
            dtRef.first = &datetime;
            dtRef.second = this;
        }

        Datetime temp{ (*dtRef.second) };

        // Accum. milliseconds
        totalMs += (
            temp.time().getMillisecond().untilPosition(
                dtRef.first->time().getMillisecond()
            )
        );
        temp.getTime()->getMillisecond().increment(
            temp.time().getMillisecond().untilPosition(
                dtRef.first->time().getMillisecond()
            )
        );

        // Accum. seconds
        totalMs += (
            ((size_t)temp.time().getSecond().untilPosition(dtRef.first->time().getSecond()) * (size_t)1'000ULL)
        );
        temp.getTime()->getSecond().increment(
            temp.time().getSecond().untilPosition(
                dtRef.first->time().getSecond()
            )
        );

        // Accum. minutes
        totalMs += (
            ((size_t)temp.time().getMinute().untilPosition(dtRef.first->time().getMinute()) * (size_t)60'000ULL)
        );
        temp.getTime()->getMinute().increment(
            temp.time().getMinute().untilPosition(
                dtRef.first->time().getMinute()
            )
        );

        // Accum. hours
        totalMs += (
            ((size_t)temp.time().getHour().untilPosition(dtRef.first->time().getHour()) * (size_t)3'600'000ULL)
        );
        temp.getTime()->getHour().increment(
            temp.time().getHour().untilPosition(
                dtRef.first->time().getHour()
            )
        );

        // Accum. days
        totalMs += (
            ((size_t)temp.date().daysUntil(dtRef.first->date()) * (size_t)86'400'000ULL)
        );

        return totalMs;
    }

    /* Returns duration from this datetime to provided datetime */
    Duration until(const Datetime& datetime) const noexcept
    {
        if (this == &datetime || *this == datetime)
            return Duration{};
        
        Duration result{};
        result.getMillisecond().largeDisplace(
            Duration::Sign::POSITIVE,
            this->millisecondsUntil(datetime)
        );

        if (this->isAfter(datetime) && result.sign() != Duration::Sign::NEGATIVE)
            result.invert();

        return result;
    }

    /* Returns standard library chronological time point of this datetime */
    Chrono toChrono() const noexcept
    {
        Chrono timePoint{};

        Datetime epoch{ Chrono{} };
        Duration sinceEpoch{ epoch.until(*this) };

        timePoint = (timePoint + sinceEpoch.toChronoDuration());

        return timePoint;
    }

    /* Displace datetime using provided duration */
    void displace(const Duration& duration) noexcept
    {
        this->m_time.displace(duration);
    }


private:
    Date m_date;
    Time m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_OBJ_H_
