
#ifndef SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_
#define SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_



#include"simplydt/datetime/date/comp/dt_date.hpp"
#include"simplydt/datetime/time/comp/dt_stime.hpp"


/* Standard datetime (YYYY-mm-dd-HH-MM-SS) */
class SDatetime {

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

    SDatetime(Chrono chrono) noexcept;

    SDatetime(const Date& date, const STime& s_time) noexcept;

    SDatetime(Date&& date, STime&& s_time) noexcept;

    SDatetime(const Date& date, STime&& s_time) noexcept;

    SDatetime(Date&& date, const STime& s_time) noexcept;

    SDatetime(const Date& date) noexcept;

    SDatetime(Date&& date) noexcept;

    SDatetime(const SDatetime& s_datetime) noexcept;

    SDatetime(SDatetime&& s_datetime) noexcept;

    SDatetime() noexcept;

    ~SDatetime() noexcept = default;

    friend std::ostream& operator<<(std::ostream& os, const SDatetime& s_datetime) noexcept;

    SDatetime& operator=(const SDatetime& s_datetime) noexcept;

    SDatetime& operator=(SDatetime&& s_datetime) noexcept;

    SDatetime& operator=(const Chrono& chrono) noexcept;

    bool operator==(const SDatetime& s_datetime) const noexcept;

    bool operator<(const SDatetime& s_datetime) const noexcept;

    bool operator>(const SDatetime& s_datetime) const noexcept;

    bool operator<=(const SDatetime& s_datetime) const noexcept;

    bool operator>=(const SDatetime& s_datetime) const noexcept;

    SDatetime operator+(const Duration& duration) const noexcept;

    SDatetime operator-(const Duration& duration) const noexcept;

    SDatetime& operator+=(const Duration& duration) noexcept;

    SDatetime& operator-=(const Duration& duration) noexcept;


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

    /* Datetime date object */
    const Date& date() const noexcept;

    /* Datetime time object */
    const STime& time() const noexcept;

    /* Returns datetime hour of day phase */
    Hour::Phase hourPhase() const noexcept;

    /* Returns datetime hour of day phase literal */
    std::string hourPhaseStr() const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Layout layout, Date::Format date_format, Date::Layout date_layout,
        STime::Format time_format, STime::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, Date::Layout date_layout,
        STime::Format time_format, STime::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, Date::Layout date_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(STime::Format time_format, STime::Layout time_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format, STime::Format time_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Layout date_layout, STime::Layout time_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Format date_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(Date::Layout date_layout) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(STime::Format time_format) const noexcept;

    /* Returns datetime string in provided configuration */
    std::string datetimeStr(STime::Layout time_layout) const noexcept;
    
    /* Returns datetime string in provided layout */
    std::string datetimeStr(Layout layout) const noexcept;

    /* Returns datetime string */
    std::string datetimeStr() const noexcept;

    /* Returns datetime day-of-week literal */
    const char* dayOfWeek() const noexcept;

    /* Returns datetime month literal */
    const char* monthTitle() const noexcept;

    /* Returns true if provided datetime occurs after this datetime */
    bool isBefore(const SDatetime& s_datetime) const noexcept;

    /* Returns true if provided date occurs after this datetime date */
    bool isBefore(const Date& date) const noexcept;

    /* Returns true if provided datetime occurs before this datetime */
    bool isAfter(const SDatetime& s_datetime) const noexcept;

    /* Returns true if provided date occurs before this datetime date */
    bool isAfter(const Date& date) const noexcept;

    /* Returns pointer to datetime date */
    Date* getDate() noexcept;

    /* Returns pointer to datetime time */
    Time* getTime() noexcept;

    /* Returns standard library chronological time point copy */
    Chrono toChrono() const noexcept;

    /* Returns absolute total number of days from this datetime to provided datetime */
    size_t daysUntil(const SDatetime& s_datetime) const noexcept;

    /* Returns absolute total number of minutes from this datetime to provided datetime */
    size_t minutesUntil(const SDatetime& s_datetime) const noexcept;

    /* Returns absolute total number of seconds from this datetime to provided datetime */
    size_t secondsUntil(const SDatetime& s_datetime) const noexcept;

    /* Returns duration from this datetime to provided datetime */
    Duration until(const SDatetime& s_datetime) const noexcept;

    /* Displace datetime using provided duration */
    void displace(const Duration& duration) noexcept;


private:
    Date m_date;
    STime m_time;

    void linkDatetime() noexcept
    {
        this->m_time.linkDate(this->m_date);
    }

};



#endif // SIMPLYDTLIB_L_STANDARD_DATETIME_OBJ_H_