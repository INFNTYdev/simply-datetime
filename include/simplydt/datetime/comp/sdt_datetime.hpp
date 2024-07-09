
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

    Datetime(Chrono chrono) noexcept;

    Datetime(const Date& date, const Time& time) noexcept;

    Datetime(Date&& date, Time&& time) noexcept;

    Datetime(const Date& date, Time&& time) noexcept;

    Datetime(Date&& date, const Time& time) noexcept;

    Datetime(const Date& date) noexcept;

    Datetime(Date&& date) noexcept;

    Datetime(const Datetime& datetime) noexcept;

    Datetime(Datetime&& datetime) noexcept;

    Datetime(const SDatetime& s_datetime) noexcept;

    Datetime(SDatetime&& s_datetime) noexcept;

    Datetime() noexcept;

    ~Datetime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const Datetime& datetime) noexcept;

    Datetime& operator=(const Datetime& datetime) noexcept;

    Datetime& operator=(Datetime&& datetime) noexcept;

    Datetime& operator=(const SDatetime& s_datetime) noexcept;

    Datetime& operator=(SDatetime&& s_datetime) noexcept;

    Datetime& operator=(const Chrono& chrono) noexcept;

    bool operator==(const Datetime& datetime) const noexcept;

    bool operator==(const SDatetime& s_datetime) const noexcept;

    bool operator<(const Datetime& datetime) const noexcept;

    bool operator>(const Datetime& datetime) const noexcept;

    bool operator<=(const Datetime& datetime) const noexcept;

    bool operator>=(const Datetime& datetime) const noexcept;

    Datetime operator+(const Duration& duration) const noexcept;

    Datetime operator-(const Duration& duration) const noexcept;

    Datetime& operator+=(const Duration& duration) noexcept;

    Datetime& operator-=(const Duration& duration) noexcept;

    /* Returns datetime year */
    uint16_t year() const noexcept;

    /* Returns datetime month */
    uint16_t month() const noexcept;

    /* Returns datetime day */
    uint16_t day() const noexcept;

    /* Returns datetime hour */
    uint16_t hour() const noexcept;

    /* Returns datetime minute */
    uint16_t minute() const noexcept;

    /* Returns datetime second */
    uint16_t second() const noexcept;

    /* Returns datetime millisecond */
    uint16_t millisecond() const noexcept;

    /* Datetime date object */
    const Date& date() const noexcept;

    /* Datetime time object */
    const Time& time() const noexcept;

    /* Returns datetime hour of day phase */
    Hour::Phase hourPhase() const noexcept;

    /* Returns datetime hour of day phase literal */
    std::string hourPhaseStr() const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Layout layout, Date::Format date_format, Date::Layout date_layout,
        Time::Format time_format, Time::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, Date::Layout date_layout,
        Time::Format time_format, Time::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, Date::Layout date_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Time::Format time_format, Time::Layout time_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, Time::Format time_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Layout date_layout, Time::Layout time_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Layout date_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Time::Format time_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Time::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided layout */
    std::string datetimeStr(Layout layout) const noexcept;

    /* Returns datetime string */
    std::string datetimeStr() const noexcept;

    /* Returns datetime day-of-week literal */
    const char* dayOfWeek() const noexcept;

    /* Returns datetime month literal */
    const char* monthTitle() const noexcept;

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const Datetime& datetime) const noexcept;

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const Date& date) const noexcept;

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const Datetime& datetime) const noexcept;

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const Date& date) const noexcept;

    /* Returns pointer to datetime date */
    Date* getDate() noexcept;

    /* Returns pointer to datetime time */
    Time* getTime() noexcept;

    /* Returns standard datetime copy of this datetime */
    SDatetime toSDatetime() const noexcept;

    /* Returns standard library chronological time point of this datetime */
    Chrono toChrono() const noexcept;

    /* Returns absolute total number of days from this datetime to provided datetime */
    size_t daysUntil(const Datetime& datetime) const noexcept;

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    size_t minutesUntil(const Datetime& datetime) const noexcept;

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const Datetime& datetime) const noexcept;

    /* Returns absolute total number of milliseconds from this datetime to provided datetime */
    size_t millisecondsUntil(const Datetime& datetime) const noexcept;

    /* Returns duration from this datetime to provided datetime */
    Duration until(const Datetime& datetime) const noexcept;

    /* Displace datetime using provided duration */
    void displace(const Duration& duration) noexcept;


private:
    Date m_date;
    Time m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_DATETIME_OBJ_H_
